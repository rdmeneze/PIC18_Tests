/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef P18F_TIMER_REGS_H
#define	P18F_TIMER_REGS_H

#include "processor.h"

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

//------------------------------------------------------------------------------
typedef enum 
{
    T0PS_PREESC_1_2      = 0, 
    T0PS_PREESC_1_4      = 1, 
    T0PS_PREESC_1_8      = 2, 
    T0PS_PREESC_1_16     = 3, 
    T0PS_PREESC_1_32     = 4, 
    T0PS_PREESC_1_64     = 5, 
    T0PS_PREESC_1_128    = 6, 
    T0PS_PREESC_1_256    = 7 
} TIMER0_T0PS;

typedef enum
{
    TMR0ON_ON = 1, 
    TMR0ON_OFF = 0             
} TIMER0_TMR0ON;

typedef enum
{
    T08BIT_LEN_8 = 1, 
    T08BIT_LEN_16 = 0
} TIMER0_T08BIT;

typedef enum 
{
    T0CS_INT     = 0,
    T0CS_T0CKI   = 1
}TIMER0_T0CS;

typedef enum 
{
    T0SE_LH_T0CKI = 0, 
    T0SE_HL_T0CKI = 1 
}TIMER0_T0SE;

typedef enum 
{
    PSA_PREESC_ASSIGN = 0,
    PSA_PREESC_NOT_ASSIGN = 1
} TIMER0_PSA;    
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* P18F_TIMER_REGS_H */

