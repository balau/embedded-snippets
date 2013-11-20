/*
 * Copyright (c) 2013 Francesco Balducci
 *
 * This file is part of embedded-snippets.
 *
 *    embedded-snippets is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    embedded-snippets is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with embedded-snippets.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef IDSTRING_H
#define IDSTRING_H

# include <stdint.h>

#ifdef IDSTRING_EXPAND_TO_ID

#  ifndef IDSTRING_SECTION
#    define IDSTRING_SECTION .idstrings
#  endif

#  define IDSTRING_SECTION_STRINGIFY_2(s) (#s)
#  define IDSTRING_SECTION_STRINGIFY(s) IDSTRING_SECTION_STRINGIFY_2(s)
#  define IDSTRING_SECTION_STR IDSTRING_SECTION_STRINGIFY(IDSTRING_SECTION)

/* http://stackoverflow.com/questions/6447463/forcing-certain-compiler-generated-variables-into-specific-elf-sections-with-gc */

#  define idstring(s) (__extension__({__attribute__((__section__(IDSTRING_SECTION_STR))) static const char c[] = (s); (intptr_t)&c[0];}))

#else /* !IDSTRING_EXPAND_TO_ID */

#  define idstring(s) (s)

#endif /* IDSTRING_EXPAND_TO_ID */

#define _(s) idstring(s)


#endif /*IDSTRING_H*/

