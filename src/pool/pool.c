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

#include "pool.h"

#define POOL_FLAG_AVAIL ((pool_flag_T)0)
#define POOL_FLAG_BUSY  ((pool_flag_T)1)

void pool_init(
        struct pool *p,
        pool_flag_T *flags,
        size_t size)
{
    int i;

    for (i = 0; ((size_t)i) < size; i++)
    {
        flags[i] = POOL_FLAG_AVAIL;
    }
    p->flags = flags;
    p->size = size;
    p->next_guess = 0;
    p->n_avail = size;
}

static
int isavail(const struct pool *p, int idx)
{
    return (p->flags[idx] == POOL_FLAG_AVAIL)?1:0;
}

static
int incr(const struct pool *p, int idx)
{
    idx++;
    if (((size_t)idx) >= p->size)
        idx = 0;
    return idx;
}

int pool_isempty(const struct pool *p)
{
    return (p->n_avail == 0)?1:0;
}

int pool_reserve(struct pool *p)
{
    int i = p->next_guess;
    if(pool_isempty(p) != 0)
    {
        return -1;
    }
    else
    {
        while(isavail(p, i) == 0)
        {
            i = incr(p, i);
        }
        p->flags[i] = POOL_FLAG_BUSY;
        p->n_avail--;
        p->next_guess = incr(p, i);
        return i;
    }
}

int pool_release(
        struct pool *p,
        int idx)
{
    if ((idx >= 0) && (((size_t)idx) < p->size))
    {
        if(isavail(p, idx) == 0)
        {
            p->n_avail++;
            p->next_guess = idx;
            p->flags[idx] = POOL_FLAG_AVAIL;
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -2;
    }
}

