/* 
 * File:   clock.c
 * Author: rdias
 *
 * Created on 18 de maio de 2016, 22:44
 */

#include "clock.h"
#include "processor.h"

enum IOF_CLOCK
{
    IOF_8MHz    = 7,
    IOF_4MHz    = 6,
    IOF_2MHz    = 5,
    IOF_1MHz    = 4, 
    IOF_500kHz  = 3, 
    IOF_250kHz  = 2, 
    IOF_125kHz  = 1, 
    IOF_32kHz   = 0
};

/******************************************************************************/

void ClockInit( void )
{
    // disables reference oscillator output
    REFOCONbits.ROON = 0;
    
    // device enters IDLE mode on SLEEP instruction
    OSCCONbits.IDLEN = 1;     
    // system clock is from primary oscillator
    OSCCONbits.SCS = 0;  
    // selects base frequency as 8MHz
    OSCCONbits.IRCF = IOF_8MHz;        
    // wait until oscillator is running
    while( !OSCCONbits.OSTS );
    
    // low speed USB (6MHz clock)
    UCFGbits.FSEN = 0;     
    
    // enable PLL
    OSCTUNEbits.PLLEN = 1;       
      
    return;
}

/******************************************************************************/
