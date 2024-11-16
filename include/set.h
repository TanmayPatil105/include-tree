/* set.h
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

#ifndef SET_H
#define SET_H

#include <stdbool.h>
#include <stdint.h>

struct SetNode
{
  char *key;
  uint64_t hash;
};

struct Set
{
  int bucket_size;

  struct SetNode **nodes;

  uint64_t (*hash_function) (char *key);
};

struct Set *set_new      (void);
void        set_add      (struct Set *set,
                          char       *key);
void        set_remove   (struct Set *set,
                          char       *key);
bool        set_contains (struct Set *set,
                          char       *key);
void        set_free     (struct Set *set);


#endif
