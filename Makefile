SRC 		= Core
BIN 		= Binary

KNAME 		= myos.bin
KERNEL 		= $(BIN)/$(KNAME)

CCOM 		= Compiler/bin/i686-elf-gcc
CPPCOM 		= Compiler/bin/i686-elf-g++
AS 			= Compiler/bin/i686-elf-as

CFLAG   	= -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
CPPFLAG 	= -c -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

OBJECT 		= $(BIN)/loader.o $(BIN)/kernel.o


all: $(KERNEL)


# Linking all object to kernel
$(KERNEL): $(OBJECT)
	$(CCOM) -T $(SRC)/linker.ld -o $(KERNEL) -ffreestanding -O2 -nostdlib $(OBJECT) -lgcc


# Compiling and assembling source files
$(BIN)/loader.o: $(SRC)/loader.s
	$(AS) $(SRC)/loader.s -o $(BIN)/loader.o

$(BIN)/kernel.o: $(SRC)/kernel.c
	$(CCOM) $(SRC)/kernel.c -o $(BIN)/kernel.o $(CFLAG)


# Generating iso image of OS
iso: os.iso

os.iso: $(KERNEL)
	cp $(KERNEL) iso/boot/$(KNAME)
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -input-charset utf8 -boot-load-size 4 -boot-info-table -o os.iso iso


# Running OS in bochs emulator
run: os.iso
	bochs -f Bochs/bochsconfig.txt -q

# Delete all object files in Binary folder
clean:
	rm $(BIN)/*.o


# Delete kernel and OS image also
clean-all: clean
	rm $(KERNEL) os.iso

#Assembly files
