#include "uart.h"
#include "mem.h"
#include "process.h"
#include "scheduler.h"
#include "timer.h"
#include "prog_bin.h"

extern char _user_program_start[];
extern char _user_program_end[];

extern void trap_handler(void);
extern void jump_to_process(struct process* p);

static void* memcpy(void* dst, const void* src, unsigned int n) {
    char* d = (char*)dst;
    const char* s = (const char*)src;
    while (n--) *d++ = *s++;
    return dst;
}

void c_kernel_main() {
    uart_puts("=== KERNEL BOOTING ===\n");

    mem_init();
    uart_puts("[MEM] initialized\n");

    proc_init();
    uart_puts("[PROC] initialized\n");

    void* user_page = kalloc();
    memcpy(user_page, prog_bin, prog_bin_len);

    struct process* proc3 = proc_create((unsigned int)user_page);
    uart_puts("[PROC] PID: "); uart_putint(proc3->pid);
    uart_puts(" PC: "); uart_puthex(proc3->pc);
    uart_puts(" SP: "); uart_puthex(proc3->sp); uart_putc('\n');

    scheduler_init();
    uart_puts("[SCHED] current PID: "); uart_putint(current->pid); uart_putc('\n');

    asm volatile("csrw mtvec, %0" : : "r"(trap_handler));
    uart_puts("[TRAP] mtvec set\n");

    timer_init();
    uart_puts("[TIMER] initialized\n");

    uart_puts("=== JUMPING TO PROCESS1 ===\n");
    asm volatile("csrci mstatus, 8");
    jump_to_process(proc3);
}