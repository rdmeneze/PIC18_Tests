
#include "sysLib.h"
#include "softtimer.h"
#include "util.h"
#include "p18f_timer_regs.h"
#include "error.h"

//------------------------------------------------------------------------------

#define NUM_TIMER           8
#define TIMER_HANDLE_OFFSET 0x10

//------------------------------------------------------------------------------

typedef void(*timercb)(void);

struct STimer
{
    TIMERHANDLE handle;
    WORD        count;
    WORD        value;
};

//------------------------------------------------------------------------------

volatile WORD wTimerTick = 0;       /*<! interrupt counter */
struct STimer timer[NUM_TIMER];     /*<! timer structure */
static BYTE bInit = 0;              
static WORD wSTimerTimeInterval = 100;

//------------------------------------------------------------------------------

timercb tcb[1];
WORD wReloadTimer[1];

#define TIMER0 0
#define TICK_TO_US 1000000L

//------------------------------------------------------------------------------

BYTE Timer0Init( WORD wTimeInterval );

//------------------------------------------------------------------------------

void TimerTick( void )
{
    wTimerTick++;
}

//------------------------------------------------------------------------------

DWORD GetTimerTick( void )
{
    return wTimerTick;
}

//------------------------------------------------------------------------------

BYTE STimerInit( WORD wTimerTick_us )
{
    BYTE bRet = 0;
    BYTE bCount;
    struct STimer *pTimer;
    
    for ( bCount = 0, pTimer = &timer[0]; bCount < GET_ARRAY_LEN( timer ); bCount++, pTimer++ )
    {        
        pTimer->handle  = TIMER_NULL_HANDLE;
        pTimer->count   = 0;
        pTimer->value   = 0;            
    }    
    
    if ( !bInit )
    {
        bRet = Timer0Init( wTimerTick_us );
        
        if ( !bRet )
        {
            bInit = 1;
        }
    }    
    return bRet;
}

//------------------------------------------------------------------------------

TIMERHANDLE STimerGetTimer( WORD TimeMS )
{
    BYTE bCount;
    struct STimer* pTimer;
    WORD dwTimeCount;    
    TIMERHANDLE handle = TIMER_NULL_HANDLE;
    
    dwTimeCount = (TimeMS*1000)/wSTimerTimeInterval;
    
    for ( bCount = 0, pTimer = &timer[0]; bCount < GET_ARRAY_LEN( timer ); bCount++, pTimer++ )
    {
        if ( pTimer->handle == TIMER_NULL_HANDLE )
        {
            pTimer->handle  = (bCount + TIMER_HANDLE_OFFSET);
            pTimer->count   = dwTimeCount + GetTimerTick();
            pTimer->value   = dwTimeCount;
            
            handle = pTimer->handle;
            break;
        }
    }
    
    return handle;
}
        
//------------------------------------------------------------------------------        

BYTE STimerIsTimeOut( TIMERHANDLE hndTimer )
{
    BYTE bCount;
    struct STimer* pTimer;
    
    for ( bCount = 0, pTimer = &timer[0]; bCount < GET_ARRAY_LEN( timer ); bCount++, pTimer++ )
    {
        if ( pTimer->handle == hndTimer )
        {
            if ( pTimer->count < GetTimerTick() )
            {
               return TRUE; 
            }
            break;
        }
    }
    return FALSE;
}

//------------------------------------------------------------------------------

BYTE STimerRelease( TIMERHANDLE hndTimer )
{
    BYTE bCount;
    struct STimer* pTimer;
    
    for ( bCount = 0, pTimer = &timer[0]; bCount < GET_ARRAY_LEN( timer ); bCount++, pTimer++ )
    {
        if ( pTimer->handle == hndTimer )
        {
            pTimer->handle  = TIMER_NULL_HANDLE;
            pTimer->count   = 0;
            pTimer->value   = 0;
            
            return TRUE;
        }
    }
    return FALSE;
}

//------------------------------------------------------------------------------

BYTE STimerRestart( TIMERHANDLE hndTimer )
{
    BYTE bCount;
    struct STimer* pTimer;
    
    for ( bCount = 0, pTimer = &timer[0]; bCount < GET_ARRAY_LEN( timer ); bCount++, pTimer++ )
    {
        if ( pTimer->handle == hndTimer )
        {
            pTimer->count   = pTimer->value + GetTimerTick();
            
            return TRUE;
        }
    }
    return FALSE;    
}

//------------------------------------------------------------------------------

BYTE Timer0Init( WORD wTimeInterval )
{
    INT8 iTmp;
    float timTick_us;
    INT8 rc = ERROR_INVALID_COMMAND;

    INTCONbits.GIE = 0;

    //! configure the timer 0 for 16 bit mode and preescaler of 1/256
    T0CONbits.TMR0ON    = TMR0ON_OFF;           //! turn off
    T0CONbits.T08BIT    = T08BIT_LEN_8;        //! select the 8 bit mode
    T0CONbits.T0CS      = T0CS_INT;             //! internal clock 
    T0CONbits.PSA       = PSA_PREESC_ASSIGN;    //! use the preescaler
    T0CONbits.T0PS      = T0PS_PREESC_1_4;     //! 1/2 preescaler
    
    INTCON2bits.TMR0IP = 1;                     //! high priority for TMR0 interruption

    INTCONbits.TMR0IF   = 0;                    //! clear the interrupt flag
    INTCONbits.TMR0IE   = 1;
    
    TMR0H        = 0;
    TMR0L        = 0;
    
    timTick_us = (GetSystemClock() / (4 * (1 << (T0CONbits.T0PS + 1 ) )));
    timTick_us /= TICK_TO_US;
    
    iTmp = ((((float)wTimeInterval)/timTick_us) + 0.5);
    
    wReloadTimer[TIMER0] = iTmp;
    
    TMR0L = (-wReloadTimer[TIMER0] + 1);
    
    wSTimerTimeInterval = wTimeInterval;
        
    T0CONbits.TMR0ON = TMR0ON_ON;            //! turn on
    INTCONbits.GIE = 1;
    
    rc = ERROR_SUCCESS;

    return rc;
}

//------------------------------------------------------------------------------
