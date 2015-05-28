LIBAR		= libhal.a
INC			= ../Include

CCOM 		= ../../Compiler/bin/i686-elf-gcc
CPPCOM 		= ../../Compiler/bin/i686-elf-g++
AS 			= ../../Compiler/bin/i686-elf-as
AR			= ../../Compiler/bin/i686-elf-ar

CFLAG   	= -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(INC)
CPPFLAG 	= -c -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -I$(INC)
ARFLAG		= -vrcs	


OBJ			= hal.o gdt.o idt.o cpu.o

all: $(LIBAR)

$(LIBAR): $(OBJ)
	$(AR) $(ARFLAG) $(LIBAR) $(OBJ)

%.o: %.c
	$(CCOM) $< -o $@ $(CFLAG)

cpu.c: cpu.h gdt.h idt.h

cpu.h: reg.h $(INC)/stdint.h

gdt.c: gdt.h $(INC)/string.h $(INC)/null.h

gdt.h: $(INC)/stdint.h

hal.c: $(INC)/hal.h cpu.h idt.h

$(INC)/hal.h: $(INC)/stdint.h

idt.c: idt.h $(INC)/string.h $(INC)/hal.h $(INC)/stdio.h $(INC)/null.h

idt.h: $(INC)/stdint.h

reg.h: $(INC)/stdint.h