/* 
 * File:   softtimer.h
 * Author: rdias
 *
 * Created on June 10, 2015, 8:54 AM
 */

#ifndef SOFTTIMER_H
#define	SOFTTIMER_H

#include "defs.h"

typedef BYTE TIMERHANDLE;
#define TIMER_NULL_HANDLE   0xFF


/**
 * @brief   Initialize the softtimer engine
 * @param   dwTimerTick timer interrupt time in us
 * @return  success or fault status
 */
uint8_t STimerInit( const uint16_t wTimerTick_us );


/**
 * @brief   get a handle to a softtimer
 * @param   TimeMS
 * @return  timer handle ot TIMER_HANDLE_NUL
 */
TIMERHANDLE STimerGetTimer( const uint16_t TimeMS );

/**
 * @brief   verify if the timer is timeout
 * @param   hndTimer
 * @return  status of timeout
 */
uint8_t STimerIsTimeOut( const TIMERHANDLE hndTimer );

/**
 * @brief   reinitialize the timer counter
 * @param   hndTimer
 * @return  success or fault status
 */
uint8_t STimerRestart( const TIMERHANDLE hndTimer );

/**
 * @brief   release a timer
 * @param   hndTimer
 * @return  success or fault status
 */
uint8_t STimerRelease( const TIMERHANDLE hndTimer );

#endif	/* SOFTTIMER_H */

