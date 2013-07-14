ES_ROOT = ../../

CFLAGS += -I$(ES_ROOT)include/fifo/
LDFLAGS += -pthread

fifo_test: fifo_test.o $(ES_ROOT)src/fifo/fifo.o

fifo_test.o: $(ES_ROOT)include/fifo/fifo.h

$(ES_ROOT)src/fifo/fifo.o: $(ES_ROOT)include/fifo/fifo.h

clean:
	rm -rf $(ES_ROOT)src/fifo/fifo.o fifo_test.o fifo_test

