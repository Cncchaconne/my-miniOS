// physical memory layout
// you can see more detail in virt/riscv64-virt.dts

#ifndef MEMORY_H
#define MEMORY_H

// this is the UART start address from memory
#define UART_BASE 0x10000000L

// core local interrupte (CLINT), which contains the timer
#define CLINT 0x2000000L
// MTIME = mechine time compare
// when mtime >= mtimecmp generated interrupt
#define CLINT_MTIMECMP(hartid)  (CLINT + 0x4000 + 8*(hartid))
#define CLINT_MTIME (CLINT + 0xBFF8)

// the -kernel option put the kernel in the 0x80000000L
// the -m 128M option make this machine has 128M memory
#define KERNEL_BASE 0x80000000L
#define PHYSTOP (KERNEL_BASE + 128 * 1024 * 1024)

// map the trampoline page to the highest address
// this is the kernel visual address
// the last page is uesd to the trampoline 
#define TRAMPOLINE  (MAXVA - PGSIZE)

// map the kernel stacks beneath the trampoline
// each surrounded by invalid guard pages
// you can see more detail in xv6 book page table
#define KSTACK(p)   (TRAMPOLINE - ((p) + 1) * 2 * PGSIZE)

#define TRAPFRAME (TRAMPOLINE - PGSIZE)

#endif