/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif


#include "console.h" /* Included here so no other file include it, directly use print */


void usefullStuff()
{
	print("Hello Kapil");	
}


#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel. */
#endif
void kernel()
{
	/* Initialize console so that print start working */
	consoleInitialize();
	
	usefullStuff();
}