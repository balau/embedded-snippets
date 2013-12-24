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


#ifndef POOL_T
#  error POOL_T needed. e.g. #define POOL_T char
#endif

#ifndef POOL_TNAME
#  error POOL_TNAME needed. e.g. #define POOL_TNAME char
#endif

#include "pool.h"

#define POOL_CREATE_NAME_2(tname, suffix) pool_ ## tname ## _ ## suffix
#define POOL_CREATE_NAME_1(tname, suffix) POOL_CREATE_NAME_2(tname, suffix)
#define POOL_CREATE_NAME(suffix) POOL_CREATE_NAME_1(POOL_TNAME, suffix)

#define POOL_STRUCT_NAME_2(tname) pool_ ## tname
#define POOL_STRUCT_NAME_1(tname) POOL_STRUCT_NAME_2(tname)
#define POOL_STRUCT_NAME POOL_STRUCT_NAME_1(POOL_TNAME)

#define POOL_TYPE POOL_T

/* TODO: check if it works with arrays and function pointers. */

struct POOL_STRUCT_NAME
{
	struct pool pool;
	POOL_TYPE *buffer;
};

extern
void POOL_CREATE_NAME(init)(
        struct POOL_STRUCT_NAME *, /* pool */
        pool_flag_T *, /* flags */
        POOL_TYPE *, /* buffer */
        size_t); /* size */

extern
int POOL_CREATE_NAME(isempty)(
    const struct POOL_STRUCT_NAME *); /* pool */

extern
POOL_TYPE * POOL_CREATE_NAME(reserve)(
    struct POOL_STRUCT_NAME *); /* pool */

extern
int POOL_CREATE_NAME(release)(
    struct POOL_STRUCT_NAME *, /* pool */
    POOL_TYPE *); /* resource */

extern
struct POOL_STRUCT_NAME *POOL_CREATE_NAME(alloc)(
        size_t); /* n_resources */

extern
void POOL_CREATE_NAME(free)(struct POOL_STRUCT_NAME *);

