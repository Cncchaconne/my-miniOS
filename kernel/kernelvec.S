# interrupts and exceptions while in supervisor
# mode come here

.globl kerneltrap
.globl kernelvec
.align 4
kernelvec:
    

#
# machine-mode timer interrupt.
.globl timervec
.align 4
timervec:
        # start.c has set up the memory that msscratch points here\

        # csrrw : Atom exchange data
        csrrw a0, mscratch, a0

        # sd : store double word
        sd a1, 0(a0)
        sd a2, 8(a0)
        sd a3, 16(a0)

        # schedule the next timer interrupt
        # by adding interval to mtimecmp.

        # ld : load double word
        ld a1, 24(a0) # CLINT_MTIMECMP(hart)
        ld a2, 32(a0) # interval
        ld a3, 0(a1)
        add a3, a3, a2
        sd a3, 0(a1)

        # arrange for a supervisor software interrupt
        # after this handler returns.

        # li : Load the immediate number into the register
        li a1, 2

        # sip : supervisor interrupt register
        # write the number to the sip register to
        # get a supervisor software interrupt
        csrw sip, a1

        ld a3, 16(a0)
        ld a2, 8(a0)
        ld a1, 0(a0)
        csrrw a0, mscratch, a0

        mret    

