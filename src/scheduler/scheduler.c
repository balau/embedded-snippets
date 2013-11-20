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

#include "scheduler.h"
#include "stdlib.h"

struct task_T
{
    unsigned time;
    void (*task)(void *);
    void *context;
    struct task_T *next;
};

#define NULL_TASK ((void (*)(void *))0)
#define INVALID_TASK_IDX (-1)
#define N_SCHEDULED_TASKS 16

static struct task_T scheduled_tasks[N_SCHEDULED_TASKS];
static int scheduled_tasks_head;
static int scheduled_tasks_last_free;

static int get_free_task(void)
{
    return INVALID_TASK_IDX;
}

int schedule_at(unsigned time, void (*task)(void *), void *context)
{
    int free;
    free = get_free_task();
    if(free != INVALID_TASK_IDX)
    {
        //...
        return 0;
    }
    else
    {
        return 1;
    }
}

void scheduler_init(void)
{
    unsigned i_task;
    for(i_task = 0; i_task < N_SCHEDULED_TASKS; i_task++)
    {
        scheduled_tasks[i_task].task = NULL_TASK;
    }
    scheduled_tasks_head = INVALID_TASK_IDX;
    scheduled_tasks_last_free = INVALID_TASK_IDX;
}

void scheduler_run(unsigned current_time)
{    
    if(scheduled_tasks_head != INVALID_TASK_IDX)
    {
        if((int)scheduled_tasks[scheduled_tasks_head].time - (int)current_time < 0)
        {
            //...
        }
    }
}

