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

#include <string.h>
#include "fifo.h"

static inline
uint32_t fifo_next_idx(uint32_t cur_idx, uint32_t buffer_len)
{
	uint32_t next_idx;
	next_idx = cur_idx + 1;
	if(next_idx >= buffer_len)
		next_idx = 0;
	return next_idx;
}

static inline
int32_t fifo_isempty_check(uint32_t head, uint32_t tail)
{
	return (head == tail)?1:0;
}

static inline
int32_t fifo_isfull_check(uint32_t head, uint32_t tail, uint32_t buffer_len)
{	
	return (head == fifo_next_idx(tail, buffer_len))?1:0;
}

void fifo_init(struct fifo_T *fifo, void *buffer, uint32_t buffer_len, uint32_t entry_size)
{
	fifo->buffer = buffer;
	fifo->buffer_len = buffer_len;
	fifo->entry_size = entry_size;
	fifo->head = 0;
	fifo->tail = 0;
}

int32_t fifo_isempty(struct fifo_T *fifo)
{
	return fifo_isempty_check(fifo->head, fifo->tail);
}

int32_t fifo_isfull(struct fifo_T *fifo)
{
	return fifo_isfull_check(fifo->head, fifo->tail, fifo->buffer_len);
}

int32_t fifo_put(struct fifo_T *fifo, const void * entry)
{
	int32_t put_result;
	uint32_t tail, buffer_len;

	tail = fifo->tail;
	buffer_len = fifo->buffer_len;
	
	if(fifo_isfull_check(fifo->head, tail, buffer_len) != 0)
	{
		put_result = 1;
	}
	else
	{
		void *p_entry;
		uint32_t entry_size;

		entry_size = fifo->entry_size;
		p_entry = ((uint8_t *)fifo->buffer) + (entry_size * tail);
		memcpy(p_entry, entry, entry_size);
		fifo->tail = fifo_next_idx(tail, buffer_len);
		put_result = 0;
	}
	return put_result;
}

int32_t fifo_get(struct fifo_T *fifo, void *entry)
{
	int32_t get_result;
	uint32_t head;

	head = fifo->head;
	
	if(fifo_isempty_check(head, fifo->tail) != 0)
	{
		get_result = 1;
	}
	else
	{
		void *p_entry;
		uint32_t entry_size;

		entry_size = fifo->entry_size;		
		p_entry = ((uint8_t *)fifo->buffer) + (entry_size * head);
		memcpy(entry, p_entry, entry_size);
		fifo->head = fifo_next_idx(head, fifo->buffer_len);
		
		get_result = 0;
	}
	
	return get_result;
}

void fifo_flush(struct fifo_T *fifo)
{
	fifo->head = fifo->tail;
}

