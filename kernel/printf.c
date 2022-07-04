#include "defs.h"
#include "uart.h"

void temporaryPrint(char *str)
{
    uartinit();
    for (int i = 0; str[i] != '\0'; i++)
    {
        uartputc((int)str[i]);
    }
}