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

#include <stdio.h>

#include "pool.h"

#define N_RESOURCES 10

static
int resources[N_RESOURCES];

static
struct pool pool;

static
pool_flag_T flags[N_RESOURCES];

int main(void) {
    struct pool *p = &pool;
    int i;
    int alloc_i;

    pool_init(p, flags, N_RESOURCES);

    for(i = 0; i < N_RESOURCES; i++)
    {
        alloc_i = pool_alloc(p);
        printf("alloc: %d\n", alloc_i);

        alloc_i = pool_alloc(p);
        printf("alloc: %d\n", alloc_i);
        printf("free(%d): %d\n", alloc_i, pool_free(p, alloc_i));

    }
    for(i = 0; i < N_RESOURCES; i++)
    {
        printf("free(%d): %d\n", i, pool_free(p, i));
    }

	return 0;
}

