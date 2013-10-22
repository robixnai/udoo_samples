
ARMGNU ?= arm-none-eabi

COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding 

gcc : timer01.bin

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

timer01.o : timer01.c
	$(ARMGNU)-gcc $(COPS) -c timer01.c -o timer01.o

periph.o : periph.c
	$(ARMGNU)-gcc $(COPS) -c periph.c -o periph.o

timer01.bin : memmap vectors.o periph.o timer01.o 
	$(ARMGNU)-ld vectors.o periph.o timer01.o -T memmap -o timer01.elf
	$(ARMGNU)-objdump -D timer01.elf > timer01.list
	$(ARMGNU)-objcopy timer01.elf -O srec timer01.srec
	$(ARMGNU)-objcopy timer01.elf -O binary timer01.bin

LOPS = -Wall -m32 -emit-llvm
LLCOPS0 = -march=arm 
#LLCOPS1 = -march=arm -mcpu=arm1176jzf-s
LLCOPS = $(LLCOPS0)
COPS = -Wall  -O2 -nostdlib -nostartfiles -ffreestanding
OOPS = -std-compile-opts

clang : timer01.clang.bin

timer01.bc : timer01.c
	clang $(LOPS) -c timer01.c -o timer01.bc

periph.bc : periph.c
	clang $(LOPS) -c periph.c -o periph.bc

timer01.clang.elf : memmap vectors.o timer01.bc periph.bc
	llvm-link periph.bc timer01.bc -o timer01.nopt.bc
	opt $(OOPS) timer01.nopt.bc -o timer01.opt.bc
	llc $(LLCOPS) timer01.opt.bc -o timer01.clang.s
	$(ARMGNU)-as timer01.clang.s -o timer01.clang.o
	$(ARMGNU)-ld -o timer01.clang.elf -T memmap vectors.o timer01.clang.o
	$(ARMGNU)-objdump -D timer01.clang.elf > timer01.clang.list

timer01.clang.bin : timer01.clang.elf
	$(ARMGNU)-objcopy timer01.clang.elf -O srec timer01.clang.srec
	$(ARMGNU)-objcopy timer01.clang.elf -O binary timer01.clang.bin


