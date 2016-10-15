/* 
 * File:   main.c
 * Author: rdias
 *
 * Created on October 14, 2016, 9:32 PM
 */

#include <p18f26j50.h>

#include "fuses.h"
#include "ttimer.h"
#include "error.h"
#include "interrupt.h"

/******************************************************************************/

BYTE LedTask( void* lParam );

/******************************************************************************/

/*
 * 
 */
int main(int argc, char** argv) 
{ 
    BYTE rc =  interruptsInit( );
    UINT16 handle;

    if ( ERROR_SUCCESS != rc )
    {
        errorFatal( ERROR_NOT_READY );
    }   
   
    TTimerCfgTimeOut( 100 );

    ANCON0bits.PCFG0 = 1;   /* configura RA0 como IO digital */
    TRISAbits.TRISA0 = 0;   /* RA0 saida */
    LATAbits.LATA0   = 0;
    
    TTimerRegisterCallBack( TTIMER_1MS_INTERVAL, TimerPeriodic, LedTask, NULL, &handle );
    
    TTimerStart( handle );
    
    for ( ;; );

    return (0);
}

/******************************************************************************/

BYTE LedTask( void* lParam )
{
    (void)lParam;
    
    LATAbits.LATA0 = !PORTAbits.RA0;
    
    return 0;
}

/******************************************************************************/




