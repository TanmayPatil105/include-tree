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

#include <stdlib.h>
#include <string.h>

/* Hash based implementation
 * which uses value-indexed array technique */

/*
 * These is fairly large amount of memory
 * We rely on the hash function to avoid collisions */
#define BUCKET_SIZE 1024

static uint64_t hash (char *key);

struct Set *
set_new (void)
{
  struct Set *set;

  set = malloc (sizeof (struct Set *));

  set->nodes = calloc (sizeof (struct SetNode *), BUCKET_SIZE);
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

  index = hash % BUCKET_SIZE;

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

  index = hash % BUCKET_SIZE;

  set->nodes[index] = malloc (sizeof (struct SetNode));

  set->nodes[index]->key = strdup (key);
  set->nodes[index]->hash = hash;
}

void
set_add (struct Set *set,
         char       *key)
{
  uint64_t hash;

  hash = set->hash_function (key);

  if (get_index (set, hash) != -1)
    return;

  fill_index (set, hash, key);
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
  for (int i = 0; i < BUCKET_SIZE; i++)
    {
      if (set->nodes[i] != NULL)
        set_node_free (set->nodes[i]);
    }

  free (set->nodes);
  free (set);
}
