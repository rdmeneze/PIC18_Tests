/* 
 * File:   fuses.h
 * Author: rdias
 *
 * Created on November 3, 2015, 9:55 PM
 */

#ifndef FUSES_H
#define	FUSES_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifdef __18CXX

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1L

#ifdef __DEBUG
    #pragma config WDTEN = OFF      // Watchdog Timer (disabled)
#else
    #pragma config WDTEN = ON       // Watchdog Timer (enabled)
#endif

#pragma config PLLDIV = 2       // PLL Prescaler Selection bits (Divide by 2 (8 MHz internal oscillator input))
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset  (Enabled)
#pragma config XINST = OFF       // Extended Instruction Set (Enabled)

// CONFIG1H
#pragma config CPUDIV = OSC1    // CPU System Clock Postscaler (CPU system clock divide by 2)
#pragma config CP0 = OFF        // Code Protect (Program memory is not code-protected)

// CONFIG2L
#pragma config OSC = INTOSCPLL  // Oscillator (INTOSCPLL)
#pragma config T1DIG = OFF      // T1OSCEN Enforcement (Secondary Oscillator clock source may be selected)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator (High-power operation)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Enabled)
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Enabled)

// CONFIG2H
#pragma config WDTPS = 32768    // Watchdog Postscaler (1:32768)

// CONFIG3L
#pragma config DSWDTOSC = INTOSCREF // DSWDT Clock Select (DSWDT uses INTRC)
#pragma config RTCOSC = T1OSCREF    // RTCC Clock Select (RTCC uses T1OSC/T1CKI)
#pragma config DSBOREN = OFF        // Deep Sleep BOR (Enabled)
#pragma config DSWDTEN = OFF        // Deep Sleep Watchdog Timer (Enabled)
#pragma config DSWDTPS = G2         // Deep Sleep Watchdog Postscaler (1:2,147,483,648 (25.7 days))

// CONFIG3H
#pragma config IOL1WAY = OFF     // IOLOCK One-Way Set Enable bit (The IOLOCK bit (PPSCON<0>) can be set/cleared as needed)
#pragma config MSSP7B_EN = MSK7  // MSSP address masking (7 Bit address masking mode)

// CONFIG4L
#pragma config WPFP = PAGE_63    // Write/Erase Protect Page Start/End Location (Write Protect Program Flash Page 63)
#pragma config WPEND = PAGE_WPFP // Write/Erase Protect Region Select (valid when WPDIS = 0) (Page WPFP<5:0> through Configuration Words erase/write protected)
#pragma config WPCFG = OFF       // Write/Erase Protect Configuration Region (Configuration Words page not erase/write-protected)

// CONFIG4H
#pragma config WPDIS = OFF       // Write Protect Disable bit (WPFP<5:0>/WPEND region ignored)

#endif // #ifdef __18CXX

#ifdef	__cplusplus
}
#endif

#endif	/* FUSES_H */

