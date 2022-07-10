// define kernel function here 

#ifndef DEFS_H
#define DEFS_H

#include "types.h"

// printf.c
void printinit();
void temporaryPrint(char *str);
void printf(const char *fmt, ...);

// string.c
void *memset(void *str, int c, uint n);
int strlen(const char *s);

#endif