K = kernel

OBJS = \
	$K/entry.o \
	$K/main.o  \
	$K/uart.o

QEMU = qemu-system-riscv64

CC = riscv64-linux-gnu-gcc
AS = riscv64-linux-gnu-as
LD = riscv64-linux-gnu-ld
OBJDUMP = riscv64-linux-gnu-objdump

CFLAGS = -ffreestanding -nostdlib -ggdb

$K/kernel: $(OBJS) $K/kernel.ld
	$(LD) -T $K/kernel.ld -o $K/kernel $(OBJS)
	$(OBJDUMP) -S $K/kernel > $K/kernel.asm


QEMUOPTIONS = -machine virt -bios none -kernel $K/kernel -m 128M 

tags: $(OBJS)
	etags *.s *.c

clean:
	rm -f $K/kernel
	rm -f $K/*.o
	rm -f $K/*.asm

qemu: $K/kernel
	$(QEMU) $(QEMUOPTIONS)

qemu-gdb: $K/kernel
	@echo "Please run gdb in another window."
	$(QEMU) $(QEMUOPTIONS) -gdb tcp::1234

