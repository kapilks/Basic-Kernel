#ifndef CONSOLE_H
#define CONSOLE_H



//************************
// Initialize console for inputing and outputing
// data on screen
// File: console.h
//************************



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
#define VGA_WIDTH 	80
#define VGA_HEIGHT 	25


/* Color bits */
#define FOREGROUND_COLOR 	0x0F 			// 00001111
#define BACKGROUND_COLOR 	0xF0 			// 11110000


//////////////////////
/* Public function */
//////////////////////


/* Print the string to console */
void printConsole(const char*);

/* Clear VGA memory and move cursor to starting position*/
void clearConsole();

/* Initialize console for printing data */
void initializeConsole(color defaultColor);

/* Set color used to display in console */
void consoleSetColor(color c);

/* Return the current color used in console */
color consoleGetColor();

/* Make color from foreground and background colors */
color makeColor(enum VGA_COLOR fg, enum VGA_COLOR bg);


#endif /* CONSOLE_H */