#include <string.h>


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