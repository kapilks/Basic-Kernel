#define ARCH_x86

#include <idt.h>

#include <string.h>
#include <hal.h>
#include <stdio.h>
#include <null.h>

/* Content of IDTR register */
struct IDTR
{
	uint16 limit;
	uint32 base;
}__attribute__((__packed__));


//====================================================================================



/* Private */

/* Interrupt Descripter Table as array of IDTDescripter */
static struct IDTDescripter idt[I86_MAX_INTERRUPTS];

/* IDT Register value */
static struct IDTR idtr;


/* Load IDTR register */
static void loadIdtr()
{
	asm
	(
		"lidt 	%0"
		:
		: [input] "g" (idtr)
		:
	);
}


/* Default interrupt handler */
// This handler is used for interrupts whose handler is
// not defined
static void defaultInterruptHandler()
{
	perror("I86 Default interrupt handler\n");

	for(;;);
}



//====================================================================================



struct IDTDescripter* idtGetDescripter(uint32 index)
{
	if(index >= I86_MAX_INTERRUPTS)
	{
		return NULL;
	}

	return &idt[index];
}


int32 putInterruptHandler(uint32 index, uint16 flags, uint16 selector, InterruptHandler handler)
{
	if(index >= I86_MAX_INTERRUPTS)
	{
		return 0;
	}

	if(!handler)
	{
		return 0;
	}

	uint32 ibase = (uint32)(&(*handler));

	idt[index].baseLow 	= (uint16)(ibase & 0xffff);
	idt[index].baseHigh = (uint16)((ibase >> 16) & 0xffff);
	idt[index].reserve 	= 0;
	idt[index].flags 	= (uint8)(flags);
	idt[index].selector = selector;

	return 0;	
}


int32 initializeIdt(uint16 selector)
{
	// Setup idtr
	idtr.limit 	= sizeof(struct IDTDescripter) * I86_MAX_INTERRUPTS -1;
	idtr.base	= (uint32)&idt[0];

	// Null idtdescripter
	memset((void*)&idt[0], 0, sizeof(struct IDTDescripter) * I86_MAX_INTERRUPTS - 1);

	// Register default handler
	for(int i = 0; i < I86_MAX_INTERRUPTS; ++i)
	{
		putInterruptHandler(i, I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32, 	selector, (InterruptHandler)defaultInterruptHandler);
	}

	loadIdtr();

	return 0;
}