// physical memory layout
// you can see more detail in virt/riscv64-virt.dts

#ifndef MEMORY_H
#define MEMORY_H

// the -kernel option put the kernel in the 0x80000000L
// the -m 128M option make this machine has 128M memory
#define KERNEL_BASE 0x80000000L
#define PHYSTOP (KERNEL_BASE + 128 * 1024 * 1024)



#endif