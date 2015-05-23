#ifndef STRING_H
#define STRING_H



//************************
// Conatain function related to string - character array
// File: string.h
//************************



#include <size.h>


/* Conversion base for integers */
enum BASE
{ 
	BASE_HEX	=	16,
	BASE_DEC	=	10,
	BASE_OCT	=	8,
	BASE_BIN	=	2,
};


//////////////////////
/* Public Function */
//////////////////////


/* Return the length of the string (excluding NULL character) */
size strlen(const char*);

/* Copy source to destination */
// Return pointer to destination string
char* strcpy(char* destination, const char* source);

/* Copy value to each byte of destination till count */
void* memset(void* destination, char value, size count);

/* Copy source to destination till count */
void* memcpy(void* destination, const void* source, size count);

/* Convert positive integer to string */
// base is for string(output value)
void inttostr(uint32 value, enum BASE base, char* destination);

/* Convert string to positive integer */
// base is for string(source value)
void strtoint(char* source, enum BASE base, uint32* destination);

/* Reverse the string inplace */
void strrev(char* source);


#endif /* STRING_H */