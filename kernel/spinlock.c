#include "spinlock.h"

void initSpinlock(struct spinlock *lock)
{
    lock->locked = 0;
}

void acquire(struct spinlock *lock)
{
    while (__sync_lock_test_and_set(&lock->locked, 1) != 0)
        ;
}

void release(struct spinlock *lock)
{
    __sync_lock_release(&lock->locked);
}