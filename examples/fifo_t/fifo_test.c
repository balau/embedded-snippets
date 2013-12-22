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

#include "fifo_uint8.h"

static
struct fifo_uint8 fifo;

/*@shared@*/
static
uint8_t buffer[10];

int main(void) {
    struct fifo_uint8 *f;
    uint8_t e;
    f = &fifo;

    fifo_uint8_init(f, buffer, sizeof(buffer)/sizeof(buffer[0]));

    if (fifo_uint8_isfull(f) == 0)
    {
        if (fifo_uint8_insert(f, 10) != 0)
        {
            printf("error: insert\n");
        }
    }

    if (fifo_uint8_isempty(f) == 0)
    {
        if (fifo_uint8_peek(f, &e) != 0)
        {
            printf("error: peek\n");
        }
        else
        {
            printf("peek: %hu\n", (unsigned short)e);
        }

        if (fifo_uint8_remove(f, &e) != 0)
        {
            printf("error: remove\n");
        }
        else
        {
            printf("remove: %hu\n", (unsigned short)e);
        }
    }
    
    fifo_uint8_flush(f);

	return 0;
}

