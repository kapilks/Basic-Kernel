#ifndef GDT_H
#define GDT_H


//************************
/* GDT: Global Descripter Table */
//
// Contain function to setup Global Descriptor Table(GDT)
// This handles memory map for system and permission level
// File: gdt.h
//************************


#ifndef ARCH_x86
#error "[gdt.h] platform not implimented. Define ARCH_X86 for HAL"
#endif /* ARCH_x86 */


#include <stdint.h>


// Maximum number of descriptor allowed
#define I86_MAX_GDT_DESCRIPTOR 				3



/* GDTDescripter bit flags */

/* Access bit */
// Set this to 0
// CPU set it 1 when segment is accessed
#define I86_GDT_DESC_ACCESS				0x0001			//0000000000000001

/* Readable/Writable bit */
// Readable bit for Code selector
// Writable bit for Data selector
#define I86_GDT_DESC_READWRITE			0x0002	 		//0000000000000010

/* Direction/Conforming bit */
// Direction bit for Data selector
// Conforming bit for Code selector
#define I86_GDT_DESC_EXPANSION			0x0004			//0000000000000100

/* Executable bit */
// Code/Data Segement
// Default Data Segment(0)
#define I86_GDT_DESC_EXEC_CODE			0x0008			//0000000000001000

/* Descripter bit */
// System/Code-Data Descripter
// Default System Descripter 
#define I86_GDT_DESC_CODEDATA			0x0010			//0000000000010000

/* DPL(Descripter Priviledge Level) bits */
#define I86_GDT_DESC_DPL				0x0060			//0000000001100000

/* In memory bit (Virtual Memory) */
#define I86_GDT_DESC_MEMORY				0x0080			//0000000010000000

/* Masks out limitHigh (High 4 bits of limit) */
#define I86_GDT_DESC_LIMITHI_MASK		0x0f00			//0000111100000000

/* OS Reserve bit (Next reserve bit always 0)*/
#define I86_GDT_DESC_RESERVE_OS			0x1000			//0001000000000000

/* Segment type 32bit/16bit */
// Default 16bit(0)
#define I86_GDT_DESC_SEG_TYPE			0x4000			//0100000000000000

/* 4KB Page size */
// Default 1byte
#define I86_GDT_DESC_PAGE_4KB			0x8000			//1000000000000000

		
/* Descripter for GDT */
// GDT is array of GDTDescripter
// limit - 20 bits
// base - 32 bits
struct GDTDescriptor
{
	uint16 	limit; 					// 0-15 bits of Segment limit
	uint16 	baseLow;				// 0-15 bits of Segment base address
	uint8 	baseMid;				// 16-23 bits of Segment base address
	uint16 	flags;					// Bit mask for different bit flags
	uint8 	baseHigh;				// 24-31 bits of Segment base address
}__attribute__((__packed__));


/* Public Function */

/* Put the given formed descripter at position index from the parameter passed */
void gdtPutDescriptor(uint32 index, uint32 base, uint32 limit /* 20 bits only */, uint16 flags);

/* Return pointer to the descripter */
struct GDTDescriptor* gdtGetDesciptor(uint32 index);

/* Setup GDT */
int32 initializeGdt();


#endif /* GDT_H */