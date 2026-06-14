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
    int current_idx = 0;
    for (int i = 0; i < NPROC; i++) {
        if (&procs[i] == current) {
            current_idx = i;
            break;
        }
    }

    for (int i = 1; i <= NPROC; i++) {
        int next_idx = (current_idx + i) % NPROC;
        if (procs[next_idx].state == 1) {
            current = &procs[next_idx];
            return current;
        }
    }

    return current;
}