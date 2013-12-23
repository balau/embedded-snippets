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

#ifndef POOL_MSG_H
#define POOL_MSG_H

#include <stdint.h>

struct msg
{
    uint32_t to;
    uint32_t from;
    uint32_t state;
    uint32_t code;
    uint8_t payload[16];
};

#define POOL_T struct msg
#define POOL_TNAME msg
#include "pool_t.h"

#endif /* POOL_MSG_H */

