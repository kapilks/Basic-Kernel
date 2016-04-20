# Usefull directories
LIB_DIR			= 	./core/lib
KER_DIR			= 	./core/kernel
HAL_DIR 		=	./core/hal


# Output files
KNAME 			= kernel.bin
KERNEL 			= $(KER_DIR)/bin/$(KNAME)
ISO 			= os32.iso


# Tools for building
CCOM 			= compiler/bin/i686-elf-gcc
CPPCOM 			= compiler/bin/i686-elf-g++
AS 				= compiler/bin/i686-elf-as


# Flags for building tools
CFLAG   		= -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra -L$(LIB_DIR)
CPPFLAG 		= -c -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -L$(LIB_DIR)


# Libraries used
LIB 			= -lhal -lstd


# Object files
_OBJ 			=	console.o kernel.o loader.o
OBJ 			= 	$(_OBJ:%.o=$(KER_DIR)/obj/debug/%.o)


# Linker file
LD_FILE 		= ./core/kernel/linker.ld


# Bochs emulator 
BOCHS 			= bochs
BCONFIG 		= bochsconfig.txt


#--------------------------------------------------------------------------
# Linking all object to kernel
$(KERNEL): $(OBJ) $(LIB_DIR)/libhal.a $(LIB_DIR)/libstd.a
	$(CCOM) -T $(LD_FILE) -o $(KERNEL) -ffreestanding -O2 -nostdlib $(OBJ) -lgcc -L$(LIB_DIR) $(LIB)

$(LIB_DIR)/libhal.a: $(HAL_DIR)/libhal.a
	cp $(HAL_DIR)/libhal.a $(LIB_DIR)/libhal.a

#--------------------------------------------------------------------------

all: hal stdlib kernel $(KERNEL) 

#--------------------------------------------------------------------------
# Building all modules

# Building kernel
kernel:
	cd $(KER_DIR); make depend; make;


# Building HAL
hal:
	cd $(HAL_DIR); make depend; make;


# Building stdlib
stdlib:
	cd $(LIB_DIR); make depend; make;

# Setup directory and dependencies file for first run
configure:
	chmod +x initialise.sh
	./initialise.sh
#-------------------------------------------------------------------------


# Generating iso image of OS
iso: $(ISO)


$(ISO): $(KERNEL)
	cp $(KERNEL) iso/boot/$(KNAME)
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -input-charset utf8 -boot-load-size 4 -boot-info-table -o $(ISO) iso


# Running OS in bochs emulator
run: $(ISO)
	bochs -f $(BOCHS)/$(BCONFIG) -q

# Delete all object files in Binary folder
clean:
	rm $(KERNEL) $(ISO)