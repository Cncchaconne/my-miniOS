#kernel.ld causes the following code to 
#be placed at 0x80000000

#add this one to the .text
.section .text
.global _entry

_entry:

    #setting the program stack to the first program
    la sp, stack0
    li a0, 1024*4
	csrr a1, mhartid
    addi a1, a1, 1
    mul a0, a0, a1
    add sp, sp, a0      #point to the biggest address
    # jump to main() in main.c
    call main