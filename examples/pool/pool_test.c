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

int main(void) {
    struct pool *p;
    int i;
    int reserve_i;

    p = pool_alloc(N_RESOURCES);

    for(i = 0; i < N_RESOURCES; i++)
    {
        reserve_i = pool_reserve(p);
        printf("reserve: %d\n", reserve_i);

        reserve_i = pool_reserve(p);
        printf("reserve: %d\n", reserve_i);
        printf("release(%d): %d\n", reserve_i, pool_release(p, reserve_i));

    }
    for(i = 0; i < N_RESOURCES; i++)
    {
        printf("release(%d): %d\n", i, pool_release(p, i));
    }
    
    pool_free(p);

	return 0;
}

