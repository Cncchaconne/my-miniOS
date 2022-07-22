// kernel visual memory

#include "types.h"
#include "riscv.h"
#include "memory.h"
#include "defs.h"

pagetable_t kernel_pagetable;

extern char etext[]; // kerbel.ld sets the name to mappings

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

    kpgtbl = (pagetable_t)kalloc(); 
    // init the kernel page table
    memset(kpgtbl, 0, PGSIZE);

    // mapping the memory from some memory
    // mapping the uart base address
    // Hardware addresses are equi-mapped
    mapping(kpgtbl, UART_BASE, UART_BASE, PGSIZE, PTE_R | PTE_W);

    // mapping the kernel base address
    mapping(kpgtbl, KERNEL_BASE, KERNEL_BASE, (uint64)etext - KERNEL_BASE, PTE_R | PTE_X);

    // mapping kernel data and the physical ram we'll use
    mapping(kpgtbl, (uint64)etext, (uint64)etext, PHYSTOP - (uint64)etext, PTE_R | PTE_W);
    return kpgtbl;
}

void kvminithart()
{
    write_satp(MAKE_SATP(kernel_pagetable));
    sfence_vma();
}

// to mapping the memory that the physical address to visual address
// by creating a pte
// pa : physical address
// va : visual address
int mapping(pagetable_t pagetable, uint64 pa, uint64 va, uint64 size, int pte_param)
{
    // size == 0 error
    if(size == 0)
    {
        printf("mapping:size\n");
        return 0;
    }

    uint64 first, last;
    first = PGROUNDDOWN(va);
    last = PGROUNDDOWN(va + size - 1);

    // mapping the physical address and write it to the pte
    pte_t *pte;
    while(1)
    {
        if((pte = walk(pagetable, first, 1)) == 0)
            return -1;

        // wirte some para to the pte
        *pte = PA2PTE(pa) | pte_param | PTE_V;
        if(first == last)
            break;
        
        first += PGSIZE;
        pa += PGSIZE;
    }
    return 0;
}

// searching in from pte to something else
// va : visual address
// alloc : if alloc not zero, alloc the physical memory
pte_t *walk(pagetable_t pagetable, uint64 va, int alloc)
{
    // three level pagetable tree  
    for(int level = 2; level > 0; level--)
    {
        // get the pte from pagetable
        pte_t *pte = &pagetable[indices(va, level)];

        // pte vaild
        if(*pte & PTE_V)
        {
            // pagetable is a pointer which is point 
            // to the first of the physical page
            pagetable = (pagetable_t)PTE2PA(*pte);
        }
        else
        {
            // if don't have the pagetable
            // alloc it
            if(alloc == 0 || (pagetable = (pagetable_t)kalloc()) == 0)
            {
                return 0;
            }
            memset(pagetable, 0, PGSIZE);

            // make the pte vaild
            *pte = PA2PTE(pagetable) | PTE_V;
        }
    }

    // return the pte which we find
    return &pagetable[indices(va, 0)];
}