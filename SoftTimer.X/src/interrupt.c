
#include <usart.h>
#include "interrupt.h"
#include "defs.h"
#include "util.h"
#include "error.h"

/*----------------------------------------------------------------------------*/

VOID high_isr(VOID);

/*----------------------------------------------------------------------------*/

extern void Timer_ISR_Handler( void );
extern WORD wReloadTimer[1];

/*----------------------------------------------------------------------------*/

INT8 interruptsInit( VOID )
{
    INT8 rc = ERROR_SUCCESS;
    
    /* Enable interrupt priority */
    RCONbits.IPEN = 1;

    /* Enable all high priority interrupts */
    INTCONbits.GIEH = 1;	
    
    /* Make receive interrupt high priority */
    IPR1bits.RCIP = 1;

    /* Enable RX interrupt on USART 1 */
    PIE1bits.RC1IE = 1;        
    
    return rc;
}

//------------------------------------------------------------------------------
// #pragma code low_vector=0x18
// void interrupt_at_low_vector(void)
// {
//      _asm GOTO low_isr _endasm
// }
// #pragma code /* return to the default code section */
// #pragma interruptlow low_isr
// void low_isr (void)
// {
//      Nop();
// }
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
VOID high_isr (VOID)
{
    if ( INTCONbits.TMR0IF )
    {
        //TMR0H   = HIGH_BYTE((WORD)(-wReloadTimer[0]+1));
        TMR0L   = LOW_BYTE((WORD)(-wReloadTimer[0]+1));   

        Timer_ISR_Handler();
        
        INTCONbits.TMR0IF = 0;
    }
    
    // put other high priority interruption handling code here    
}
