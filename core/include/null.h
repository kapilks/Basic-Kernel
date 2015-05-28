#ifndef NULL_H
#define NULL_H


//************************
// Standard NULL declaration 
// File: null.h
//************************


/* Undefine NULL if it is already defined by stdlib */
#ifdef NULL
#undef NULL
#endif


#ifdef __cplusplus
extern "C"
{
	/* Standard NULL declaraton for C++*/
#define NULL 0
/* Written #endif so that redefinition does not occur */
#endif

#ifdef __cplusplus
}
#else
	/* Standard NULL declaration for C*/
#define NULL (void*)0 
#endif


#endif	/* NULL_H */