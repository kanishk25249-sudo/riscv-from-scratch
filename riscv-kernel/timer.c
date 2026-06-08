#include "timer.h"

#define MTIME      0x200BFF8
#define MTIMECMP   0x2004000
#define INTERVAL   100000

void timer_init(void) {
    *(unsigned long long*)MTIMECMP = *(unsigned long long*)MTIME + INTERVAL;
    unsigned int mie;
    asm volatile("csrr %0, mie" : "=r"(mie));
    mie |= (1 << 7);
    asm volatile("csrw mie, %0" : : "r"(mie));

    unsigned int mstatus;
    asm volatile("csrr %0, mstatus" : "=r"(mstatus));
    mstatus |= (1 << 3);
    asm volatile("csrw mstatus, %0" : : "r"(mstatus));
}
    
void timer_reset(void) {
    *(unsigned long long*)MTIMECMP = *(unsigned long long*)MTIME + INTERVAL;
}
