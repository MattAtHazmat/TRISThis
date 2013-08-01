/******************************************************************************/
/*                                                                            */
/* File:   tick.h                                                             */
/* Author: Matt Bennett                                                       */
/*                                                                            */
/* Created on June 13, 2012                                                   */
/* Description: Tick manager definitions                                      */
/*                                                                            */
/******************************************************************************/


#ifndef _TICK_H_
#define _TICK_H_

typedef UINT64 TICK_TYPE;

#define TICK_INTERRUPT_FLAG         (IFS0bits.T4IF)
#define TICK_INTERRUPT_ENABLE       (IEC0bits.T4IE)
#define mTickEnableInterrupt()      (TICK_INTERRUPT_ENABLE = 1)
#define mTickDisableInterrupt()     (TICK_INTERRUPT_ENABLE = 0)
#define mTickClearInterruptFlag()   (TICK_INTERRUPT_FLAG = 0)

#define TICK_UPDATE_RATE            1000 /* Hz */

#if ((FCY/TICK_UPDATE_RATE)<=0xFFFF)
    #define TICK_PRESCALER  T1_PS_1_1
    #define TICK_PRESCALER_VALUE    1
#elif ((FCY/(8*TICK_UPDATE_RATE))<=0xFFFF)
    #define TICK_PRESCALER  T1_PS_1_8
    #define TICK_PRESCALER_VALUE    8
#elif ((FCY/(64*TICK_UPDATE_RATE))<=0xFFFF)
    #define TICK_PRESCALER  T1_PS_1_64
    #define TICK_PRESCALER_VALUE    64
#elif ((FCY/(256*TICK_UPDATE_RATE))<=0xFFFF)
    #define TICK_PRESCALER  T1_PS_1_256
    #define TICK_PRESCALER_VALUE    256
#else
    #error "Can't define TICK_PRESCALER- tick update rate too low"
#endif

#define TICK_UPDATE_INTERVAL    (FCY/(TICK_PRESCALER_VALUE*TICK_UPDATE_RATE))

/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

void TickInitialize(void);
UINT64 TickGet(void);

#else
    #warning "Redundant include of tick.h"
#endif
