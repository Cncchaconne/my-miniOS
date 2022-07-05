#include "riscv.h"
#include "types.h"
#include "defs.h"

void main();

void start()
{
    // mret is the return of the M mode
    temporaryPrint("Here is in the start function\n");
    asm volatile("call main");
}