// some operation of register of riscv
// use inline assemble to operator the riscv register

#ifndef RISCV_H
#define RISCV_H

#include "types.h"

// read mhartid to find out which core is used.
// csrr : read the status register and store the value.
// mhartid : a register which store the CPU id.
static inline uint64 read_mhartid()
{
    uint64 x;
    asm volatile("csrr %0, mhartid"
                 : "=r"(x));
    return x;
}

// Machine Status Register, mstatus
// at first your machine is in machine status
// mstatus store many status

#define MSTATUS_MIE     (1L << 3)    

static inline uint64 read_mstatus()
{
    uint64 x;
    asm volatile("csrr %0, mstatus"
                 : "=r"(x));
    return x;
}

static inline void write_mstatus(uint64 x)
{
    asm volatile("csrw mstatus, %0"
                 :
                 : "r"(x));
}

// mepc register store the Except call

static inline void write_mepc(uint64 x)
{
    asm volatile("csrw mepc, %0"
                 :
                 : "r"(x));
}

#endif