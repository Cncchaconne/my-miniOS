// kernel visual memory

#include "types.h"
#include "riscv.h"
#include "memory.h"

pagetable_t *kernel_pagetable;

// init the kernel visual memory pagetable
void kvminit()
{
    kernel_pagetable = kvmmake();
}

// kernel pagetable make
// to gengerate a kernel table to kvminit
pagetable_t kvmmake()
{
    // new a kernel table to return. avoid malloc
    pagetable_t kpgtbl;
    
    // mapping the memory from some memory

    // to implement.
    return kpgtbl;
}

// to mapping the memory that the physical address to visual address
// by creating a pte
// pa : physical address
// va : visual address
int mapping(pagetable_t pagetable, uint64 pa, uint64 va, int pte_param)
{
    // to implememt.
}

// searching in from pte to something else
// va : visual address
pte_t *traverse(pagetable_t pagetable, uint64 va)
{
    // to implememt.
}