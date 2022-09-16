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
    if (cpuid() == 0)
    {
        printinit();
        printf("This is the main function\n");
        int id = cpuid();
        printf("The hart id == %d\n", id);
        kinit();
        kvminit();
        kvminithart();
        procinit();
        started = 1;
    }
    else
    {
        while (started == 0)
            ;

        char hello[] = "This is other hart!\n";
        printf("%s", hello);
        int id = cpuid();
        printf("The hart id == %d\n", id);
    }

    while (1)
        ;
}