#ifndef STDIO_H
#define STDIO_H



//************************
// Constain function related to input and output to console
// File: stdio.h
//************************



/* String of this size can be printed on console at a time */
#define BUFFER_SIZE			255


//////////////////////
/* Public Function */
//////////////////////


/* Print formatted output to console */
void printf(const char* format, ...);

/* Print formatted error on console with red color */ 
void perror(const char* format, ...);


#endif /* STDIO_H */