#ifndef MEM_H
#define MEM_H

void mem_init(void);
void* kalloc(void);
void kfree(void* page);

#endif