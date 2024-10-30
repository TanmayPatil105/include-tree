/* header.h
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

#ifndef HEADER_H
#define HEADER_H

#include "set.h"

struct Header
{
  char *name;                /* name of header file */

  int height;                /* height of the header inside current tree */

  int n_children;            /* number of files included */
  struct Header **children;  /* pointer to included files */
};

struct Header *header_read       (char          *file,
                                  struct Set    *set);
void           header_rename     (struct Header *header,
                                  char          *new_name);
void           header_print_tree (struct Header *header);
void           header_free       (struct Header *header);

#endif
