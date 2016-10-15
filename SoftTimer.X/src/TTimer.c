#include "ttimer.h"
#include "sysLib.h"
#include "util.h"
#include "p18f_timer_regs.h"
#include "error.h"

/*----------------------------------------------------------------------------*/

#define TIMER_ENTRY_CB      8
#define TIMER_ENTRY_NULL    0

#define TIMER_TIMEBASE_us (GetSystemClock() / 1000000.)
#define TIMER_TIMEBASE_ms (GetSystemClock() / 1000.)

#define TIMER_HANDLE_INITIAL_VALUE  (0xEEDF)
#define TICK_TO_US 1000000L

/*----------------------------------------------------------------------------*/

BYTE Timer0Init( WORD wTimeInterval );
WORD wReloadTimer[1];

/*----------------------------------------------------------------------------*/
/**
 * @brief TTimer control struct
 */
struct STTimer
{
  BYTE          dwHandle;            /**< TTimer system identification */
  INT16         iCount;              /**< counter control              */
  INT16         iReloadValue;        /**< reload value. Used by reload timer      */
  TimerType     type;                /**< type of timer: retriggerable or oneshot */
  void*         lpParam;             /**< parameter to be passed to callback function */
  uint8_t       bStarted;            /**< signalize that the timer is started     */
  callbacktimer_func   callback_func;  /**< callback function */
};

/*----------------------------------------------------------------------------*/
//! local declarations
static  DWORD dwTimerTimeBase = 0;
static  BYTE  bInit = 0;
static DWORD  dwHandleCount = 0;
static struct STTimer stCBTimer[TIMER_ENTRY_CB];
static BYTE   bInstanceCounter = 0;
/*----------------------------------------------------------------------------*/
//! timer ISR
void Timer_ISR_Handler( void );
/*----------------------------------------------------------------------------*/

void TTimerCfgTimeOut( DWORD dwTimeMicro )
{    
    if ( dwTimeMicro < 10 )
    {
        dwTimeMicro = 10;
    }
 
    if ( !bInit )
    {
        DWORD dwCounter = 0;
        struct STTimer * pTTimer = &stCBTimer[0];
        
        for( ; dwCounter < GET_ARRAY_LEN( stCBTimer ); dwCounter++, pTTimer++ )
        {
            pTTimer->dwHandle       = TIMER_ENTRY_NULL;
            pTTimer->iCount         = 0;
            pTTimer->iReloadValue   = 0;
            pTTimer->type           = TimerOneShot;
            pTTimer->lpParam        = NULL;
            pTTimer->callback_func  = NULL;
            pTTimer->bStarted       = 0;
        }    

        /* hardware timer initialization */
        Timer0Init( dwTimeMicro );
        
        bInit = 1;
    }
   
    dwTimerTimeBase = dwTimeMicro;
    
    return;
}

/*----------------------------------------------------------------------------*/

DWORD TTimerGetTimeBase( void )
{
    return dwTimerTimeBase;
}

/*----------------------------------------------------------------------------*/

BYTE TTimerRegisterCallBack( DWORD dwDelay, TimerType type, callbacktimer_func callback_func, void* lpParam, UINT16* cbHandle )
{
    int i;
    int count;
    struct STTimer * pTTimer;
    
    if ( !bInit )
    {
      /* the library isn't initialized  */
      return ERROR_OP_NOT_ALLOWED;
    }
    
    if ( callback_func == NULL )
    {
      /* invalid parameter */
      return ERROR_OP_NOT_ALLOWED;
    }
    
    if ( bInstanceCounter++ > TIMER_ENTRY_CB )
    {
      /* exceed the timers limit. See at the TIMER_ENTRY_CB macro  */
      return ERROR_LIMIT_EXCEEDED;
    }
    
    if ( dwDelay < dwTimerTimeBase )
    {
      dwDelay = dwTimerTimeBase;
    }
    
    count = (DWORD)((dwDelay / (float)dwTimerTimeBase) + 0.5f);
    
    for ( pTTimer = stCBTimer, i = 0; i < GET_ARRAY_LEN( stCBTimer ); i++, pTTimer++ )
    {
        if ( pTTimer->dwHandle == TIMER_ENTRY_NULL )
        {
            pTTimer->dwHandle       = (TIMER_HANDLE_INITIAL_VALUE) + (++dwHandleCount);
            pTTimer->iReloadValue   = count;            
            pTTimer->iCount         = pTTimer->iReloadValue;
            pTTimer->type           = (TimerType)type;
            pTTimer->lpParam        = lpParam;
            pTTimer->callback_func  = callback_func;
            pTTimer->bStarted       = 0;
            
            break;
        }
    }
    
    if ( i == GET_ARRAY_LEN( stCBTimer ) )
    {
        return ERROR_VALUE_OUT_OF_RANGE;
    }
    
    if ( cbHandle != NULL )
    {
        *cbHandle = pTTimer->dwHandle;
    }
    
    return ERROR_SUCCESS;
}

