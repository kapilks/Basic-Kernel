#define ARCH_x86

#include <gdt.h>

#include <string.h>
#include <null.h>

/* Extracting bit (All 1) */
#define LEAST_32_BITS				0xffffffff
#define LEAST_16_BITS				0xffff
#define LEAST_8_BITS   				0xff

/* Content of GDTR register */
struct GDTR
{
	uint16 limit;					// Size of GDT - 1 bytes
	uint32 base;					// Linear address of first entry of GDT
}__attribute__((__packed__));



//====================================================================================


/* Private */

// Global Destriptor Table as array of descriptor entries
static struct GDTDescriptor gdt[I86_MAX_GDT_DESCRIPTOR];

// GDT Register value
static struct GDTR gdtr;


/* Load GDTR register */
static void loadGdt()
{
	asm
	(
		"lgdt 	%0"
		:
		: [input] "g" (gdtr)
		:
	);
}



//=====================================================================================



void gdtPutDescriptor(uint32 index, uint32 base, uint32 limit, uint16 flags)
{
	if(index >= I86_MAX_GDT_DESCRIPTOR)
	{
		return;
	}

	memset((void*)&gdt[index], 0, sizeof(struct GDTDescriptor));

	// Set limit and base address
	gdt[index].baseLow 		= (uint16)(base & LEAST_16_BITS);
	gdt[index].baseMid 		= (uint8)((base >> 16) & LEAST_8_BITS);
	gdt[index].baseHigh 	= (uint8)((base >> 24) & LEAST_8_BITS);
	gdt[index].limit 		= (uint16)(limit & LEAST_16_BITS);

	// Add limit first 4 bits to flag starting at 5th bit
	flags |= (uint16)((limit >> 16) << 8);

	// Set flag
	gdt[index].flags = flags;
}


struct GDTDescriptor* gdtGetDesciptor(uint32 index)
{
	if(index >= I86_MAX_GDT_DESCRIPTOR)
	{
		return NULL;
	}

	return &gdt[index];
}


int32 initializeGdt()
{
	// Set up gdtr
	gdtr.limit 	= sizeof(struct GDTDescriptor) * I86_MAX_GDT_DESCRIPTOR - 1;
	gdtr.base 	= (uint32)(&gdt[0]);

	// Set null descriptor
	gdtPutDescriptor(0, 0, 0, 0);

	// Set default code descriptor
	gdtPutDescriptor(1, 0, LEAST_32_BITS,
		I86_GDT_DESC_READWRITE | 
		I86_GDT_DESC_EXEC_CODE | 
		I86_GDT_DESC_CODEDATA |
		I86_GDT_DESC_MEMORY |
		I86_GDT_DESC_PAGE_4KB |
		I86_GDT_DESC_SEG_TYPE | 
		I86_GDT_DESC_LIMITHI_MASK);

	// Set default data descriptor
	gdtPutDescriptor(2, 0, LEAST_32_BITS,
		I86_GDT_DESC_READWRITE |
		I86_GDT_DESC_CODEDATA |
		I86_GDT_DESC_MEMORY |
		I86_GDT_DESC_PAGE_4KB |
		I86_GDT_DESC_SEG_TYPE | 
		I86_GDT_DESC_LIMITHI_MASK);

	loadGdt();

	return 0;
}