#include "uart.h"
#include "defs.h"
#include "riscv.h"

#define DEBUG 0

#define CPUS 4

__attribute__((aligned(16))) char stack0[4096 * CPUS];

// the start() function jump here.
// and change the M model to S mode
void main()
{
    if (read_mhartid() == 0)
    {
        uint64 x = read_mstatus();
        x &= MSTATUS_MPP_MASK;
        if(x == MSTATUS_MPP_S)
        {
            temporaryPrint("Supervisor mode\n");
        }
        while (1)
        {
        }
    }
    else
    {
        while (1)
        {
        }
    }
}