// define kernel function here 

#ifndef DEFS_H
#define DEFS_H

#include "types.h"
#include "riscv.h"

// physical memory alloc
// kalloc.c
void kinit();
void kfree(void *physical_address);
void *kalloc(void);

// printf.c
void printinit();
void temporaryPrint(char *str);
void printf(const char *fmt, ...);

// string.c
void *memset(void *str, int c, uint n);
int strlen(const char *s);

// kernel visual memory alloc and mapping
// kvm.c
void kvminit();
pagetable_t kvmmake();
void kvminithart();
int mapping(pagetable_t pagetable, uint64 pa, uint64 va, uint64 size, int pte_param);
pte_t *walk(pagetable_t pagetable, uint64 va, int alloc);

#endif