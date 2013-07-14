
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

