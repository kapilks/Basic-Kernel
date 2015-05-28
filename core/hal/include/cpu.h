#ifndef CPU_H
#define CPU_H


//************************
// Processor interface for managing processors,
// processor cores, data structure
// File: cpu.h
//************************
//


#ifndef ARCH_x86
#error "[cpu.h] platform not implimented. Define ARCH_X86 for HAL"
#endif /* ARCH_x86 */


#include <stdint.h>
#include "reg.h"


/* Setup the processor idt, gdt */
int32 initializeProcessor();

/* Shutdown processor */
void shutdownProcessor();


#endif /* CPU_H */