ES_ROOT = ../../

CFLAGS += -I$(ES_ROOT)include/fsm/

fsm_test: fsm_test.o $(ES_ROOT)src/fsm/fsm.o

fsm_test.o: $(ES_ROOT)include/fsm/fsm.h

$(ES_ROOT)src/fsm/fsm.o: $(ES_ROOT)include/fsm/fsm.h

clean:
	rm -rf $(ES_ROOT)src/fsm/fsm.o fsm_test.o fsm_test

