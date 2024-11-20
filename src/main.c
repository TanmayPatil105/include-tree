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
#include "args.h"

int
main (int   argc,
      char *argv[])
{
  struct Args *args;
  struct Set *set;
  char *cwd;

  args = args_parse (argc, argv);

  set = set_new ();
  cwd = get_current_dir_name ();

  if (argc < 2)
    utils_throw_error ("Not enough arguments");

  for (int i = 0; i < args->n_files; i++)
    {
      struct Header *header;
      char *path;
      char *file = args->input[i];

      path = utils_get_absolute_path (file);

      header = header_read (path, set, args);
      header_rename (header, file);

      header_print_tree (header);

      /* restore current dir */
      utils_change_dir (cwd);

      if (args->independent)
        set_clear (set);

      str_free (path);
      header_free (header);
    }

  str_free (cwd);
  set_free (set);
  args_free (args);

  return 0;
}
