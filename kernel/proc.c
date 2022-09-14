// process opeate

#include "riscv.h"

// return the id which CPU is used
int cpuid()
{
    int id = read_tp();
    return id;
}