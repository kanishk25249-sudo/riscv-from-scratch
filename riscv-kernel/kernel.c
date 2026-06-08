#include "uart.h"
#include "mem.h"
#include "process.h"
#include "scheduler.h"
#include "timer.h"

extern void trap_handler(void);
extern void jump_to_process(struct process* p);

void process_a(void) {
    while (1) {
        uart_puts("A\n");
        for (volatile int i = 0; i < 500000; i++);
    }
}

void process_b(void) {
    while (1) {
        uart_puts("B\n");
        for (volatile int i = 0; i < 500000; i++);
    }
}

void c_kernel_main() {
    uart_puts("=== KERNEL BOOTING ===\n");

    mem_init();
    uart_puts("[MEM] initialized\n");

    void* p1 = kalloc();
    uart_puts("[MEM] kalloc p1: "); uart_puthex((unsigned int)p1); uart_putc('\n');

    void* p2 = kalloc();
    uart_puts("[MEM] kalloc p2: "); uart_puthex((unsigned int)p2); uart_putc('\n');

    kfree(p1);
    uart_puts("[MEM] kfree p1\n");

    void* p3 = kalloc();
    uart_puts("[MEM] kalloc p3 (should be p1): "); uart_puthex((unsigned int)p3); uart_putc('\n');

    kfree(p2);
    kfree(p3);

    proc_init();
    uart_puts("[PROC] initialized\n");

    struct process* proc1 = proc_create((unsigned int)process_a);
    uart_puts("[PROC] PID: "); uart_putint(proc1->pid);
    uart_puts(" PC: "); uart_puthex(proc1->pc);
    uart_puts(" SP: "); uart_puthex(proc1->sp); uart_putc('\n');

    struct process* proc2 = proc_create((unsigned int)process_b);
    uart_puts("[PROC] PID: "); uart_putint(proc2->pid);
    uart_puts(" PC: "); uart_puthex(proc2->pc);
    uart_puts(" SP: "); uart_puthex(proc2->sp); uart_putc('\n');

    scheduler_init();
    uart_puts("[SCHED] current PID: "); uart_putint(current->pid); uart_putc('\n');

    asm volatile("csrw mtvec, %0" : : "r"(trap_handler));
    uart_puts("[TRAP] mtvec set\n");

    timer_init();
    uart_puts("[TIMER] initialized\n");

    uart_puts("=== JUMPING TO PROCESS A ===\n");
    jump_to_process(current);
}