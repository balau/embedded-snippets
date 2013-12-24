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

void POOL_CREATE_NAME(init)(
        struct POOL_STRUCT_NAME *p,
        pool_flag_T *flags,
        POOL_TYPE *buffer,
        size_t size)
{
    p->buffer = buffer;
    pool_init(&p->pool, flags, size);
}

int POOL_CREATE_NAME(isempty)(
    const struct POOL_STRUCT_NAME *p)
{
    return pool_isempty(&p->pool);
}

POOL_TYPE * POOL_CREATE_NAME(reserve)(
    struct POOL_STRUCT_NAME *p)
{
    int idx;

    idx = pool_reserve(&p->pool);
    if(idx >= 0)
    {
        return &p->buffer[idx];
    }
    else
    {
        return NULL;
    }
}

static
int get_idx(
    struct POOL_STRUCT_NAME *p,
    POOL_TYPE *elem)
{
    POOL_TYPE *start = &p->buffer[0];

    if (elem < start)
    {
        return -1;
    }
    else
    {
        size_t idx;
        idx = (elem - start) / sizeof(POOL_TYPE);
        if (idx >= p->pool.size)
        {
            return -1;
        }
        else
        {
            return (int)idx;
        }
    }
}

int POOL_CREATE_NAME(release)(
    struct POOL_STRUCT_NAME *p,
    POOL_TYPE *elem)
{
    int idx;

    idx = get_idx(p, elem);
    if(idx >= 0)
    {
        int ret;

        ret = pool_release(&p->pool, idx);
        if (ret == 0)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

