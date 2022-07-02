K = kernel

OBJS = \
	$K/entry.o \
	$K/main.o

QEMU = qemu-system-riscv64

CFLAGS = -ffreestanding -nostdlib

$K/kernel: $K/main.c
	riscv64-linux-gnu-gcc $K/main.c $(CFLAGS) -g -o $K/kernel.o
	riscv64-linux-gnu-ld $K/kernel.o -T $K/kernel.ld -o $K/kernel

QEMUOPTIONS = -machine virt -bios none -kernel $K/kernel -m 128M

clean:
	rm -f $K/kernel
	rm -f $K/*.o

qemu: $K/kernel
	$(QEMU) $(QEMUOPTIONS)

qemu-gdb: $K/kernel
	@echo "Please run gdb in another window."
