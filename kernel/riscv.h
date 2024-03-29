// some operation of register of riscv
// use inline assemble to operator the riscv register
// hardware therad is the name of (hart)

#ifndef RISCV_H
#define RISCV_H

// to include some constant to asm but not include function
#ifndef __ASSEMBLER__

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

// Machine-mode Interrupte Enable
#define MIE_MEIE (1L << 11) // external
#define MIE_MTIE (1L << 7)  // timer
#define MIE_MSIE (1L << 3)  // software

// machine interrupt register (mip and mie)
static inline uint64 read_mie()
{
    uint64 x;
    asm volatile("csrr %0, mie"
                 : "=r"(x));
    return x;
}

static inline void write_mie(uint64 x)
{
    asm volatile("csrw mie, %0"
                 :
                 : "r"(x));
}

// machine mode scratch register
// used to stored other register when it is interrupt
static inline void write_mscratch(uint64 x)
{
    asm volatile("csrw mscratch, %0"
                 :
                 : "r"(x));
}

// machine mode timer interrupt
static inline void write_mtvec(uint64 x)
{
    asm volatile("csrw mtvec, %0"
                 :
                 : "r"(x));
}

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
// this register is used to be control the page
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

// flush the TLB
static inline void sfence_vma()
{
    // zero means flush all TLB
    // TLB is a cache must maintain consistency with the page table
    asm volatile("sfence.vma zero, zero");
}

#endif // __ASSEMBLER__

// memory setting
#define PGSIZE 4096 // bytes per page
#define PGSHIFT 12  // bits of offset with a page

// use riscv sv39 page table scheme
// when stap mask == 8 mean that use sv39
#define SATP_SV39 (8L << 60)

// memory alignment up or down
// The address offset is rounded and aligned
// search from internet
// magic algorithm
#define PGROUNDUP(a) (((a) + PGSIZE - 1) & ~(PGSIZE - 1))
#define PGROUNDDOWN(a) (((a)) & ~(PGSIZE - 1))

// PTE
#define PTE_V (1L << 0) // valid
#define PTE_R (1L << 1) // read
#define PTE_W (1L << 2) // write
#define PTE_X (1L << 3) // executable
#define PTE_U (1L << 4) // user can access
// there some appointer for the value of the register
// if R,W,X == 0 than this PTE point to next PTE

#ifndef __ASSEMBLER__

// define the data of pte and pagetable
typedef uint64 pte_t; // 64bits
// the size of a page table is the same of a physical page
typedef uint64 *pagetable_t; // have 512 ptes

#endif // __ASSEMBLER__

// use SV39 theme to the address
#define SATP_SV39 (8L << 60)

// enable paging
#define MAKE_SATP(pagetable) (SATP_SV39 | (((uint64)pagetable) >> 12))

#ifndef __ASSEMBLER__
// get the 9 bits of the page number from the visual address
// va : visual address
static inline uint64 indices(uint64 va, int level)
{
    // 9 bits
    uint64 mask = 0x1FF;

    // calculate the shift of the level
    int shift = PGSHIFT + (9 * level);

    // return the 9 bits of number
    va = va >> shift;
    va &= mask;

    return va;
}
#endif // __ASSEMBLER__

// pte to physical address
// the 10 bits of pte
// must input pte_t pte
#define PTE2PA(pte) (((pte) >> 10) << 12)

// physical address to pte
// pa : physical address
#define PA2PTE(pa) ((((uint64)pa) >> 12) << 10)

// Sv39 the max visual address (39bits)
#define MAXVA (1L << (9 + 9 + 9 + 12 - 1))

#endif