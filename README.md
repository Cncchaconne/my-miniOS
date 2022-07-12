# my-miniOS （RISC-V）

计划实现一个risc-v的类unix操作系统，由qemu运行

## 参考资料
- xv6-riscv ：https://github.com/mit-pdos/xv6-riscv
- riscv中文手册 ：http://riscvbook.com/chinese/RISC-V-Reader-Chinese-v2p1.pdf 
- riscv英文手册 ：https://riscv.org/technical/specifications/
- 大佬的博客 ：https://dingfen.github.io/
- 大佬的博客 ：http://www.databusworld.cn/author/3/page/6/
- virt平台主要参考（参考U540平台）：https://sifive.cdn.prismic.io/sifive/d3ed5cd0-6e74-46b2-a12d-72b06706513e_fu540-c000-manual-v1p4.pdf
- 其他学校的实验手册 ：https://rcore-os.github.io/rCore-Tutorial-deploy/docs/lab-3/guide/part-1.html
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
- gdbinit gdb调试脚本文件  食用方式：source gdbinit
- note 一边学一边写的笔记
- kernel/ 内核程序存放目录
- virt/ 硬件布局文件存放目录
