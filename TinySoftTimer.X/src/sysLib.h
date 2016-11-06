#ifndef _SYSLIB_H_
#define _SYSLIB_H_

#include "defs.h"

/**
 * @brief hardware initialization
 */
void HwInit(void);

/**
 * @brief get the configurated system clock
 * @return microcontroller clock
 */
UINT32 GetSystemClock( void );

#endif