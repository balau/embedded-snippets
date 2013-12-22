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


#ifndef FIFO_T
#  error FIFO_T needed. e.g. #define FIFO_T char
#endif

#ifndef FIFO_TNAME
#  error FIFO_TNAME needed. e.g. #define FIFO_TNAME char
#endif

#include <stdlib.h>

#define FIFO_CREATE_NAME_2(tname, suffix) fifo_ ## tname ## _ ## suffix
#define FIFO_CREATE_NAME_1(tname, suffix) FIFO_CREATE_NAME_2(tname, suffix)
#define FIFO_CREATE_NAME(suffix) FIFO_CREATE_NAME_1(FIFO_TNAME, suffix)

#define FIFO_STRUCT_NAME_2(tname) fifo_ ## tname
#define FIFO_STRUCT_NAME_1(tname) FIFO_STRUCT_NAME_2(tname)
#define FIFO_STRUCT_NAME FIFO_STRUCT_NAME_1(FIFO_TNAME)

#define FIFO_TYPE FIFO_T

/* TODO: check if it works with arrays and function pointers. */

struct FIFO_STRUCT_NAME
{
	size_t size;
	size_t in;
	size_t out;
	FIFO_TYPE *buffer;
};

extern
void FIFO_CREATE_NAME(init)(
        struct FIFO_STRUCT_NAME *, /* fifo */
        FIFO_TYPE *, /* buffer */
        size_t); /* size */

int FIFO_CREATE_NAME(isempty)(
    const struct FIFO_STRUCT_NAME *); /* fifo */

int FIFO_CREATE_NAME(isfull)(
    const struct FIFO_STRUCT_NAME *); /* fifo */

int FIFO_CREATE_NAME(insert)(
    struct FIFO_STRUCT_NAME *, /* fifo */
    FIFO_TYPE); /* element */

int FIFO_CREATE_NAME(peek)(
    const struct FIFO_STRUCT_NAME *, /* fifo */
    /*@out@*/ FIFO_TYPE *); /* element */

int FIFO_CREATE_NAME(remove)(
    struct FIFO_STRUCT_NAME *, /* fifo */
    /*@out@*/ FIFO_TYPE *); /* element */

void FIFO_CREATE_NAME(flush)(
    struct FIFO_STRUCT_NAME *); /* fifo */


