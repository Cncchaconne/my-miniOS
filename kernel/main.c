#include "uart.h"

#define CPUS 8

__attribute__((aligned(16))) char stack0[4096 * CPUS];

int main()
{
    char p = 'h';
    uartinit();
    uartputc(p);
    char i = 'i';
    uartputc(i);
    while(1)
    {

    }
}