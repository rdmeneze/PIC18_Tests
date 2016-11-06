#include "syslib.h"
#include "processor.h"
#include "clock.h"

/******************************************************************************/

UINT32 GetSystemClock( void )
{
    return CLOCK;
}

/******************************************************************************/

void HwInit(void)
{
    /* initialize and configure the clock system */
    ClockInit();
    
    /* Enable interrupt priority */
    RCONbits.IPEN = 1;
    
    /* Enable all high priority interrupts */
    INTCONbits.GIEH = 1;	    
    
    return;
}

/******************************************************************************/
