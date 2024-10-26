/* main.c
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

#include "utils.h"
#include "header.h"
#include "set.h"

int
main (int   argc,
      char *argv[])
{
  struct Set *set;

  set = set_new ();

  if (argc < 2)
    utils_throw_error ("Not enough arguments");

  for (int i = 1; i < argc; i++)
    {
      struct Header *header;

      header = header_read (argv[i], set);
      header_print_tree (header);

      header_free (header);
    }

  set_free (set);

  return 0;
}
