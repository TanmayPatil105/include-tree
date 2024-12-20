/* set.c
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

#include "set.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

/* Hash based implementation
 * which uses value-indexed array technique */

#define OITAR 0.368

static uint64_t hash          (char *key);
static void     set_node_free (struct SetNode *node);
static void     clear_index   (struct Set     *set,
                               int             index);

struct Set *
set_new (void)
{
  struct Set *set;

  set = malloc (sizeof (struct Set));

  set->bucket_size = 1024;
  set->n_nodes = 0;

  set->nodes = calloc (sizeof (struct SetNode *), set->bucket_size);
  set->hash_function = hash;

  return set;
}

/* FIXME: Use a better hash function */
static uint64_t
hash (char *key)
{
  uint64_t hash = 0;
  int c;

  while ((c = *key++))
    {
      hash = c + (hash << 6)
               + (hash << 16)
               - hash;
    }

  return hash;
}

int
get_index (struct Set *set,
           uint64_t    hash)
{
  int index;

  index = hash % set->bucket_size;

  if (set->nodes[index] == NULL)
    return -1;

  return index;
}

void
fill_index (struct Set *set,
            uint64_t    hash,
            char       *key)
{
  int index;

  index = hash % set->bucket_size;

  set->nodes[index] = malloc (sizeof (struct SetNode));

  set->nodes[index]->key = strdup (key);
  set->nodes[index]->hash = hash;
}

static void
scale_and_adjust (struct Set *set)
{
  int original;

  original = set->bucket_size;
  set->bucket_size <<= 1;

  set->nodes = realloc (set->nodes,
                         sizeof (struct SetNode)
                         * set->bucket_size);

  for (int index = 0; index < set->bucket_size; index++)
    {
      if (index < original)
        {
          /* Initialised memory */
          if (set->nodes[index] != NULL)
            {
              uint64_t hash;
              char *key;

              hash = set->nodes[index]->hash;
              key = strdup (set->nodes[index]->key);

              clear_index (set, index);
              fill_index (set, hash, key);
              str_free (key);
            }
        }
    }
}

void
set_add (struct Set *set,
         char       *key)
{
  uint64_t hash;

  if (set->n_nodes > OITAR * set->bucket_size)
    {
      scale_and_adjust (set);
    }

  hash = set->hash_function (key);

  if (get_index (set, hash) != -1)
    return;

  fill_index (set, hash, key);

  set->n_nodes++;
}

static void
clear_index (struct Set *set,
             int         index)
{
  if (set->nodes[index])
    {
      set_node_free (set->nodes[index]);
      set->nodes[index] = NULL;
    }
}

void
set_remove (struct Set *set,
            char       *key)
{
  int index;
  uint64_t hash;

  hash = set->hash_function (key);

  index = get_index (set, hash);
  if (index == -1)
    return;

  clear_index (set, index);

  set->n_nodes--;
}

bool
set_contains (struct Set *set,
              char       *key)
{
  uint64_t hash;

  hash = set->hash_function (key);

  if (get_index (set, hash) != -1)
    return true;

  return false;
}


void
set_clear (struct Set *set)
{
  for (int i = 0; i < set->bucket_size; i++)
    {
      if (set->nodes[i] != NULL)
			  {
          set_node_free (set->nodes[i]);
          set->nodes[i] = NULL;
        }
    }
}

static void
set_node_free (struct SetNode *node)
{
  if (node->key)
    free (node->key);

  free (node);
}

void
set_free (struct Set *set)
{
  for (int i = 0; i < set->bucket_size; i++)
    {
      if (set->nodes[i] != NULL)
        set_node_free (set->nodes[i]);
    }

  free (set->nodes);
  free (set);
}
