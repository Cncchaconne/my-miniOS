rm *dtb
rm *dts
qemu-system-riscv64 -machine virt -machine dumpdtb=riscv64-virt.dtb
dtc -I dtb -O dts -o riscv64-virt.dts riscv64-virt.dtb

