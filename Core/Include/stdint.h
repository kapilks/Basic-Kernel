#ifndef STDINT_H
#define STDINT_H


//
// Standard integer data-type
// File: stdint.h
//


/* Exact width integer type */
typedef signed char 		int8;
typedef unsigned char 		uint8;
typedef signed short 		int16;
typedef unsigned short 		uint16;
typedef signed int 			int32;
typedef unsigned int 		uint32;
typedef signed long long 	int64;
typedef unsigned long long 	uint64;


/* Integer capable of holding pointers */
typedef signed int 		intp;
typedef unsigned int 	uintp;


/* Min and Max values for integer data-type */
#define INT8_MIN 	(-128) 
#define INT16_MIN 	(-32768)
#define INT32_MIN 	(-2147483647 - 1)
#define INT64_MIN  	(-9223372036854775807LL - 1)

#define INT8_MAX 	127
#define INT16_MAX 	32767
#define INT32_MAX 	2147483647
#define INT64_MAX 	9223372036854775807LL

// Unsigned integer Min all 0
#define UINT8_MAX 	0xff 							/* 255U */
#define UINT16_MAX 	0xffff 							/* 65535U */
#define UINT32_MAX 	0xffffffff  					/* 4294967295U */
#define UINT64_MAX 	0xffffffffffffffffULL 			/* 18446744073709551615ULL */

/* Min and Max values for integer pointer data-type */
#define INTP_MIN 	INT32_MIN
#define INTP_MAX 	INT32_MAX
#define UINTP_MAX 	UINT32_MAX


#endif /* STDINT_H */