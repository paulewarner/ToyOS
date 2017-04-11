A simple, toy OS, written in C, for x86_64 systems.

Requirements:
* A Unix compatible C compiler. It should compile under clang or gcc.
* [nasm](http://nasm.us), An x86 assembler
* GNU make
* A Python 3 interpreter is required for running the experimental bootloader.
* [qemu](http://http://www.qemu-project.org/) to test.
* GNU Grub is used to build a bootable disk, so grub-mkrescue must be available
* Can be debugged using either lldb or gdb. lldb requires [this](https://github.com/llvm-mirror/lldb/blob/master/examples/python/x86_64_target_definition.py) file in the deps directory to debug

In addition to the above, creating a bootable ISO requires some binary files from [this](http://packages.ubuntu.com/yakkety/grub-pc-bin) ubuntu package. /usr/lib/grub to the deps directory in this project.
