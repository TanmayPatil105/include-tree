/* header.c
 *
 * Copyright 2024 Tanmay Patil <tanmaynpatil105@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include "header.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX(a, b) (a > b ? a : b)


struct Header *
header_init (char *name)
{
  struct Header *header;

  header = malloc (sizeof (struct Header));

  header->name = strdup (name);

  header->n_children = 0;
  header->height = 1;
  header->children = NULL;

  return header;
}

void
header_rename (struct Header *header,
               char          *new_name)
{
  if (header->name)
    free (header->name);

  header->name = strdup (new_name);
}

static void
header_add_child (struct Header *header,
                  struct Header *child)
{
  header->children = realloc (header->children,
                              sizeof (struct Header *)
                              * (header->n_children + 1));

  header->children[header->n_children++] = child;
}

char *
get_header_from_line (char *line)
{
  char *quote, *end;

  if (strncmp (line, "#include", 8) != 0)
    return NULL;

  quote = strchr (line, '"');
  if (quote == NULL)
    return NULL;

  end = strchr (quote + 1, '"');
  if (end == NULL)
    return NULL;

  return strndup (quote + 1, end - quote - 1);
}

struct Header *
header_read (char       *file,
             struct Set *set)
{
  struct Header *header;
  FILE *fp;
  char *line = NULL;
  size_t len;
  int height = 1;

  header = header_init (file);

  fp = fopen (file, "r");

  /* We don't mind if the file is valid or invalid
   * Instead just add it to output */
  if (fp == NULL)
    { 
      return header;
    }

  if (set_contains (set, file))
    { 
      fclose (fp);
      return header;
    }

  set_add (set, file);

  while (getline (&line, &len, fp) != -1)
    {
      char *inc;
      struct Header *child;

      inc = get_header_from_line (line);
      if (inc == NULL)
        continue;

      /* depth-first search */
      child = header_read (inc, set);
      header_add_child (header, child);

      height = MAX (height, child->height + 1);

      free (inc);
    }

  header->height = height;

  if (line)
    free (line);

  fclose (fp);

  return header;
}

/* Should we use ASCII ?? */
#define CONTINUE "│   "

#define MIDDLE   "├── "

#define LAST     "└── "

static void
header_print_helper (struct Header *header,
                     int            depth,
                     bool          *is_last)
{

  for (int i = 0; i < depth - 1; i++)
    {
      if (is_last[i])
        printf ("    ");
      else
        printf (CONTINUE);
    }

  if (depth > 0)
    {
      printf ("%s", is_last[depth - 1] ? LAST : MIDDLE);
    }

  printf ("%s\n", header->name);
  for (int i = 0; i < header->n_children; i++)
    {
      is_last[depth] = i == header->n_children - 1;
      header_print_helper (header->children[i], depth + 1,
                           is_last);
    }
}

void
header_print_tree (struct Header *header)
{
  bool *is_last = malloc (sizeof (bool) * header->height);

  header_print_helper (header, 0, is_last);

  free (is_last);
}

void
header_free (struct Header *header)
{
  if (header->name)
    free (header->name);

  for (int i = 0; i < header->n_children; i++)
    {
      header_free (header->children[i]);
    }

  free (header->children);

  free (header);
}
