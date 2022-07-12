// Physical memory allocator,
// page-table pages

#include "types.h"
#include "spinlock.h"
#include "defs.h"
#include "memory.h"

extern char end[];
void initlist(void *physical_start, void *physical_end);

// Manage physical memory with a physical paging linked list
struct pageNode
{
    struct pageNode *next;
};

struct
{
    struct spinlock alloclock;
    struct pageNode *freelist;
} kmem;

void kinit()
{
    initlock(&kmem.alloclock);
    initlist(end, (void *)PHYSTOP);
}

// use kfree to add the free page to the list
void initlist(void *physical_start, void *physical_end)
{
    char *p;
    // must memory alignment up
    p = (char*)PGROUNDUP((uint64)physical_start);
    for (; p + PGSIZE <= (char *)physical_end; p += PGSIZE)
        kfree(p);
}

// pa : physical address
// free just add the free page node
// at the head of the list.
void kfree(void *physical_address)
{
    struct pageNode *ret;

    // check the list is or not out of the range

    // (uint64)physical_address % PGSIZE) != 0
    // mean the physical_address must be the integer times of page size

    // (char *)physical_address < end mean that physical_adress must after the kernel
    //
    if (((uint64)physical_address % PGSIZE) != 0 || (char *)physical_address < end || (uint64)physical_address >= PHYSTOP)
        return;

    memset(physical_address, 0, PGSIZE);

    ret = (struct pageNode *)physical_address;

    // lock out this opertaion
    acquire(&kmem.alloclock);
    ret->next = kmem.freelist;
    kmem.freelist = ret;
    release(&kmem.alloclock);
}

// alloc the physical memory
// Allocate one 4096-byte page of physical memory
// return a pointer that the kernel can use
void *kalloc(void)
{
    struct pageNode *ret;

    // pick up the first page to the user process
    acquire(&kmem.alloclock);
    ret = kmem.freelist;
    if(ret)
        kmem.freelist = ret->next;
    release(&kmem.alloclock);

    if(ret)
        memset((char *)ret, 1, PGSIZE);
    return (void *)ret;
}