#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "fifo.h"

#define FIFO_BUFFER_LEN 50

static uint32_t fifo_buffer[FIFO_BUFFER_LEN];
//static struct fifo_T fifo;
static FIFO_INIT(fifo, fifo_buffer, FIFO_BUFFER_LEN, sizeof(uint32_t));

static void print_fifo_state(struct fifo_T *fifo)
{
	uint32_t i_entry;
	printf("L:%u H:%u T:%u ", (unsigned int)(fifo->tail - fifo->head)%fifo->buffer_len, (unsigned int)fifo->head, (unsigned int)fifo->tail);
	for(i_entry = 0; i_entry < FIFO_BUFFER_LEN; i_entry++)
	{
		printf("%02x ", (unsigned int)fifo_buffer[i_entry]);
	}
	printf("\n");
}

#define DATA_LEN 100000
static uint32_t producer_in[DATA_LEN];
static uint32_t consumer_out[DATA_LEN];

static void *produce(void *ptr)
{
	struct fifo_T *fifo;
	uint32_t i_entry = 0;
	
	fifo = ptr;
	
	while(i_entry < DATA_LEN)
	{
		if((rand()%128) == 0)
		{
			uint32_t entry;
			
			entry = producer_in[i_entry];
			
			if(fifo_put(fifo, &entry) == 0)
			{
				//printf("put %02x\n", entry);
				i_entry++;
			}
		}
		else
		{
			
		}
	}
	return NULL;
}

static void *consume(void *ptr)
{
	struct fifo_T *fifo;
	uint32_t i_entry = 0;
	
	fifo = ptr;
	
	while(i_entry < DATA_LEN)
	{
		if((rand()%128) == 0)
		{
			uint32_t entry;
						
			if(fifo_get(fifo, &entry) == 0)
			{
				consumer_out[i_entry] = entry;
				i_entry++;
				//printf("get %02x\n", entry);
			}
		}
		else
		{
			
		}
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	uint32_t i_entry;
	
	pthread_t producer_th, consumer_th;
	
	//fifo_init(&fifo, fifo_buffer, FIFO_BUFFER_LEN, sizeof(uint32_t));

	pthread_create(&producer_th, NULL, produce, &fifo);
	pthread_create(&consumer_th, NULL, consume, &fifo);

	pthread_join(producer_th, NULL);
	pthread_join(consumer_th, NULL);
	
	for(i_entry = 0; i_entry < DATA_LEN; i_entry++)
	{
		if(producer_in[i_entry] != consumer_out[i_entry])
		{
			printf("%u\n", i_entry);
		}
	}
	return 0;
}

