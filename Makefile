K = kernel

OBJS = \
	$K/entry.o \
	$K/main.o

QEMU = qemu-system-riscv64

CC = riscv64-linux-gnu-gcc
AS = riscv64-linux-gnu-as
LD = riscv64-linux-gnu-ld

CFLAGS = -ffreestanding -nostdlib -g

$K/kernel: $(OBJS) $K/kernel.ld
	$(LD) -T $K/kernel.ld -o $K/kernel $(OBJS)


QEMUOPTIONS = -machine virt -bios none -kernel $K/kernel -m 128M -gdb tcp::1234

tags: $(OBJS)
	etags *.s *.c

clean:
	rm -f $K/kernel
	rm -f $K/*.o

qemu: $K/kernel
	$(QEMU) $(QEMUOPTIONS)

qemu-gdb: $K/kernel
	@echo "Please run gdb in another window."
