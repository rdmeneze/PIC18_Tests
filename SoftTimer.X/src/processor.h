/* 
 * File:   processor.h
 * Author: rdmeneze
 *
 * Created on 14 de Novembro de 2014, 11:38
 */

#ifndef PROCESSOR_H
#define	PROCESSOR_H

#ifdef __18F26J50

#ifdef __DEBUG
#warning CPU is PIC18F26J50
#endif

#define CLOCK 48000000
#include "p18f26j50.h"

#else

#error WRONG microcontroller defined!

#endif

#endif	/* PROCESSOR_H */
