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

/* TODO: check if pool_t.h has been included. */

#ifndef POOL_T
#  error POOL_T needed. e.g. #define POOL_T uint8_t
#endif

#ifndef POOL_TNAME
#  error POOL_TNAME needed. e.g. #define POOL_TNAME uint8
#endif

struct POOL_STRUCT_NAME *POOL_CREATE_NAME(alloc)(
        size_t size)
{
    struct POOL_STRUCT_NAME *p;
    POOL_TYPE *buffer;
    pool_flag_T *flags;

    buffer = malloc(sizeof(POOL_TYPE) * size);
    if (buffer != NULL)
    {
        p = malloc(sizeof(struct POOL_STRUCT_NAME));
        if (p != NULL)
        {
            flags = malloc(sizeof(pool_flag_T) * size);
            if (flags != NULL)
            {

                POOL_CREATE_NAME(init)(p, flags, buffer, size);
                return p;
            }
            else
            {
                free(p);
                free(buffer);
                return NULL;
            }
        }
        else
        {
            free(buffer);
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

void POOL_CREATE_NAME(free)(
    struct POOL_STRUCT_NAME *p)
{
    free(p->buffer);
    free(p->pool.flags);
    free(p);
}

