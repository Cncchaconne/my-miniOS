#include <stdarg.h>

#include "defs.h"
#include "uart.h"
#include "spinlock.h"

struct spinlock printlock;

// qemu simulator don't need to init the device
void printinit()
{
    uartinit();
    initSpinlock(&printlock);
}

void temporaryPrint(char *str)
{
    acquire(&printlock);
    for (int i = 0; str[i] != '\0'; i++)
    {
        uartputc((int)str[i]);
    }
    release(&printlock);
}

static char numbers[] = "0123456789abcdef";

static int abs(int num)
{
    if(num>=0)
        return num;
    else
        return -num;
}

static void printint(int num, int base)
{
    char buf[16];
    num = abs(num);
}

// Uncertain parameters programing
int printf(const char *fmt, ...)
{
    va_list ap;

    if(fmt == 0)
    {
        return 0;
    }

    // init va_list
    va_start(ap, fmt);    

    int c;
    for(int i = 0; (c = fmt[i] & 0xff) !=0; i++)
    {
        if(c != '%')
        {
            uartputc(c);
            continue;
        }

        c = fmt[++i] & 0xff;
        if(c == 0)
        {
            break;
        }

        switch (c)
        {
        case 'd':
            printint(va_arg(ap, int), 10);
            break;
        case 'x':
            printint(va_arg(ap, int), 16);
            break;
        default:
            break;
        }
    }
}