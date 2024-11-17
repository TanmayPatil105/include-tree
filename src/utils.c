/* utils.c
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
#include "log.h"

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

void
utils_throw_error (char *format, ...)
{
  va_list list;

  va_start (list, format);

  fprintf (stderr, "itree: ");
  vfprintf (stderr, format, list);
  fprintf (stderr, "\n");

  va_end (list);

  exit (EXIT_FAILURE);
}

void
utils_throw_warning (char *format, ...)
{
  va_list list;

  va_start (list, format);

  fprintf (stderr, "itree: warning: ");
  vfprintf (stderr, format, list);
  fprintf (stderr, "\n");

  va_end (list);
}

char *
utils_get_absolute_path (char *path)
{
  char *abs = NULL;
  char *ptr = NULL;
  char *last = NULL;

  ptr = realpath (path, NULL);
  if (ptr == NULL)
    return strdup (path);

  last = strrchr (ptr, '/');
  if (last == NULL)
    {
      str_free (ptr);
      return strdup (path);
    }

  abs = strdup (last + 1);

  /* change directory to parent */
  *last = '\0';
  utils_change_dir (ptr);

  str_free (ptr);

  return abs;
}

int
utils_change_dir (char *dir)
{
  int ret;

  ret = chdir (dir);

  return ret;
}
