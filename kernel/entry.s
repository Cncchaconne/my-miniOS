#kernel.ld causes the following code to 
#be placed at 0x80000000

#add this one to the .text
.section .text
.global _entry

_entry:

    # jump to main() in main.c
    call main