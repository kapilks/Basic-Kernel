#ifndef VA_LIST_H
#define VA_LIST_H


//
// Define the data-type used for variable list argument in function
// File: va_list.h
//


#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef uint8* va_list; 

#ifdef __cplusplus
}
#endif


#endif /* VA_LIST_H */