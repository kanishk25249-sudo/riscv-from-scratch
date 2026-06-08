#include "process.h"
#include "mem.h"

struct process procs[NPROC];
int nextpid = 1;

void proc_init(void) {
    for (int i = 0; i < NPROC; i++) {
        procs[i].state = 0;
        procs[i].pid = 0;
    }
}

struct process* proc_create(unsigned int entry) {
    for (int i = 0; i < NPROC; i++) {
        if (procs[i].pid == 0) {
            procs[i].pid = nextpid;
            nextpid++;
            procs[i].pc = entry;
            void* stack = kalloc();
            procs[i].sp = (unsigned int)stack + 4096;
            procs[i].regs[2] = procs[i].sp;
            procs[i].state = 1;
            return &procs[i];
        }
    }
    return 0;
}