#ifndef STDARG_H
#define STDARG_H


//
// Defines macros for using in variable lenght arguments
// File: stdarg.h
//


#include <va_list.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Stack width = Int width */
#define STACKITEM int

/* Round up width of objects pushed on stack. The expression before the & 
 * ensures that we get 0 for objects of size 0. 
 */
#define	VA_SIZE(TYPE) ((sizeof(TYPE) + sizeof(STACKITEM) - 1) & ~(sizeof(STACKITEM) - 1))

/* &(LASTARG) Points to the LEFTMOST argument of the function call (before the ...) */
/* AP - argument pointer */
/* LASTARG - last argument */
#define	vaStart(AP, LASTARG) (AP=((va_list) &(LASTARG) + VA_SIZE(LASTARG)))

/* nothing for vaEnd */
#define vaEnd(AP)

#define vaArg(AP, TYPE)	(AP += VA_SIZE(TYPE), *((TYPE *)(AP - VA_SIZE(TYPE))))


#ifdef __cplusplus
}
#endif


#endif /* STDARG_H */