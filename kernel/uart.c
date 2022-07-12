#include "uart.h"

struct spinlock uartlock;

// register operation improve efficiency
// use inline to
inline volatile unsigned char *Reg(int reg)
{
    return (volatile unsigned char *)(UART_BASE + reg);
}

// return the value of register
inline unsigned char ReadReg(int reg)
{
    return (*Reg(reg));
}

inline void WriteReg(int reg, unsigned char c)
{
    (*Reg(reg)) = c;
}

// uart init
// setting the start up value of the register
void uartinit()
{
    // disable interrupt
    WriteReg(UART_IER, 0x00);

    // set baud rate
    // DLAB is the first bit in the register of LCR
    // when the DLAB bit is 1. (0x80)
    // the RHR and the IER are used to seting baud rate
    WriteReg(UART_LCR, 0x80);

    // set the baud rate of 38.4K.
    // 0x03 and 0x00 are in document.
    WriteReg(UART_DLL, 0x03);
    WriteReg(UART_DLM, 0x00);

    // leave setting model and set word length to 8-bits
    WriteReg(UART_LCR, 0x03);

    // enable FIFOs
    // FIFOs can read or wirte more than one character.
    WriteReg(UART_FCR, FCR_FIFO_ENABLE | FCR_FIFO_CLEAR);

    // enable transmit and receive interrupts
    WriteReg(UART_IER, IER_RX_ENABLE | IER_TX_ENABLE);

    // init the uart spin lock
    initlock(&uartlock);
}

// I/O operation
void uartputc(int c)
{
    // the THR register store the charater to transmit
    // and read the 5th bit of LSR to know the THR empty or not.
    acquire(&uartlock); 
    while (ReadReg(UART_LSR) & (1 << 5) == 0)
        ;
    WriteReg(UART_THR, c);
    release(&uartlock);
}

int uartgetc()
{
    // the 1st bit in LSR mean that
    // The state of the receive and transmit buffers 
    // is also available.
    // the RHR register is the buff of the data.
    if(ReadReg(UART_LSR) & (0x01))
    {
        return ReadReg(UART_RHR);
    }
    else
    {
        return -1;
    }
}