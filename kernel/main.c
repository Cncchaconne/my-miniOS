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
    if (read_tp() == 0)
    {
        printinit();
        printf("This is the main function\n");
        printf("This is the printf output!\n");
        int id = read_tp();
        printf("The hart id == %d\n", id);
        kinit();
        kvminit();
        kvminithart();
        started = 1;
    }
    else
    {
        while (started == 0)
            ;

        char hello[] = "This is other hart!\n";
        printf("%s", hello);
        int id = read_tp();
        printf("The hart id == %d\n", id);
    }

    while (1)
        ;
}