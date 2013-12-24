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

#include <stdlib.h>

#include "pool.h"

struct pool *pool_alloc(
        size_t n_resources)
{
    struct pool *p;
    pool_flag_T *flags;
    p = malloc(sizeof(struct pool));
    if (p != NULL)
    {
        flags = malloc(sizeof(pool_flag_T) * n_resources);
        if (flags != NULL)
        {
            pool_init(p, flags, n_resources);
            return p;
        }
        else
        {
            free(p);
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

void pool_free(struct pool *p)
{
    free(p->flags);
    free(p);
}

