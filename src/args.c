/* args.c
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

#include "args.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>

static struct Args *
args_init (void)
{
  struct Args *args;

  args = malloc (sizeof (struct Args));

  args->n_files = 0;
  args->input = NULL;

  args->print_help = false;
  args->flag_cycle = false;
  args->depth = INT_MAX;   /* Infinite depth */

  return args;
}

#define CMP_ARGS(arg, lng, shrt)      \
        ((strcmp (arg, lng) == 0)      \
         || (strcmp (arg, shrt) == 0))


static void
print_help (char *binary)
{
  fprintf (stdout, "Usage: %s [input files]\n"
  "Print file inclusion tree\n"
  "\n"
  "Optional arguments:\n"
  "  -d, --depth             set recursion depth\n"
  "  -c, --cycle             detect cyclic inclusion\n"
  "  -h, --help              display this message\n", binary);
}

struct Args *
args_parse (int   argc,
            char *argv[])
{
  struct Args *args;

  args = args_init ();

  for (int i = 1; i < argc; i++)
    {
      if (CMP_ARGS (argv[i], "--help", "-h"))
        {
          args->print_help = true;
          break;
        }
      else if (CMP_ARGS (argv[i], "--depth", "-d"))
        {
          i++;
          if (i >= argc)
            utils_throw_error ("args: --depth requires an argument");

          args->depth = atoi (argv[i]);
        }
      else if (CMP_ARGS (argv[i], "--cycle", "-c"))
        {
          args->flag_cycle = true;
        }
      else
        {
          args->n_files++;

          args->input = realloc (args->input, sizeof (char *)
                                              * args->n_files);
          args->input[args->n_files - 1] = strdup (argv[i]);
        }
    }

  if (args->print_help)
    {
      print_help (argv[0]);
      exit (EXIT_SUCCESS);
    }

  if (args->depth != INT_MAX
      && args->flag_cycle)
    utils_throw_warning ("the --depth flag should not be used with --cycle");

  return args;
}

void
args_free (struct Args *args)
{
  for (int i = 0; i < args->n_files; i++)
    {
      if (args->input[i])
        free (args->input[i]);
    }

  if (args->input)
    free (args->input);

  free (args);
}
