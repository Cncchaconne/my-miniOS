#include "uart.h"
#include "defs.h"

#define DEBUG   0

#define CPUS    8

__attribute__((aligned(16))) char stack0[4096 * CPUS];

// the start() function jump here.
// and change the M model to S mode
void main()
{
    temporaryPrint("Here is in the main function\n");
    while (1)
    {
    }
}