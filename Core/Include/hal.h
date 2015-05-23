#ifndef HAL_H
#define HAL_H


//************************
/* HAL: Hardware Abstraction Layer */
//
// The Hardware Abstraction Layer provide interface for controlling
// motherboard hardware device
// Specific HAL inplimentation is provided in for of library for
// specific hardware
// File: hal.h
//************************


#ifndef ARCH_x86
#error "HAL is not implimented"
#endif /* ARCH_x86 */


#include <stdint.h>


/* Public Function */

/* Initialize HAL specific implimentation */
int halInitialize();

/* Shutdown HAL */
int halShutdown();

/* Generate Software interrupt */
// interrupt is index in IDT
void genInterrupt(uint32 interrupt);


#endif /* HAL_H */