#ifndef PROCESS_H
#define PROCESS_H

#define NPROC 10

struct process {
    unsigned int regs[32];
    unsigned int pc;
    unsigned int sp;
    int pid;
    char state;
};

void proc_init(void);
struct process* proc_create(unsigned int entry);

#endif