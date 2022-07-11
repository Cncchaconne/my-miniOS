// some operation of register of riscv
// use inline assemble to operator the riscv register
// hardware therad is the name of (hart)

#ifndef RISCV_H
#define RISCV_H

#include "types.h"

// machine mode operation

// read mhartid to find out which core is used.
// csrr : read the status register and store the value.
// mhartid : a register which store the CPU id.
// can not enter in supervisor mode
static inline uint64 read_mhartid()
{
    uint64 x;
    asm volatile("csrr %0, mhartid"
                 : "=r"(x));
    return x;
}

// Machine Status Register, mstatus
// at first your machine is in machine status
// mstatus store many status in machine status
// mstatus mpp[12:11] is two nits wide and decide the next mode
// User mode 00 Supervisor mode 01 machine mode 11

#define MSTATUS_MPP_MASK (3L << 11) // previous mode.
#define MSTATUS_MIE (1L << 3)
#define MSTATUS_MPP_M (3L << 11)
#define MSTATUS_MPP_S (1L << 11)
#define MSTATUS_MPP_U (0L << 11)

static inline uint64 read_mstatus()
{
    uint64 x;
    asm volatile("csrr %0, mstatus"
                 : "=r"(x));
    return x;
}

// csrw write the control and status register
static inline void write_mstatus(uint64 x)
{
    asm volatile("csrw mstatus, %0"
                 :
                 : "r"(x));
}

// mepc register store the Except call
// which return by mret
static inline void write_mepc(uint64 x)
{
    asm volatile("csrw mepc, %0"
                 :
                 : "r"(x));
}

// usually, the interrupts are processed in machine mode
// but sometimes, some interrupt are delegated to supervisor mode
// this two registes are used here.
// machine tarp delegation register (medeleg and mideleg)
// medeleg :: machine exception delegation
// mideleg :: machine interrupt delegation
static inline uint64 read_medeleg()
{
    uint64 x;
    asm volatile("csrr %0, medeleg"
                 : "=r"(x));
    return x;
}

static inline void write_medeleg(uint64 x)
{
    asm volatile("csrw medeleg, %0"
                 :
                 : "r"(x));
}

static inline uint64 read_mideleg()
{
    uint64 x;
    asm volatile("csrr %0, mideleg"
                 : "=r"(x));
    return x;
}

static inline void write_mideleg(uint64 x)
{
    asm volatile("csrw mideleg, %0"
                 :
                 : "r"(x));
}

// machine interrupt register (mip and mie)
// mip and mie are both

// machine timer registers
// they provide some timer in the machine

// PMP physical manage
static inline void write_pmpcfg0(uint64 x)
{
    asm volatile("csrw pmpcfg0, %0"
                 :
                 : "r"(x));
}

static inline void write_pmpaddr0(uint64 x)
{
    asm volatile("csrw pmpaddr0, %0"
                 :
                 : "r"(x));
}

// supervisor operation

// supervisor address translation and protection;
// satp register
static inline void write_satp(uint64 x)
{
    asm volatile("csrw satp, %0"
                 :
                 : "r"(x));
}

static inline uint64 read_satp()
{
    uint64 x;
    asm volatile("csrr %0, satp"
                 : "=r"(x));
    return x;
}

// read and wirte tp, the thread pointer, which hold
// this core's hartid(core number)
static inline uint64 read_tp()
{
    uint64 x;
    asm volatile("mv %0, tp"
                 : "=r"(x));
    return x;
}

static inline void write_tp(uint64 x)
{
    asm volatile("mv tp, %0"
                 :
                 : "r"(x));
}
// memory setting
#define PGSIZE 4096 // bytes per page
#define PGSHIFT 12  // bits of offset with a page

// memory alignment up or down
// The address offset is rounded and aligned
// search from internet
// magic algorithm
#define PGROUNDUP(a)    (((a) + PGSIZE - 1) & ~(PGSIZE - 1))
#define PGROUNDDOWN(a)  (((a)) & ~(PGSIZE-1))

// PTE 
#define PTE_V   (1L << 0)   // valid
#define PTE_R   (1L << 1)   // read
#define PTE_W   (1L << 2)   // write
#define PTE_X   (1L << 3)   
#define PTE_U   (1L << 4)   // user can access

#endif