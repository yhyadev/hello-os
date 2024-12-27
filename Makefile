OUT := out
SRC := src

LINKER_SCRIPT := $(SRC)/link.ld

$(OUT):
	mkdir $@

$(OUT)/%.o: $(SRC)/%.cerm
	cerium compile $< --output $@ --target x86-freestanding-none --emit object --runner none --code-model kernel

$(OUT)/hello-os.bin: $(OUT)/kernel.o
	ld.lld -T $(LINKER_SCRIPT) $? -o $@ -O2

.PHONY: all
all: $(OUT) $(OUT)/hello-os.bin

.PHONY: run
run: all
	qemu-system-i386 -kernel $(OUT)/hello-os.bin

.PHONY: clean
clean: $(OUT)
	rm -rf $<
