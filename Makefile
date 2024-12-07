OUT := out
SRC := src
IMPL = c

LINKER_SCRIPT := $(SRC)/link.ld

.PHONY: all
all: $(OUT) $(OUT)/hello-os.bin

.PHONY: run
run: all
	qemu-system-i386 -kernel $(OUT)/hello-os.bin

.PHONY: clean
clean: $(OUT)
	rm -rf $<

$(OUT):
	mkdir $@

$(OUT)/hello-os.bin: $(OUT)/boot.o $(OUT)/kernel.o
	ld.lld -T $(LINKER_SCRIPT) $? -o $@ -O2

$(OUT)/%.o: $(SRC)/%.s
	clang -c $? -o $@ -target i386-pc-none-elf -nostdlib

ifeq ($(IMPL), c)
$(OUT)/%.o: $(SRC)/%.c
	clang -c $? -o $@ -target i386-pc-none-elf -ffreestanding -nostdlib -O2 -Werror -Wall -Wextra
else ifeq ($(IMPL), cerium)
$(OUT)/%.o: $(SRC)/%.cerm
	cerium compile $? --output $@ --target x86-freestanding-none --emit object --runner none --code-model kernel
endif
