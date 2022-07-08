#include "defs.h"
#include "uart.h"
#include "spinlock.h"

struct spinlock printlock;

void temporaryPrint(char *str)
{
    uartinit();
    initSpinlock(&printlock);
    acquire(&printlock);
    for (int i = 0; str[i] != '\0'; i++)
    {
        uartputc((int)str[i]);
    }
    release(&printlock);
}