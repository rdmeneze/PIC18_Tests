/* 
 * File:   Timer.h
 * Author: rdias
 *
 * Created on November 6, 2016, 11:55 AM
 */

#ifndef TIMER_H
#define	TIMER_H

#include "defs.h"
#include "error.h"

#ifdef	__cplusplus
extern "C" {
#endif

enum TIMER
{
    TIMER0,
    TIMER1,
    TIMER2,
    TIMER3,
    TIMER_NULL
};

#define TIMER_LEN TIMER_NULL

/**
 * @brief initialize hardware timers
 * @param tm timer to initialize
 * @returns ERROR_SUCCESS on success
 * @returns ERROR_NOT_IMPLEMENTED on ERROR
 * 
 */
BYTE TimerInit( enum TIMER tm , WORD interval );

/**
 * @brief do a timer tick
 * @param tm timer to update
 */
void TimerTick( enum TIMER tm );

/**
 * @brief get the timer counter
 * @param tm timer to get
 * @return timer counter
 */
WORD GetTimerTick( enum TIMER tm );

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

