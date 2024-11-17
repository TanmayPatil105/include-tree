/* log.c
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

#include "log.h"

#include <stdio.h>
#include <stdarg.h>

#define COLOR_RESET "\033[0;m"

static char *
get_color_sequence (LogColor color)
{
  switch (color)
    {
      case COLOR_RED:
        return "\033[0;31m";
      case COLOR_GREEN:
        return "\033[0;32m";
      case COLOR_YELLOW:
        return "\033[0;33m";
    }

  return COLOR_RESET;
}

void
log_str (LogColor  color,
         char     *format, ...)
{
  va_list list;

  va_start (list, format);

  if (color != COLOR_NONE)
    fprintf (stdout,
             "%s", get_color_sequence (color));

  vfprintf (stdout, format, list);

  if (color != COLOR_NONE)
    fprintf (stdout, COLOR_RESET);

  va_end (list);
}
