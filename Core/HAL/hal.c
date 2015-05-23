#define ARCH_x86

#ifndef ARCH_x86
#error "[hal.c] platform not implimented. Define ARCH_X86 for HAL"
#endif /* ARCH_x86 */


#include <hal.h>
#include "cpu.h"
#include "idt.h"


int initializeHal()
{
	initializeProcessor();
	return 0;
}


int shutdownHal()
{
	shutdownProcessor();
	return 0;
}
			

void genInterrupt(uint32 interrupt)
{
	asm
	(
		"mov 	byte ptr[%0], 	%%al\n\t"
		"mov 	%%al, 			byte ptr[genInt + 1]\n\t"
		"jmp 	genInt\n\t"
		"genInt:\n\t"
		"int 	0\n\t"
		:
		: [input] "g" (interrupt)
		: "%al"
	);
}