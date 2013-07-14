#include "scheduler.h"

void task1(int *context)
{
    *context = *context + 1;
}

int a;
unsigned cur_time;

int main()
{
    
    a = 0;
    cur_time = 0;

    scheduler_init();

    schedule_at(10, task1, &a);
    while(a == 0)
    {
        scheduler_run(cur_time);
        cur_time++;
    }
    return 0;
}

