#include "scheduler.h"
#include "process.h"

extern struct process procs[NPROC];
struct process* current = 0;

void scheduler_init(void) {
    for (int i = 0; i < NPROC; i++) {
        if (procs[i].state == 1) {
            current = &procs[i];
            return;
        }
    }
}

struct process* schedule(void) {
    if (current == &procs[0]) {
        current = &procs[1];
    } else {
        current = &procs[0];
    }
    return current;
}