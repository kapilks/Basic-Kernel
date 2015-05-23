#include <string.h>


//////////////
/* Private */
//////////////


// Integers characters in different base
static char characters[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};


//////////////////////
/* Public Function */
//////////////////////


size strlen(const char* str)
{
	size length = 0;
	
	while(str[length] != 0)
	{
		length++;
	}
	
	/* This length exclude NULL character */
	return length;
}

char* strcpy(char* destination, const char* source)
{
	char* destinationTmp = destination;
		
	while(*source)
	{
		*destination = *source;
		destination++;
		source++; 
	}

	// Copy null character
	*destination = *source;

	return destinationTmp;
}

void* memset(void* destination, char value, size count)
{
	// Converting for valid pointer ++
	uint8* destinationTmp = (uint8*)destination;

	for(; count > 0; --count, ++destinationTmp)
	{
		*destinationTmp = value;
	}

	return destination;
}

void* memcpy(void* destination, const void* source, size count)
{
	uint8* destinationTmp = (uint8*)destination;
	const uint8* sourceTmp = (const uint8*)source;

	for(; count > 0; --count, ++destinationTmp, ++sourceTmp)
	{
		*destinationTmp = *sourceTmp;
	}

	return destination;
}

void inttostr(uint32 value, enum BASE base, char* destination)
{
	char* destinationTmp = destination;
	uint8 ch;

	if(value == 0)
	{
		*destination++ = '0';
		*destination = '\0';

		return;
	}

	while(value > 0)
	{
		ch = (uint8)(value % base);

		*destination++ = characters[ch];

		value /= base;
	}

	// NULL character
	*destination = '\0';

	strrev(destinationTmp);
}

void strtoint(char* source, enum BASE base, uint32* destination)
{
	uint32 output = 0;
	
	size length = strlen(source);
	
	for(; length > 0; --length, source++)
	{
		uint8 ch = (uint8)*source;

		if(ch >= 'a' && ch <= 'f')
		{
			ch =  ch - (uint8)'a' + 10;
		}
		else if(ch >= 'A' && ch <= 'F')
		{
			ch = ch - (uint8)'A' + 10;
		}
		else
		{
			ch -= (uint8)'0';
		}

		output = output * base + ch;
	}

	*destination = output;
}

void strrev(char* source)
{
	size length = strlen(source);
	uint8 tmp;

	size high = length - 1;
	size low = 0;

	while(low < high)
	{
		tmp = source[low];
		source[low] = source[high];
		source[high] = tmp;

		low++;
		high--;
	}
}

uint8 strcmp(const char* str1, const char* str2)
{
	size len1 = strlen(str1);
	size len2 = strlen(str2);

	if(len1 != len2)
	{
		return 0;
	}

	for(size i = 0; i < len1; ++i)
	{
		if(*str1++ != *str2++)
		{
			return 0;
		}
	}

	return 1;
}