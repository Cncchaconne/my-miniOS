#include "types.h"

void *memset(void *str, int c, uint n)
{
    char *temp;
    temp = (char *)str;
    for (int i = 0; i < n; i++)
    {
        temp[i] = c;
    }
    return str;
}

int strlen(const char *s)
{
    int len;
    for (len = 0; s[len]; len++)
        ;
    return len;
}