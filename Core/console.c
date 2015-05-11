#include "console.h"
#include <string.h>


size consoleRow;
size consoleColumn;
color consoleColor;
vga_entry* consoleBuffer;


void consoleInitialize()
{
	consoleRow 		= 0;
	consoleColumn 	= 0;
	consoleColor 	= makeColor(COLOR_WHITE, COLOR_BLACK);
	consoleBuffer 	= (uint16*) 0xB8000;
	
	for ( size y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size x = 0; x < VGA_WIDTH; x++ )
		{
			const size index = y * VGA_WIDTH + x;
			consoleBuffer[index] = makeVGAEntry(' ', consoleColor);
		}
	}
}


void print(const char* data)
{
	size datalen = strlen(data);
	for (size i = 0; i < datalen; i++)
	{
		consolePutChar(data[i]);
	}
}


color makeColor(enum VGA_COLOR fg, enum VGA_COLOR bg)
{
	return fg | bg << 4;
}


vga_entry makeVGAEntry(char ch, color c)
{
	uint16 ch16 	= ch;
	uint16 color16 	= c;
	
	return ch16 | color16 << 8;
}


void consoleSetColor(color c)
{
	consoleColor = c;
}


void consolePutVGAEntryAt(char ch, color c, size x, size y)
{
	const size index = y * VGA_WIDTH + x;
	consoleBuffer[index] = makeVGAEntry(ch, c);
}


void consolePutChar(char ch)
{
	if(ch == '\n')
	{
		consoleColumn = 0;
		if(++consoleRow == VGA_HEIGHT)
		{
			consoleRow = 0;
		}

		return;
	}

	consolePutVGAEntryAt(ch, consoleColor, consoleColumn, consoleRow);
	
	if ( ++consoleColumn == VGA_WIDTH )
	{
		consoleColumn = 0;
		if ( ++consoleRow == VGA_HEIGHT )
		{
			consoleRow = 0;
		}
	}
}