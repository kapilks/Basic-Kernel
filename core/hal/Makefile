# Output librabry file
LIB_ARCH		= 	libhal.a


# Usefull directories
INC_DIR			= 	../include
INC_HAL_DIR		= 	./include
SRC_DIR			= 	./source
D_OBJ_DIR		=	./obj/debug
R_OBJ_DIR		=	./obj/release


# Tools for building
CCOM 			= 	../../compiler/bin/i686-elf-gcc
CPPCOM 			= 	../../compiler/bin/i686-elf-g++
ASM 			= 	../../compiler/bin/i686-elf-as
ARCH			= 	../../compiler/bin/i686-elf-ar
MAKEDEPEND		= 	makedepend 


# Flags for building tools
CFLAG   		= 	-c -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(INC_DIR) -I$(INC_HAL_DIR)
CPPFLAG 		= 	-c -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -I$(INC_DIR) -I$(INC_HAL_DIR)
ARFLAG			= 	-vrcs	


_SOURCE			=	hal.c gdt.c idt.c cpu.c

# Contain path to source files
SRC_FILE 		=	$(_SOURCE:%.c=$(SRC_DIR)/%.c)

# Output debug object file
D_OBJ			=	$(_SOURCE:%.c=$(D_OBJ_DIR)/%.o)

# Output release object file
R_OBJ			=	$(_SOURCE:%.c=$(R_OBJ_DIR)/%.o)

# Output dependency file
DEP 			=	.depend

#-------------------------------------------------------------------------

lib: $(LIB_ARCH)

$(LIB_ARCH): $(D_OBJ)
	$(ARCH) $(ARFLAG) $(LIB_ARCH) $(D_OBJ)

$(D_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CCOM) $< -o $@ $(CFLAG)


# Include dependency files for object files
include $(DEP)

# Clean object files
clean:
	rm $(D_OBJ_DIR)/*
	rm $(LIB_ARCH)

# Generate dependency for course and output to DEP file
depend:
	$(MAKEDEPEND) -v -f$(DEP) -Y$(INC_DIR) -I$(INC_HAL_DIR) $(SRC_FILE)
	rm $(DEP).bak