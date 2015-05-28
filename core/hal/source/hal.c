#define ARCH_x86

#ifndef ARCH_x86
#error "[hal.c] platform not implimented. Define ARCH_X86 for HAL"
#endif /* ARCH_x86 */


#include <hal.h>
#include "cpu.h"
#include "idt.h"

void zero_int()
{
	//__asm__("pushad");

	perror("Error: divide by zero\n");

	//__asm__("popad; leave; iret;");
}

int initializeHal()
{
	initializeProcessor();

	putInterruptHandler(0, I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32, 0x8, (InterruptHandler)zero_int);
	return 0;
}


int shutdownHal()
{
	shutdownProcessor();
	return 0;
}
			

void genInterrupt(uint32 interrupt)
{
	uint16 opcode = 0;
	asm
	(
		"movb 	%0, 	%%al\n\t"
		"movb 	%%al, 	genInt + 1\n\t"
		"jmp 	genInt\n\t"
		"genInt:\n\t"
		"int 	$0\n\t"
		:
		: [input] "g" (interrupt)
		: "%al"
	);
}