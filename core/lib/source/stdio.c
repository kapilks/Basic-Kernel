#include <stdio.h>

#include <string.h>
#include <stdarg.h>
#include <va_list.h>

#include <../Kernel/console.h>


/////////////
/* Private */
/////////////


static size bprintf(char* buffer, const char* format, va_list arguments);


//////////////////////
/* Private Function */
//////////////////////


static size bprintf(char* buffer, const char* format, va_list arguments)
{
	if(!format || !arguments)
	{
		return 0;
	}

	size formatLength = strlen(format);
	size index = 0;

	for(size i = 0; i < formatLength; ++i)
	{
		if(format[i] == '%')
		{
			i++;
			
			switch(format[i])
			{
				case 'c':		// Characters
				{		
						buffer[index] = va_arg(arguments, char);
						index++;

						break;
				}
				case 's':		// String
				{
						const char* str = va_arg(arguments, char*);
						strcpy(&buffer[index], str);
						index += strlen(str);

						break;
				}
				default:		
				{
					// Default decimal base
					enum BASE base = BASE_DEC;

					switch(format[i])
					{
						case 'x':		// Hex
						{
								base = BASE_HEX; break;
						}
						case 'b':		// Binary
						{
								base = BASE_BIN; break;
						}
						case 'o':		// Octal
						{
								base = BASE_OCT; break;
						}
						case 'd':		// Integers
						{
								base = BASE_DEC; break;
						}
					}

					uint32 num = va_arg(arguments, uint32);

					// 32 bits integer
					char str[32] = {0};

					inttostr(num, base, str);
					strcpy(&buffer[index], str);
					index += strlen(str);
				}
			}
		}
		else
		{
			buffer[index++] = format[i];
		}
	}

	buffer[index] = (char)0;

	// index id the length of buffer string 
	return index;
}


//////////////////////
/* Public Function */
//////////////////////


void printf(const char* format, ...)
{
	char buffer[BUFFER_SIZE];

	va_list arguments;
	va_start(arguments, format);

	bprintf(buffer, format, arguments);

	va_end(arguments);

	printConsole(buffer);
}

void perror(const char* format, ...)
{
	color consoleColor = consoleGetColor();
	// Using bg of consoleColor and fg as red

	consoleSetColor(makeColor(COLOR_LIGHT_RED, (consoleColor & BACKGROUND_COLOR) >> 4));

	// Same as printf
	char buffer[BUFFER_SIZE];

	va_list arguments;
	va_start(arguments, format);

	bprintf(buffer, format, arguments);

	va_end(arguments);

	printConsole(buffer);


	consoleSetColor(consoleColor);
}