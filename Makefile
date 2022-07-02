K = kernel

QEMU = qemu-system-riscv64

$K/kernel: $K/main.c
	riscv64-linux-gnu-gcc $K/main.c -g -o $K/kernel

QEMUOPTIONS = -machine virt -bios none -kernel $K/kernel -m 128M

clean:
	rm -f $K/kernel

qemu: $K/kernel
	$(QEMU) $(QEMUOPTIONS)

