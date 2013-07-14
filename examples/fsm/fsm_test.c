#include <stdio.h>

#include "fsm.h"

enum states
{
	ST_INIT,
	ST_RX,
	ST_TX,

	N_STATES,
};

int action_init(const struct fsm_T *, void *);
int action_rx(const struct fsm_T *, void *);
int action_tx(const struct fsm_T *, void *);
int entry_action_rx(const struct fsm_T *fsm, void *ptr);

fsm_action_T actions[N_STATES] = {
	[ST_INIT] = action_init,
	[ST_RX] = action_rx,
	[ST_TX] = action_tx,
};

fsm_action_T entry_actions[N_STATES] = {
	[ST_RX] = entry_action_rx,
};

int action_init(const struct fsm_T *fsm, void *ptr)
{
	printf("init\n");
	return ST_RX;
}

int action_rx(const struct fsm_T *fsm, void *ptr)
{
	printf("rx\n");
	return ST_TX;
}

int action_tx(const struct fsm_T *fsm, void *ptr)
{
	printf("tx\n");
	return ST_RX;
}

int entry_action_rx(const struct fsm_T *fsm, void *ptr)
{
	printf("entry rx\n");
	return 0;
}

struct fsm_T fsm;

int main()
{
	int i;
	fsm_init(&fsm, actions, entry_actions, FSM_NO_ACTIONS, N_STATES, ST_INIT);
	for(i = 0; i < 10; i++)
	{
		fsm_step(&fsm, 0);
	}
	return 0;
}

