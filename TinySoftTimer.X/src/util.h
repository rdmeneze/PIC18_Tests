/* 
 * File:   util.h
 * Author: rdias
 *
 * Created on November 20, 2014, 10:35 PM
 */

#ifndef UTIL_H
#define	UTIL_H

#include <GenericTypeDefs.h>

#define GET_ARRAY_LEN( x ) (sizeof(x)/sizeof(x[0]))

#define LOW_BYTE(x)     ((BYTE)((x)&0xFF))
#define HIGH_BYTE(x)    ((BYTE)(((x)>>8)&0xFF))
#define LOW_WORD(x)     ((WORD)((x)&0xFFFF))
#define HIGH_WORD(x)    ((WORD)(((x)>>16)&0xFFFF))

#endif	/* UTIL_H */
