#ifndef PROC_H
#define PROC_H

// this is the define of process

#include "types.h"
#include "spinlock.h"

#define NPROC 64        // maximun number of process

// Per-CPU state
// Per-CPU information
struct cpu
{
    struct proc *proc; // The Process running on this cpu, or null
};

enum procstate
{
    UNUSED,
    USED,
    SLEEPING,
    RUNNABLE,
    RUNNING,
    ZOMBIE
};

// each process state
struct proc
{
    struct spinlock lock;

    enum procstate state; // Process state

    int killed; // if non-zero, have been killed
    int pid;    // Process ID

    struct proc *parent; // Parent process

    uint64 kstack;        // Virtual address of kernel stack address
};

#endif