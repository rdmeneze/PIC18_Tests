#include "Timer.h"
#include "p18f_timer_regs.h"
#include "sysLib.h"
#include "util.h"

/******************************************************************************/

#define TICK_TO_US 1000000L

/******************************************************************************/

//timercb tcb[TIMER_LEN];
WORD wReloadTimer[TIMER_LEN];
volatile WORD wTimerTick[TIMER_LEN];       /*<! interrupt counter */

/******************************************************************************/

void Timer0Init( WORD wTimeInterval )
{
    INT16 iTmp;
    UINT32 timTick_us;

    INTCONbits.GIEH = 0;                        /* turn off the high priority interrupts */

    //! configure the timer 0 for 16 bit mode and preescaler of 1/256
    T0CONbits.TMR0ON    = TMR0ON_OFF;       //! turn off
    T0CONbits.T08BIT    = T08BIT_LEN_16;     //! select the 8 bit mode
    T0CONbits.T0CS      = T0CS_INT;         //! internal clock 
    T0CONbits.PSA       = PSA_PREESC_ASSIGN;//! use the preescaler
    T0CONbits.T0PS      = T0PS_PREESC_1_4;  //! 1/2 preescaler
    
    INTCON2bits.TMR0IP = 1;                 //! high priority for TMR0 interruption

    INTCONbits.TMR0IF   = 0;                //! clear the interrupt flag
    INTCONbits.TMR0IE   = 1;
    
    TMR0H        = 0;
    TMR0L        = 0;
    
    timTick_us = (GetSystemClock() / (4 * (1 << (T0CONbits.T0PS + 1 ) )));
    timTick_us /= TICK_TO_US;
    
    iTmp = ((((float)wTimeInterval)/timTick_us) + 0.5);
    
    wReloadTimer[TIMER0] = (WORD)(-iTmp + 1);
    
    TMR0H = HIGH_BYTE(wReloadTimer[TIMER0]);
    TMR0L = LOW_BYTE(wReloadTimer[TIMER0]);
    
    T0CONbits.TMR0ON = TMR0ON_ON;            //! turn on
    INTCONbits.GIEH = 1;    
}

/******************************************************************************/

void TimerTick( enum TIMER tm )
{
    switch( tm )
    {
        case TIMER0:
            wTimerTick[TIMER0]++;
            break;
        case TIMER1:
            wTimerTick[TIMER1]++;
            break;
        case TIMER2:
            wTimerTick[TIMER2]++;
            break;
        case TIMER3:
            wTimerTick[TIMER3]++;
            break;
    }
}

/******************************************************************************/

WORD GetTimerTick( enum TIMER tm )
{
    switch( tm )
    {
        case TIMER0:
            return wTimerTick[TIMER0];
        case TIMER1:
            return wTimerTick[TIMER1];
        case TIMER2:
            return wTimerTick[TIMER2];
        case TIMER3:
            return wTimerTick[TIMER3];
    }
}

/******************************************************************************/

BYTE TimerInit( enum TIMER tm , WORD interval  )
{
    BYTE bRet = ERROR_NOT_IMPLEMENTED;
    
    switch( tm )
    {
        case TIMER0:
        {
            Timer0Init( interval );
            bRet = ERROR_SUCCESS;
            break;
        }
        
        case TIMER1:
        case TIMER2:
        case TIMER3:
        default:
            break;
    }
    return bRet;
}

/******************************************************************************/