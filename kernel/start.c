#include "riscv.h"
#include "types.h"
#include "defs.h"

void main();

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

    // write each CPU's hartid in its tp register for read
    int id = read_mhartid();
    write_tp((uint64)id);
    // the hardware behavior when we use mret
    // 1. set the pc to the register mepc point to.
    // 2. set the privilege mode to mpp where mstatus stored/
    asm volatile("mret");
}


// init timer interrupt
void timeinit()
{

}