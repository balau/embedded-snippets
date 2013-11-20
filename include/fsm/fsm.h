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


#ifndef FSM_H
#define FSM_H

struct fsm_T;

typedef int (*fsm_action_T)(const struct fsm_T *, void *);

struct fsm_T
{
	int state;
	int last_state;
	unsigned int n_states;
	const fsm_action_T *actions;
	const fsm_action_T *entry_actions;
	const fsm_action_T *exit_actions;
};

enum fsm_errors
{
	FSM_INVALID_STATE = -1,
	FSM_INVALID_ACTION = -2,
	FSM_INVALID_NEXT_STATE = -3,
};

#define FSM_NO_ACTION  ((void *)0)
#define FSM_NO_ACTIONS ((void *)0)

void fsm_init(
		struct fsm_T *fsm,
		const fsm_action_T *actions,
		const fsm_action_T *entry_actions,
		const fsm_action_T *exit_actions,
		unsigned int n_states, int init_state);

void fsm_reset(struct fsm_T *fsm, int init_state);

int fsm_step(struct fsm_T *fsm, void *ptr);

int fsm_get_state(const struct fsm_T *fsm);

int fsm_get_last_state(const struct fsm_T *fsm);

#endif

