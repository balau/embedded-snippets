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


#ifndef POOL_H
#define POOL_H

#include <stdlib.h>

typedef unsigned char pool_flag_T;

struct pool
{
    size_t size;
    pool_flag_T *flags;
    int next_guess;
    size_t n_avail;
};

extern
void pool_init(
        struct pool *,
        pool_flag_T *,
        size_t);

extern
int pool_isempty(const struct pool *);

extern
int pool_reserve(struct pool *);

extern
int pool_release(
        struct pool *,
        int);

#endif /* POOL_H */

