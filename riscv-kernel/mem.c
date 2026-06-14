#include "mem.h"

#define PAGESIZE 4096
#define PHYMEM_START 0x80020000
#define PHYMEM_END   0x80100000

struct page {
    struct page* next;
};

static struct page* freelist = 0;

void mem_init(void) {
    struct page* p;
    char* addr = (char*)PHYMEM_START;
    
    while (addr + PAGESIZE <= (char*)PHYMEM_END) {
        p = (struct page*)addr;
        p->next = (struct page*)(addr + PAGESIZE);
        addr += PAGESIZE;
    }
    
    p->next = 0;
    freelist = (struct page*)PHYMEM_START;
}

void* kalloc(void) {
    struct page* p;
    if (freelist == 0) {
        return 0;
    }
    p = freelist;
    freelist = p->next;
    return (void*)p;
}

void kfree(void* page) {
    struct page* p = (struct page*)page;
    p->next = freelist;
    freelist = p;
}