# my-miniOS （RISC-V）

计划实现一个risc-v的类unix操作系统，由qemu运行

## manjaro 环境配置
```
sudo pacman -S riscv64-linux-gnu-binutils riscv64-linux-gnu-gcc riscv64-linux-gnu-gdb qemu-arch-extra
```

## 食用指南
```
make qemu
```

## gdb 调试配置
```
riscv64-linux-gnu-gdb -tui kernel/kernel
(gdb) target remote :1234
```

## 文件说明
- gdbinit gdb调试脚本文件
- note 一边学一边写的笔记
- kernel/ 内核程序存放目录
