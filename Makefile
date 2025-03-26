OUT := out
SRC := src

LINKER_SCRIPT := $(SRC)/link.ld

$(OUT):
	mkdir $@

$(OUT)/%.o: $(SRC)/%.bq
	barq compile $< --output $@ --target x86-freestanding-none --emit object --runner none --optimize release --code-model kernel \
		--cpu-model generic --add-cpu-features soft_float --remove-cpu-features mmx,sse,sse2,sse3,avx,avx2

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
