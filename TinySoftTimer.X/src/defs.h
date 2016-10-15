/* 
 *  @file:      defs.h
 *  @author:    Rafael Dias <rafael.dias@silicaconsulting.com>
 *
 *  @date:      October 29, 2014, 10:49 PM
 *  @brief:     soeme definitions about datatypes 
 */

#ifndef DEFS_H
#define	DEFS_H

#ifdef __18CXX
#include <GenericTypeDefs.h>
#else
#error NEED DEFINES FOR DATATYPES!
#endif

#define DIGITAL_INPUT  1
#define DIGITAL_OUTPUT 0

typedef BYTE uint8_t;
typedef UINT16 uint16_t;
typedef UINT16 WORD;

#endif	/* DEFS_H */
