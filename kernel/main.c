#include "uart.h"
#include "defs.h"
#include "riscv.h"

#define DEBUG 0

#define CPUS 4

__attribute__((aligned(16))) char stack0[4096 * CPUS];

volatile static int started = 0;

// the start() function jump here.
// and change the M model to S mode
void main()
{

    if (read_mhartid() == 0)
    {
        printinit();
        temporaryPrint("This is main function!\n");
        printf("This is the printf output!\n");
        uint64 x = read_mstatus();
        x &= MSTATUS_MPP_MASK;
        if (x == MSTATUS_MPP_S)
        {
            temporaryPrint("main hart run in supervisor mode\n");
        }
        int id = read_mhartid();
        printf("The hart id == %d\n", id);
        started = 1;
    }
    else
    {
        while (started == 0)
            ;

        char hello[] = "This is other hart!\n";
        printf("%s", hello);
        int id = read_mhartid();
        printf("The hart id == %d\n", id);
    }

    while (1)
        ;
}