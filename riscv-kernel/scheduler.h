#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

extern struct process* current;

void scheduler_init(void);
struct process* schedule(void);

#endif