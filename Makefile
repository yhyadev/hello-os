all: hello-os.bin

hello-os.bin: boot.o kernel.o
	ld.lld -T link.ld $? -o $@ -O2

boot.o: boot.s
	clang $? -o $@ -c -target i386-pc-none-elf -nostdlib

kernel.o: kernel.c
	clang $? -o $@ -c -target i386-pc-none-elf -ffreestanding -nostdlib -O2
