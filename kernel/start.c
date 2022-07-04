#include "riscv.h"
#include "types.h"
#include "defs.h"

void main();

void start()
{
    temporaryPrint("Here is in the start function\n");
    // mret is the return of the M mode
    asm volatile("call main");
}