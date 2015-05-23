#include "cpu.h"
#include "gdt.h"
#include "idt.h"


int32 initializeProcessor()
{
	initializeGdt();
	initializeIdt(0x8);

	return 0;
}


void shutdownProcessor()
{

}