#ifndef CONSOLE_H
#define CONSOLE_H


#include <stdint.h>
#include <size.h>

/* color data-type, include Foreground and background color */
// first 4-bit are background color
// last 4-bit are foreground color
typedef uint8 color;


/* vga_entry data-type, for using in VGA buffer */
// first 8-bit are color data-type 
// last 8-bit are character
typedef uint16 vga_entry;


/* Hardware text mode color constants. */
enum VGA_COLOR
{
	COLOR_BLACK 			= 0,
	COLOR_BLUE 				= 1,
	COLOR_GREEN 			= 2,
	COLOR_CYAN 				= 3,
	COLOR_RED 				= 4,
	COLOR_MAGENTA 			= 5,
	COLOR_BROWN 			= 6,
	COLOR_LIGHT_GREY 		= 7,
	COLOR_DARK_GREY 		= 8,
	COLOR_LIGHT_BLUE 		= 9,
	COLOR_LIGHT_GREEN 		= 10,
	COLOR_LIGHT_CYAN 		= 11,
	COLOR_LIGHT_RED 		= 12,
	COLOR_LIGHT_MAGENTA 	= 13,
	COLOR_LIGHT_BROWN 		= 14, 
	COLOR_WHITE 			= 15,
};


/* VGA console dimension - 80 * 25 characters */
static const size VGA_WIDTH 	= 80;
static const size VGA_HEIGHT 	= 25;


/* Public function */
void print(const char*);

/* Initialize console for printing data */
void consoleInitialize();


/* Private funtion */

/* Make color from foreground and background colors */
static color makeColor(enum VGA_COLOR, enum VGA_COLOR);

/* Make single vga_entry for given chracter and color */
static vga_entry makeVGAEntry(char, color);

/* Put a character in VGA text memory at specific location */
static void consolePutVGAEntryAt(char, color, size, size);

/* Put a character in VGA text moemory at current cursor location */
static void consolePutChar(char);

/* Set color used to display in console */
static void consoleSetColor(color);


#endif /* CONSOLE_H */