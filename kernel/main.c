#include "uart.h"

#define CPUS 8

__attribute__((aligned(16))) char stack0[4096 * CPUS];

void temporaryPrint(char *str)
{
    uartinit();
    for (int i = 0; str[i] != '\0'; i++)
    {
        uartputc((int)str[i]);
    }
}

int main()
{
    temporaryPrint("hello, world\n");
    while (1)
    {
    }
}