#include "console.h"
#include <string.h>


//////////////
/* Private */
//////////////


static size consoleRow;
static size consoleColumn;
static color consoleColor;
static vga_entry* consoleBuffer;


/* Make single vga_entry for given chracter and color */
static vga_entry makeVGAEntry(char ch, color c);

/* Put a character in VGA text memory at specific location */
static void consolePutVGAEntryAt(char ch, color c, size x, size y);

/* Put a character in VGA text moemory at current cursor location */
static void consolePutChar(char ch);

/* Change the cursor position in console as character are printed*/
static void moveCursor();


//////////////////////
/* Private funtion */
//////////////////////


vga_entry makeVGAEntry(char ch, color c)
{
	uint16 ch16 	= ch;
	uint16 color16 	= c;
	
	return ch16 | color16 << 8;
}

void consolePutVGAEntryAt(char ch, color c, size x, size y)
{
	const size index = y * VGA_WIDTH + x;
	consoleBuffer[index] = makeVGAEntry(ch, c);
}

void consolePutChar(char ch)
{
	if(consoleRow == VGA_HEIGHT - 1)
	{
		// Scroll
		size limit = VGA_WIDTH * VGA_HEIGHT - VGA_WIDTH;
		for(size i = 0; i < limit; ++i)
		{
			consoleBuffer[i] = consoleBuffer[i + VGA_WIDTH];
		}

		consoleRow--;
	}


	if(ch == '\n')
	{
		consoleColumn = 0;
		consoleRow++;

		return;
	}
	
	consolePutVGAEntryAt(ch, consoleColor, consoleColumn, consoleRow);
	
	if ( ++consoleColumn == VGA_WIDTH )
	{
		consoleColumn = 0;
		consoleRow++;
	}
}

void moveCursor()
{
	uint16 location = consoleRow * VGA_WIDTH + consoleColumn;
	
	/* out ins. write second operand to port in first operand */
	asm
	(
		"mov 	%0, 			%%bx\n\t"				/*Copy location to bx register*/
		
		/*Setting Low byte of cursor position*/
		
		"mov 	$0x0f, 			%%al\n\t"				/*Cursor location low byte index*/
		"mov 	$0x03D4, 		%%dx\n\t"				/*Write it to the CRT index register*/
		"out 	%%al, 			%%dx\n\t"
	 	
		"mov 	%%bl, 			%%al\n\t"				/*The current location is in EBX. BL contains the low byte, BH high byte*/
		"mov 	$0x03D5, 		%%dx\n\t"				/*Write it to the data register*/
		"out 	%%al, 			%%dx\n\t"				/*low byte*/
		
		
		/*Setting High byte of cursor position*/
		
		"mov	$0x0e,			%%al\n\t" 				/*Cursor location high byte index*/
		"mov	$0x03D4,		%%dx\n\t"				/*Write to the CRT index register*/
		"out	%%al,			%%dx\n\t"
	 	
		"mov	%%bh,			%%al\n\t"				/*the current location is in EBX. BL contains low byte, BH high byte*/
		"mov	$0x03D5,		%%dx\n\t"				/*Write it to the data register*/
		"out	%%al,			%%dx\n\t"
		:
		: [input] "g" (location)
		: "%bx"
	);
}


//////////////////////
/* Public Function */
//////////////////////


color makeColor(enum VGA_COLOR fg, enum VGA_COLOR bg)
{	
	return fg | bg << 4;
}

void initializeConsole(color defaultColor)
{
	consoleColor 	= defaultColor;
	consoleBuffer 	= (uint16*) 0xB8000;
	
	clearConsole();
}

void printConsole(const char* data)
{
	size datalen = strlen(data);
	for (size i = 0; i < datalen; i++)
	{
		consolePutChar(data[i]);
	}

	moveCursor();
}

void consoleSetColor(color c)
{
	consoleColor = c;
}

color consoleGetColor()
{
	return consoleColor;
}

void clearConsole()
{
	for ( size y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size x = 0; x < VGA_WIDTH; x++ )
		{
			const size index = y * VGA_WIDTH + x;
			consoleBuffer[index] = makeVGAEntry(' ', consoleColor);
		}
	}

	consoleRow = 0;
	consoleColumn = 0;

	moveCursor();
}