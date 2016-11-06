
#include <usart.h>
#include "interrupt.h"
#include "defs.h"
#include "softtimer.h"
#include "util.h"
#include "error.h"
#include "Timer.h"

/*----------------------------------------------------------------------------*/
/* foward declarations */
void high_isr(void);
void low_isr (void);

/*----------------------------------------------------------------------------*/
/* external objects */
extern WORD wReloadTimer[TIMER_LEN];

//------------------------------------------------------------------------------
#pragma code low_vector=0x18
void interrupt_at_low_vector(void)
{
      _asm GOTO low_isr _endasm
 }
 #pragma code /* return to the default code section */
 #pragma interruptlow low_isr
 void low_isr (void)
 {
      Nop();
 }
//------------------------------------------------------------------------------

/* 
 * For PIC18 devices the high interrupt vector is found at
 * 00000008h. The following code will branch to the
 * high_interrupt_service_routine function to handle
 * interrupts that occur at the high vector.
 */
#pragma code high_vector=0x08
VOID interrupt_at_high_vector( VOID )
{
  _asm GOTO high_isr _endasm
}
#pragma code /* return to the default code section */

#pragma interrupt high_isr
void high_isr (void)
{
    if ( INTCONbits.TMR0IF )
    {
        TMR0H = HIGH_BYTE(wReloadTimer[TIMER0]);
        TMR0L = LOW_BYTE(wReloadTimer[TIMER0]);        
                
        TimerTick( TIMER0 ); // calls the timer0 callback function
        
        INTCONbits.TMR0IF = 0;
    }
    
    // put other high priority interruption handling code here    
}
