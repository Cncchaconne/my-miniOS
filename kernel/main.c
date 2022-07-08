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

    temporaryPrint("Here is in the main function\n");
    if (read_mhartid() == 0)
    {
        temporaryPrint("Start init\n");
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