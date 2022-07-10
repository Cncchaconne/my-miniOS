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

    // the hardware behavior when we use mret
    // 1. set the pc to the register mepc point to.
    // 2. set the privilege mode to mpp where mstatus stored/
    asm volatile("call main");
}


// init timer interrupt
void timeinit()
{

}