#ifndef PROC_H
#define PROC_H

// this is the define of process

#include "types.h"
#include "spinlock.h"

// Per-CPU state
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
};

#endif