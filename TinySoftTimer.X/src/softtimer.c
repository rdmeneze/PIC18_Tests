
#include "sysLib.h"
#include "softtimer.h"
#include "util.h"
#include "error.h"
#include "Timer.h"

//------------------------------------------------------------------------------

#define NUM_TIMER           8
#define TIMER_HANDLE_OFFSET 0x10

//------------------------------------------------------------------------------

typedef void(*timercb)(void);

/**
 * @typedef STimer
 * @brief hold the timer control variables
 */
struct STimer
{
    TIMERHANDLE handle; /* the timer unique ID  */
    WORD        count;  /* counter              */
    WORD        value;  /* timer value          */
};

//------------------------------------------------------------------------------

struct STimer timer[NUM_TIMER];     /*<! timer structure */
static BYTE bInit = 0;              
static WORD wSTimerTimeInterval = 100;

//------------------------------------------------------------------------------

BYTE STimerInit( const uint16_t wTimerTick_us )
{
    BYTE bRet = 0;
    BYTE bCount;
    struct STimer *pTimer;

    if ( !bInit )
    {
        for ( bCount = 0, pTimer = &timer[0]; bCount < GET_ARRAY_LEN( timer ); bCount++, pTimer++ )
        {        
            pTimer->handle  = TIMER_NULL_HANDLE;
            pTimer->count   = 0;
            pTimer->value   = 0;            
        }    
    
        bRet = TimerInit( TIMER0, wTimerTick_us );
        
        if ( !bRet )
        {
            wSTimerTimeInterval = wTimerTick_us;
            bInit = 1;
        }
    }    
    return bRet;
}

//------------------------------------------------------------------------------

TIMERHANDLE STimerGetTimer( const uint16_t TimeMS )
{
    BYTE bCount;
    struct STimer* pTimer;
    WORD dwTimeCount;    
    TIMERHANDLE handle = TIMER_NULL_HANDLE;
    
    if ( bInit )
    {    
        dwTimeCount = (TimeMS*1000)/wSTimerTimeInterval;

        for ( bCount = 0, pTimer = &timer[0]; bCount < GET_ARRAY_LEN( timer ); bCount++, pTimer++ )
        {
            if ( pTimer->handle == TIMER_NULL_HANDLE )
            {
                pTimer->handle  = (bCount + TIMER_HANDLE_OFFSET);
                pTimer->count   = dwTimeCount + GetTimerTick(TIMER0);
                pTimer->value   = dwTimeCount;

                handle = pTimer->handle;
                break;
            }
        }
    }
    
    return handle;
}
        
//------------------------------------------------------------------------------        

BYTE STimerIsTimeOut( const TIMERHANDLE hndTimer )
{
    BYTE bCount;
    struct STimer* pTimer;
    BYTE bTimeOut = FALSE;
    
    if ( bInit )
    {    
        for ( bCount = 0, pTimer = &timer[0]; bCount < GET_ARRAY_LEN( timer ); bCount++, pTimer++ )
        {
            if ( hndTimer == pTimer->handle )
            {
                if ( pTimer->count < GetTimerTick(TIMER0) )
                {
                   bTimeOut = TRUE; 
                }
                break;
            }
        }
    }
    return bTimeOut;
}

//------------------------------------------------------------------------------

BYTE STimerRelease( const TIMERHANDLE hndTimer )
{
    BYTE bCount;
    struct STimer* pTimer;
    BYTE bRet = FALSE;
    
    if ( bInit )
    {
        for ( bCount = 0, pTimer = &timer[0]; bCount < GET_ARRAY_LEN( timer ); bCount++, pTimer++ )
        {
            if ( hndTimer == pTimer->handle )
            {
                pTimer->handle  = TIMER_NULL_HANDLE;
                pTimer->count   = 0;
                pTimer->value   = 0;

                bRet = TRUE;
                break;
            }
        }
    }
    
    return bRet;
}

//------------------------------------------------------------------------------

BYTE STimerRestart( const TIMERHANDLE hndTimer )
{
    BYTE bCount;
    struct STimer* pTimer;
    BYTE bRet = FALSE;
    
    if ( bInit )
    {
        for ( bCount = 0, pTimer = &timer[0]; bCount < GET_ARRAY_LEN( timer ); bCount++, pTimer++ )
        {
            if ( hndTimer == pTimer->handle )
            {
                pTimer->count   = pTimer->value + GetTimerTick(TIMER0);

                bRet =  TRUE;
                break;
            }
        }
    }
    return bRet;    
}

//------------------------------------------------------------------------------


