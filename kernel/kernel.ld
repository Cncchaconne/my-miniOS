OUTPUT_ARCH( "riscv" )
ENTRY(_entry)

/* ALGIN 是对齐命令 */

SECTIONS
{
    /* 
        ensure that enty.s / _entry is at 0x80000000,
        qemu's kernel jumps.
        . = 0x8000000 is mean that the program start at 0x80000000
     */
    . = 0x80000000;

    .text : {
        *(.text .text.*)
        . = ALIGN(0x1000);
        _trampoline = .;
        *(trampsec)
        . = ALIGN(0x1000);
        ASSERT(. - _trampoline == 0x1000, "error: trampoline larger than one page");
        PROVIDE(etext = .);
    }

    .rodata : {
        . = ALIGN(16);
        *(.sdata .sdata.*)
        . = ALIGN(16);
        *(.rodata .rodata.*)
    }

    .data : {
        . = ALIGN(16);
        *(.sdata .sdata.*) 
        . = ALIGN(16);
        *(.data .data.*) 
    }

    .bss : {
        . = ALIGN(16);
        *(.sbss .sbss.*) 
        . = ALIGN(16);
        *(.bss .bss.*)
    }

    PROVIDE(end = .);
}