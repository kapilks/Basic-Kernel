#ifndef CTYPE_H
#define CTYPE_H


//
// Header for determining type and their details
// of the character of string
// File: ctype.h
//


#ifdef __cplusplus
extern "C"
{
#endif

extern char _ctype[];

/* Character type Constants */

#define CTYPE_UP	0x01	/* upper case */
#define CTYPE_LOW	0x02	/* lower case */
#define CTYPE_DIG	0x04	/* digit */
#define CTYPE_CTL	0x08	/* control */
#define CTYPE_PUN	0x10	/* punctuation */
#define CTYPE_WHT	0x20	/* white space (space/cr/lf/tab) */
#define CTYPE_HEX	0x40	/* hex digit */
#define CTYPE_SP	0x80	/* hard space (0x20) */

/* Basic macros for getting details of character */

#define isAlnum(c)	((_ctype + 1)[(unsigned int)(c)] & (CTYPE_UP | CTYPE_LOW | CTYPE_DIG))
#define isAlpha(c)	((_ctype + 1)[(unsigned int)(c)] & (CTYPE_UP | CTYPE_LOW))
#define isCntrl(c)	((_ctype + 1)[(unsigned int)(c)] & (CTYPE_CTL))
#define isDigit(c)	((_ctype + 1)[(unsigned int)(c)] & (CTYPE_DIG))
#define isGraph(c)	((_ctype + 1)[(unsigned int)(c)] & (CTYPE_PUN | CTYPE_UP | CTYPE_LOW | CTYPE_DIG))
#define isLower(c)	((_ctype + 1)[(unsigned int)(c)] & (CTYPE_LOW))
#define isPrint(c)	((_ctype + 1)[(unsigned int)(c)] & (CTYPE_PUN | CTYPE_UP | CTYPE_LOW | CTYPE_DIG | CTYPE_SP))
#define isPunct(c)	((_ctype + 1)[(unsigned int)(c)] & (CTYPE_PUN))
#define isSpace(c)	((_ctype + 1)[(unsigned int)(c)] & (CTYPE_WHT))
#define isUpper(c)	((_ctype + 1)[(unsigned int)(c)] & (CTYPE_UP))
#define isXdigit(c)	((_ctype + 1)[(unsigned int)(c)] & (CTYPE_DIG | CTYPE_HEX))
#define isAscii(c)	((unsigned int)(c) <= 0x7F)

#define toAscii(c)	((unsigned int)(c) & 0x7F)
#define toLower(c)	(isupper(c) ? c + 'a' - 'A' : c)
#define toUpper(c)	(islower(c) ? c + 'A' - 'a' : c)

#ifdef __cplusplus
}
#endif


#endif /* CTYPE_H */