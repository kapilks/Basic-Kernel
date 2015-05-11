LIBAR		= libstd.a
INC			= ../Include

CCOM 		= ../../Compiler/bin/i686-elf-gcc
CPPCOM 		= ../../Compiler/bin/i686-elf-g++
AS 			= ../../Compiler/bin/i686-elf-as
AR			= ../../Compiler/bin/i686-elf-ar

CFLAG   	= -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(INC)
CPPFLAG 	= -c -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -I$(INC)
ARFLAG		= -vrcs


OBJ			= string.o


all: libstd.a


libstd.a: $(OBJ)
	$(AR) $(ARFLAG) $(LIBAR) $(OBJ)
	
string.o: string.c
	$(CCOM) string.c -o string.o $(CFLAG) 
	
string.c: $(INC)/string.h