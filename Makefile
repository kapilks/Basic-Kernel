SRC 		= Core
BIN 		= Binary
INC			= Include
LIB			= $(SRC)/Library


KNAME 		= myos.bin
KERNEL 		= $(BIN)/$(KNAME)

CCOM 		= Compiler/bin/i686-elf-gcc
CPPCOM 		= Compiler/bin/i686-elf-g++
AS 			= Compiler/bin/i686-elf-as

CFLAG   	= -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(SRC)/$(INC) -L$(LIB)
CPPFLAG 	= -c -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -I$(SRC)/$(INC) -L$(LIB)

OBJECT 		= $(BIN)/loader.o $(BIN)/kernel.o $(BIN)/console.o

BOCHS 		= Bochs
BCONFIG 	= bochsconfig.txt

all: $(KERNEL)


# Linking all object to kernel
$(KERNEL): $(OBJECT)
	$(CCOM) -T $(SRC)/linker.ld -o $(KERNEL) -ffreestanding -O2 -nostdlib $(OBJECT) -lgcc -L$(LIB) -lstd


# Compiling and assembling source files
$(BIN)/loader.o: $(SRC)/loader.s
	$(AS) $(SRC)/loader.s -o $(BIN)/loader.o

$(BIN)/kernel.o: $(SRC)/kernel.c
	$(CCOM) $(SRC)/kernel.c -o $(BIN)/kernel.o $(CFLAG)

$(BIN)/console.o: $(SRC)/console.c $(SRC)/console.h
	$(CCOM) $(SRC)/console.c -o $(BIN)/console.o $(CFLAG)



$(SRC)/kernel.c: $(SRC)/$(INC)/null.h $(SRC)/console.h

# Generating iso image of OS
iso: os.iso

os.iso: $(KERNEL)
	cp $(KERNEL) iso/boot/$(KNAME)
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -input-charset utf8 -boot-load-size 4 -boot-info-table -o os.iso iso


# Running OS in bochs emulator
run: os.iso
	bochs -f $(BOCHS)/$(BCONFIG) -q

# Delete all object files in Binary folder
clean:
	rm $(BIN)/*.o


# Delete kernel and OS image also
clean-all: clean
	rm $(KERNEL) os.iso

#Assembly files
