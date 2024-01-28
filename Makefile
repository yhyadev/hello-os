all: hello-os.bin

hello-os.bin: boot.o kernel.o screen.o
	ld.lld -T link.ld $? -o $@ -O2

%.o: %.s
	clang $? -o $@ -c -target i386-pc-none-elf -nostdlib

%.o: %.c
	clang $? -o $@ -c -target i386-pc-none-elf -ffreestanding -nostdlib -O2 -Werror -Wall -Wextra

clean:
	rm *.o *.bin
