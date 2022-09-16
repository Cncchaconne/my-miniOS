// process opeate

#include "riscv.h"
#include "proc.h"
#include "memory.h"

// use a array to manage the process
// named the proc table
struct proc proc[NPROC];

// initaialize the proc table
// set the state unused
// copy the kernel stack visual address to uint64 kstack
void procinit()
{
    struct proc *p;
    for(int i = 0; i < NPROC; i++)
    {
        p = &proc[i];
        p->state = UNUSED;
        p->kstack = KSTACK((int)i);
    }
}


// return the id which CPU is used
int cpuid()
{
    int id = read_tp();
    return id;
}