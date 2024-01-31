OUT := out
SRC := src

LINKER_SCRIPT := $(SRC)/link.ld

all: $(OUT) $(OUT)/hello-os.bin

$(OUT):
	mkdir $@

$(OUT)/hello-os.bin: $(OUT)/boot.o $(OUT)/kernel.o $(OUT)/screen.o
	ld.lld -T $(LINKER_SCRIPT) $? -o $@ -O2

$(OUT)/%.o: $(SRC)/%.s
	clang -c $? -o $@ -target i386-pc-none-elf -nostdlib

$(OUT)/%.o: $(SRC)/%.c
	clang -c $? -o $@ -target i386-pc-none-elf -ffreestanding -nostdlib -O2 -Werror -Wall -Wextra

clean: $(OUT)
	rm -rf $<
