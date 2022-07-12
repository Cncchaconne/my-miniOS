#include <stdarg.h>

#include "defs.h"
#include "uart.h"
#include "spinlock.h"

struct spinlock printlock;

static struct
{
    struct spinlock lock;
    int locking;
} pr;

// qemu simulator don't need to init the device
void printinit()
{
    uartinit();
    initlock(&pr.lock);
    pr.locking = 1;
}

// print something temporary
void temporaryPrint(char *str)
{
    int locking;
    locking = pr.locking;

    if (locking)
        acquire(&pr.lock);

    for (int i = 0; str[i] != '\0'; i++)
    {
        uartputc((int)str[i]);
    }

    if (locking)
        release(&pr.lock);
}

static char numbers[] = "0123456789abcdef";

// the assist function for printint function
static int abs(int num)
{
    if (num >= 0)
        return num;
    else
        return -num;
}

static void printint(int num, int base)
{
    char buf[16];
    int flag = 0;

    if (num < 0)
    {
        num = abs(num);
        flag = 1;
    }

    // i is the flag of the buf
    // use do-while to avoid the 0 status
    int i = 0;
    do
    {
        buf[i] = numbers[num % base];
        i++;
        num = num / base;
    } while (num != 0);

    if (flag)
        buf[i++] = '-';

    // after finish, i always ++
    // and we must sub 1 for the correct i.
    i -= 1;

    while (i >= 0)
    {
        uartputc(buf[i]);
        i--;
    }
}

// Uncertain parameters programing
// the implement of the kernel output
// to the screen directly
// now is understand %d %x %s
void printf(const char *fmt, ...)
{
    va_list ap;

    // s is a pointer of %s output
    char *s;

    // lock to avoid interleaving concurrent printf's.
    int locking;
    locking = pr.locking;

    if (locking)
        acquire(&pr.lock);

    if (fmt == 0)
    {
        return;
    }

    // init va_list
    va_start(ap, fmt);

    int c;
    for (int i = 0; (c = fmt[i] & 0xff) != 0; i++)
    {
        if (c != '%')
        {
            uartputc(c);
            continue;
        }

        c = fmt[++i] & 0xff;
        if (c == 0)
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
        case 's':
            if ((s = va_arg(ap, char *)) == 0)
                s = "(null)";
            for (; *s; s++)
                uartputc((int)*s);
            break;
        default:
            break;
        }
    }

    if (locking)
        release(&pr.lock);
}