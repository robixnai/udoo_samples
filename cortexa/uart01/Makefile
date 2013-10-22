
ARMGNU ?= arm-none-eabi

COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding 

gcc : uart01.bin

all : gcc clang

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.srec
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f *.clang.s


vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

uart01.o : uart01.c
	$(ARMGNU)-gcc $(COPS) -c uart01.c -o uart01.o

periph.o : periph.c
	$(ARMGNU)-gcc $(COPS) -c periph.c -o periph.o

uart01.bin : memmap vectors.o periph.o uart01.o 
	$(ARMGNU)-ld vectors.o periph.o uart01.o -T memmap -o uart01.elf
	$(ARMGNU)-objdump -D uart01.elf > uart01.list
	$(ARMGNU)-objcopy uart01.elf -O srec uart01.srec
	$(ARMGNU)-objcopy uart01.elf -O binary uart01.bin

LOPS = -Wall -m32 -emit-llvm
LLCOPS0 = -march=arm 
#LLCOPS1 = -march=arm -mcpu=arm1176jzf-s
LLCOPS = $(LLCOPS0)
COPS = -Wall  -O2 -nostdlib -nostartfiles -ffreestanding
OOPS = -std-compile-opts

clang : uart01.clang.bin

uart01.bc : uart01.c
	clang $(LOPS) -c uart01.c -o uart01.bc

periph.bc : periph.c
	clang $(LOPS) -c periph.c -o periph.bc

uart01.clang.elf : memmap vectors.o uart01.bc periph.bc
	llvm-link periph.bc uart01.bc -o uart01.nopt.bc
	opt $(OOPS) uart01.nopt.bc -o uart01.opt.bc
	llc $(LLCOPS) uart01.opt.bc -o uart01.clang.s
	$(ARMGNU)-as uart01.clang.s -o uart01.clang.o
	$(ARMGNU)-ld -o uart01.clang.elf -T memmap vectors.o uart01.clang.o
	$(ARMGNU)-objdump -D uart01.clang.elf > uart01.clang.list

uart01.clang.bin : uart01.clang.elf
	$(ARMGNU)-objcopy uart01.clang.elf -O srec uart01.clang.srec
	$(ARMGNU)-objcopy uart01.clang.elf -O binary uart01.clang.bin


