/******************************************************************************/
/* File:   configuration.h                                                    */
/* Author: Matt Bennett                                                       */
/*                                                                            */
/* Created on December 16, 2012, 4:36 PM                                      */
/******************************************************************************/

#ifndef _CONFIGURATION_H_
#define	_CONFIGURATION_H_
// DEVCFG3
// USERID = No Setting
#pragma config FSRSSEL = PRIORITY_7     // SRS Select (SRS Priority 7)
#pragma config FMIIEN = ON              // Ethernet RMII/MII Enable (MII Enabled)
#pragma config FETHIO = ON              // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config FCANIO = OFF              // CAN I/O Pin Select (Default CAN I/O)
#pragma config FUSBIDIO = OFF           // USB USID Selection (Controlled by Port Function)
#pragma config FVBUSONIO = OFF          // USB VBUS ON Selection (Controlled by Port Function)

// DEVCFG2
#if PLL_INPUT_DIVIDER==12
    #pragma config FPLLIDIV = DIV_12
#elif PLL_INPUT_DIVIDER==10
    #pragma config FPLLIDIV = DIV_10
#elif PLL_INPUT_DIVIDER==6
    #pragma config FPLLIDIV = DIV_6
#elif PLL_INPUT_DIVIDER==5
    #pragma config FPLLIDIV = DIV_5
#elif PLL_INPUT_DIVIDER==4
    #pragma config FPLLIDIV = DIV_4
#elif PLL_INPUT_DIVIDER==3
    #pragma config FPLLIDIV = DIV_3
#elif PLL_INPUT_DIVIDER==2
    #pragma config FPLLIDIV = DIV_2
#elif PLL_INPUT_DIVIDER==1
    #pragma config FPLLIDIV = DIV_1
#else
    #error "PLL_INPUT_DIVIDER not correctly defined"
#endif

#pragma config UPLLIDIV = DIV_12        // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF             // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)

// DEVCFG1
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = HS             // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = ON            // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#ifdef __DEBUG
    #pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
    #pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Enabled)
#else
    #pragma config WDTPS = PS512            // Watchdog Timer Postscaler (1:512)AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    #pragma config FWDTEN = ON              // Watchdog Timer Enable (WDT Enabled)
#endif /* __DEBUG */
// DEVCFG0
#ifdef __DEBUG
#pragma config DEBUG = ON               // Background Debugger Enable
#else
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#endif
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

#else
    #warning "Redundant include of configuration.h"
#endif	/* _CONFIGURATION_H_ */
