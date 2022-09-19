#include "riscv.h"
#include "types.h"
#include "defs.h"
#include "memory.h"

#define NCPU 8  // maximun number of CPU

void main();
void timerinit();

// a scratch area pre CPU for machine-mode timer interrupts.
uint64 timer_scratch[NCPU][5];

// assembly code in kernelvec.S for machine-mode timer interrupt
extern void timervec();

void start()
{
    // mret is the return of the M mode
    // seet M Previous Privilege mode to Supervisor, for mret.
    unsigned long x = read_mstatus();
    x &= ~MSTATUS_MPP_MASK;
    x |= MSTATUS_MPP_S;
    write_mstatus(x);

    // set the Program Couunter to main, for mert.
    // request -mcmodel=medany
    // generate some code for the medium-any code model.
    write_mepc((uint64)main);

    // disable page table now
    write_satp(0);

    // give supervisor mode to access the physical memory
    // this number is 54 bits
    write_pmpaddr0(0x3fffffffffffffull);
    // pmp config register
    write_pmpcfg0(0xf);

    // ask for clock interrupts.
    timerinit();

    // write each CPU's hartid in its tp register for read
    int id = read_mhartid();
    write_tp((uint64)id);
    // the hardware behavior when we use mret
    // 1. set the pc to the register mepc point to.
    // 2. set the privilege mode to mpp where mstatus stored/
    asm volatile("mret");
}

// init timer interrupt in mechine mode
void timerinit()
{
    // each CPU has a separate source of timer interrupts.
    int id = read_mhartid();

    // ask the CLINT for a timer interrupt.
    int interval = 1000000; // cycles; about 1/10th second
    *(uint64 *)CLINT_MTIMECMP(id) = *(uint64 *)CLINT_MTIME + interval;

    // prepare information in scratch[] for timervec.Just like user trap
    // scratch[0..2] : space for timervec to save registers.
    // scratch[3] : address of CLINT MTIMECMP register.
    // scratch[4] : desired interval (in cycles) between timer interrupts.
    uint64 *scratch = &timer_scratch[id][0];
    scratch[3] = CLINT_MTIMECMP(id);
    scratch[4] = interval;
    write_mscratch((uint64)scratch);

    // set the machine-mode trap handler.
    write_mtvec((uint64)timervec);

    // enable machine-mode interrupts.
    write_mstatus(read_mstatus() | MSTATUS_MIE);

    // enable machine-mode timer interrupts.
    write_mie(read_mie() | MIE_MTIE);
}