#ifndef IDT_H
#define IDT_H


//************************
/* IDT: Interrupt Descripter Table */
//
// IDT is responsible for managing interrupt related functionality
// File: idt.h
//************************


#ifndef ARCH_x86
#error "[idt.h] platform not implimented. Define ARCH_X86 for HAL"
#endif /* ARCH_x86 */


#include <stdint.h>


/* I86 Has 256 interrupts (0-255) */
#define I86_MAX_INTERRUPTS				256

/* Descripter flags bits */

/* Type of interrupt gate 32bit/16bit */
#define I86_IDT_DESC_BIT16				0x06	// 00000110
#define I86_IDT_DESC_BIT32				0x0E	// 00001110

/* Priviledge level */
#define I86_IDT_DESC_RING1				0x40	// 01000000
#define I86_IDT_DESC_RING2				0x20	// 00100000
#define I86_IDT_DESC_RING3				0x60	// 01100000

/* Present bit (Virtual Memory) */
#define I86_IDT_DESC_PRESENT			0x80	// 10000000


/* Descripter for IDT */
// IDT is array of GDTDescripter
// selector - 16 bits
// base - 32 bits
struct IDTDescripter
{
	uint16 	baseLow;				// 0-15 bits of Interrupt Routine address
	uint16 	selector;				// Code selector in GDT (index of GDT array)
	uint8 	reserve;				// Reserved (0)
	uint8 	flags;					// Bit mask for flags
	uint16 	baseHigh;				// 16-32 bits of Interrupt Routine address
}__attribute__((__packed__));


/* Interrupt handler function type */
typedef void (*InterruptHandler)(void);


/* Public function */

/* Return pointer to the IDTDescripter indexed by given index */
struct IDTDescripter* idtGetDescripter(uint32 index);

/* Register own interrupt handler for specific interrupts */
// If not registered default handler will be called
int32 putInterruptHandler(uint32 index, uint16 flags, uint16 selector, InterruptHandler handler);

/* Setup IDT */
// called from cpu initialization function
int32 initializeIdt(uint16 selector);


#endif /* IDT_H */