/*----------------------------------------------------------------------------*/

BYTE TTimerUnregisterCallBack( UINT16 dwHandle )
{
    int i;
    struct STTimer * pTTimer;
    
    for ( pTTimer = stCBTimer, i = 0; i < GET_ARRAY_LEN( stCBTimer ); i++, pTTimer++ )
    {
        if ( pTTimer->dwHandle == dwHandle )
        {
            pTTimer->dwHandle       = TIMER_ENTRY_NULL;
            pTTimer->iCount        = 0;
            pTTimer->iReloadValue  = 0;
            pTTimer->type           = TimerOneShot;
            pTTimer->lpParam        = NULL;
            pTTimer->callback_func  = NULL;
            pTTimer->bStarted       = 0;
            
            break;
        }
    }
    
    if ( i == GET_ARRAY_LEN( stCBTimer ) )
    {
        return ERROR_VALUE_OUT_OF_RANGE;
    }
    
    bInstanceCounter--;
    
    return 0;
}

/*----------------------------------------------------------------------------*/

void Timer_ISR_Handler( void )
{
    int i;
    struct STTimer * pTTimer;
    BYTE dwExecuteCBFlag = 0;
    BYTE dwCBRet = 0;
    
    for ( i = 0, pTTimer = stCBTimer; i < GET_ARRAY_LEN( stCBTimer ); i++, pTTimer++ )
    {
        if ( pTTimer->dwHandle != TIMER_ENTRY_NULL )
        {
            if ( pTTimer->bStarted )
            {
                pTTimer->iCount--;
                if ( !dwExecuteCBFlag )
                {
                    if ( pTTimer->iCount <= 0 )
                    {
                        if ( pTTimer->callback_func != NULL )
                        {
                            dwExecuteCBFlag = 1;
                            
                            dwCBRet = pTTimer->callback_func( pTTimer->lpParam );	// execute the callback code
                            
                            if ( dwCBRet )
                            {
                                // an error ocurred in the call back execution
                                TTimerUnregisterCallBack( pTTimer->dwHandle );
                                continue;
                            }
                            
                            if ( pTTimer->type == TimerPeriodic )
                            {
                                pTTimer->iCount = pTTimer->iReloadValue;
                            }
                            else
                            {
                                pTTimer->bStarted = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    
    return;
}

/*----------------------------------------------------------------------------*/

BYTE TTimerStart( UINT16 dwHandle )
{
    int i;
    struct STTimer* pTTimer;
    
    for ( i = 0, pTTimer = stCBTimer; i < GET_ARRAY_LEN( stCBTimer ); i++, pTTimer++ )
    {
        if ( pTTimer->dwHandle == dwHandle )
        {
            pTTimer->iCount    = pTTimer->iReloadValue;
            pTTimer->bStarted  = 1;
            break;
        }
    }
    
    if ( i == GET_ARRAY_LEN( stCBTimer ) )
    {
        return ERROR_VALUE_OUT_OF_RANGE;
    }
    
    return 0;
}

/*----------------------------------------------------------------------------*/        

BYTE TTimerStop( UINT16 dwHandle )
{
    int i;
    struct STTimer* pTTimer;
    
    for ( i = 0, pTTimer = stCBTimer; i < GET_ARRAY_LEN( stCBTimer ); i++, pTTimer++ )
    {
        if ( pTTimer->dwHandle == dwHandle )
        {
            pTTimer->bStarted  = 0;
            break;
        }
    }
    
    if ( i == GET_ARRAY_LEN( stCBTimer ) )
    {
        return ERROR_VALUE_OUT_OF_RANGE;
    }
    
    return 0;
}

/*----------------------------------------------------------------------------*/        

BYTE TTimerRestart( UINT16 dwHandle )
{
    DWORD dwRet = TTimerStop( dwHandle );
    
    if ( !dwRet )
    {
      dwRet = TTimerStart( dwHandle );
    }
    return dwRet;
}

/*----------------------------------------------------------------------------*/        

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
    
    wReloadTimer[0] = iTmp;
    
    TMR0L = (-wReloadTimer[0] + 1);
        
    T0CONbits.TMR0ON = TMR0ON_ON;            //! turn on
    INTCONbits.GIE = 1;
    
    rc = ERROR_SUCCESS;

    return rc;
}

//------------------------------------------------------------------------------
