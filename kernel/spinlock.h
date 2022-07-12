#ifndef SPINLOCK_H
#define SPINLOCK_H

#include "types.h"
#include "riscv.h"

// spinlock usually used in the kernel process

struct spinlock{
    uint locked;
};

// init the lock
void initlock(struct spinlock *lock);

// Acquire the lock
void acquire(struct spinlock *lock);

// Release the lock
void release(struct spinlock *lock);

#endif