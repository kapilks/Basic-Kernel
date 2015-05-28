#define ARCH_x86


#include "cpu.h"
#include "gdt.h"
#include "idt.h"


int32 initializeProcessor()
{
	initializeGdt();
	initializeIdt(0x8); // selector of gdt 1 index (code selector)

	return 0;
}


void shutdownProcessor()
{

}