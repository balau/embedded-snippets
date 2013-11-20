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

#include "fsm.h"

void fsm_init(
		struct fsm_T *fsm,
		const fsm_action_T *actions,
		const fsm_action_T *entry_actions,
		const fsm_action_T *exit_actions,
		unsigned int n_states, int init_state)
{
	fsm->state = init_state;
	fsm->last_state = FSM_INVALID_STATE;
	fsm->n_states = n_states;
	fsm->actions = actions;
	fsm->entry_actions = entry_actions;
	fsm->exit_actions = exit_actions;
}

void fsm_reset(struct fsm_T *fsm, int init_state)
{
	fsm->state = init_state;
	fsm->last_state = FSM_INVALID_STATE;
}

int fsm_get_state(const struct fsm_T *fsm)
{
	return fsm->state;
}

int fsm_get_last_state(const struct fsm_T *fsm)
{
	return fsm->last_state;
}

int fsm_step(struct fsm_T *fsm, void *ptr)
{
	int cur_state;
	int next_state;
	int return_val;

	cur_state = fsm->state;
	next_state = cur_state;
	
	if((cur_state < 0) || (((unsigned int)cur_state) >= fsm->n_states))
	{
		return_val = FSM_INVALID_STATE;		
	}
	else
	{
		fsm_action_T action;

		action = fsm->actions[cur_state];
		if(action == (fsm_action_T)0)
		{
			return_val = FSM_INVALID_ACTION;
		}
		else
		{
			next_state = action(fsm, ptr);
			if((next_state < 0) || (((unsigned int)next_state) >= fsm->n_states))
			{
				return_val = FSM_INVALID_NEXT_STATE;
				next_state = cur_state;
			}
			else
			{
				return_val = next_state;
			}
		}
		
		if(next_state != cur_state)
		{
			if(fsm->exit_actions != FSM_NO_ACTIONS)
			{
				fsm_action_T exit_action;

				exit_action = fsm->exit_actions[cur_state];
				if(exit_action != FSM_NO_ACTION)
				{
					(void)exit_action(fsm, ptr);
				}
			}

			fsm->last_state = cur_state;
			fsm->state = next_state;

			if(fsm->entry_actions != FSM_NO_ACTIONS)
			{
				fsm_action_T entry_action;
				entry_action = fsm->entry_actions[next_state];
				if(entry_action != FSM_NO_ACTION)
				{
					(void)entry_action(fsm, ptr);
				}
			}
			
		}
		else
		{
			fsm->last_state = cur_state;
		}
	}
	return return_val;
}

