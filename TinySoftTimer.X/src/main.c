/* 
 * File:   main.c
 * Author: rdias
 *
 * Created on October 14, 2016, 9:32 PM
 */

#include <p18f26j50.h>

#include "fuses.h"
#include "softtimer.h"
#include "error.h"
#include "interrupt.h"
#include "sysLib.h"

/*
 * 
 */
void main(void) 
{
    TIMERHANDLE handle;    
    BYTE rc;  
    
    HwInit( );
    
    rc = STimerInit( 500 );
    if ( ERROR_SUCCESS != rc )
    {
        errorFatal( ERROR_NOT_READY );
    }
    
    handle = STimerGetTimer( 2 );
    if ( TIMER_NULL_HANDLE == handle )
    {
        errorFatal( ERROR_NOT_READY );        
    }

    ANCON0bits.PCFG0 = 1;   /* configura RA0 como IO digital */
    TRISAbits.TRISA0 = 0;   /* RA0 saida */
    LATAbits.LATA0   = 0;
    
    for ( ;; )
    {
        if ( STimerIsTimeOut( handle ))
        {
            LATAbits.LATA0 = !PORTAbits.RA0;
            STimerRestart( handle );
        }
    }
}

