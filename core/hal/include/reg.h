#ifndef REG_H
#define REG_H


#ifndef ARCH_x86
#error "[reg.h] platform not implimented. Define ARCH_X86 for HAL"
#endif /* ARCH_x86 */


#include <stdint.h>


// 32 bit Registers
struct R32Bit
{
	uint32 eax;
	uint32 ebx;
	uint32 ecx;
	uint32 edx;
	uint32 esi;
	uint32 edi;
	uint32 ebp;
	uint32 esp;
	uint32 eflags;
	uint8  cflags;
};


// 16 bit Registers
struct R16Bit
{
	uint16 ax;
	uint16 bx;
	uint16 cx;
	uint16 dx;
	uint16 si;
	uint16 di;
	uint16 bp;
	uint16 sp;
	uint16 es;
	uint16 cs;
	uint16 ss;
	uint16 ds;
	uint16 flags;
	uint8  cflags;
};


// 16 bit Registers expressed as 32 bit Registers
struct R16Bit32
{
	uint16 ax;
	uint16 axh;
	uint16 bx;
	uint16 bxh;
	uint16 cx;
	uint16 cxh;
	uint16 dx;
	uint16 dxh;

	uint16 si;
	uint16 di;
	uint16 bp;
	uint16 sp;
	uint16 es;
	uint16 cs;
	uint16 ss;
	uint16 ds;
	uint16 flags;
	uint8 cflags;
};


// 8 bit Registers
struct R8Bit
{
	uint8 al;
	uint8 ah;
	uint8 bl;
	uint8 bh;
	uint8 cl;
	uint8 ch;
	uint8 dl;
	uint8 dh;
};


// 8 bit Registers expressed as 32 bit Registers
struct R8Bit32
{
	uint8 al, ah;
	uint16 axh;
	uint8 bl, bh;
	uint16 bxh;
	uint8 cl, ch;
	uint16 cxh;
	uint8 dl, dh;
	uint16 dxh;
};


union IntR16
{
	struct R16Bit x;
	struct R8Bit h;
};

union IntR32
{
	struct R32Bit x;
	struct R16Bit32 l;
	struct R8Bit32 h;
};
#endif /* REG_H */