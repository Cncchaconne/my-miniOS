// the implementation of uart ns16550a
// documemt https://www.lammertbies.nl/comm/info/serial-uart

#ifndef UART_H
#define UART_H

// add spinlock to the uart
#include "spinlock.h"
// move the UAET_BASE to memory.h to mamnge the
// hardware address mapping.
#include "memory.h"
// #define UART_BASE 0x10000000L

// the base address add some offset can visit the register
#define UART_RHR    0
#define UART_THR    0
#define UART_IER    1
#define UART_IIR    2
#define UART_FCR    2
#define UART_LCR    3
#define UART_MCR    4
#define UART_LSR    5
#define UART_MSR    6
#define UART_SCR    7    

#define UART_DLL    0
#define UART_DLM    1

// every bit of the register have different usage.
// you can find more information in document.
// define some operation number of the register
#define FCR_FIFO_ENABLE     (1 << 0)
#define FCR_FIFO_CLEAR      (3 << 1)

#define IER_RX_ENABLE       (1 << 0)
#define IER_TX_ENABLE       (1 << 1)



// register operation
// get the address of register
// volatile make sure that you can find the lastest register value
volatile unsigned char *Reg(int reg);
unsigned char ReadReg(int reg);
void WriteReg(int reg, unsigned char c);

// init uart. 
// Please read the document to find the magic number in this function  
void uartinit();

// I/O operation
void uartputc(int c);
int uartgetc();

#endif