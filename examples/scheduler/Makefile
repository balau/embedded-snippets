ES_ROOT = ../../

CFLAGS += -I$(ES_ROOT)include/scheduler/

scheduler_test: scheduler_test.o $(ES_ROOT)src/scheduler/scheduler.o

scheduler_test.o: $(ES_ROOT)include/scheduler/scheduler.h

$(ES_ROOT)src/scheduler/scheduler.o: $(ES_ROOT)include/scheduler/scheduler.h

clean:
	rm -rf $(ES_ROOT)src/scheduler/scheduler.o scheduler_test.o scheduler_test

