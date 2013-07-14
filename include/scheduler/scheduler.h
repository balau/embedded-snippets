#ifndef SCHEDULER_H
#define SCHEDULER_H

int schedule_at(unsigned time, void (*task)(void *), void *context);

void scheduler_init(void);
void scheduler_run(unsigned current_time);

#endif /* SCHEDULER_H */

