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


#ifndef FIFO_H
#define FIFO_H

#include <stdint.h>

struct fifo_T
{
	volatile void *buffer;
	uint32_t buffer_len;
	uint32_t entry_size;
	volatile uint32_t head;
	volatile uint32_t tail;
};

#define FIFO_INIT(fifo_, buffer_, buffer_len_, entry_size_)\
	struct fifo_T fifo_ = {\
		.buffer = buffer_,\
		.buffer_len = buffer_len_,\
		.entry_size = entry_size_,\
		.head = 0,\
		.tail = 0,\
	}

void fifo_init(struct fifo_T *fifo, void *buffer, uint32_t buffer_len, uint32_t entry_size);
int32_t fifo_put(struct fifo_T *fifo, const void * entry);
int32_t fifo_get(struct fifo_T *fifo, void *entry);
int32_t fifo_isempty(struct fifo_T *fifo);
int32_t fifo_isfull(struct fifo_T *fifo);
void fifo_flush(struct fifo_T *fifo);

#endif /* FIFO_H */

