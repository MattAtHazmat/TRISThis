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

//#define TICK_INTERRUPT_FLAG         (IFS0bits.T4IF)
//#define TICK_INTERRUPT_ENABLE       (IEC0bits.T4IE)
//#define mTickEnableInterrupt()      IEC0SET=_IEC0_T4IE_MASK
//#define mTickDisableInterrupt()     IEC0CLR=_IEC0_T4IE_MASK
//#define mTickClearInterruptFlag()   IFS0CLR=_IFS0_T4IF_MASK

#define TICK_UPDATE_RATE            1000 /* Hz */
#define TICKS_PER_MS                1

#if ((GetPeripheralClock()/TICK_UPDATE_RATE)<=0xFFFF)
    #define TICK_PRESCALER  T1_PS_1_1
    #define TICK_PRESCALER_VALUE    1
#elif ((GetPeripheralClock()/(8*TICK_UPDATE_RATE))<=0xFFFF)
    #define TICK_PRESCALER  T1_PS_1_8
    #define TICK_PRESCALER_VALUE    8
#elif ((GetPeripheralClock()/(64*TICK_UPDATE_RATE))<=0xFFFF)
    #define TICK_PRESCALER  T1_PS_1_64
    #define TICK_PRESCALER_VALUE    64
#elif ((GetPeripheralClock()/(256*TICK_UPDATE_RATE))<=0xFFFF)
    #define TICK_PRESCALER  T1_PS_1_256
    #define TICK_PRESCALER_VALUE    256
#else
    #error "Can't define TICK_PRESCALER- tick update rate too low"
#endif

#define TICK_UPDATE_INTERVAL    (GetPeripheralClock()/(TICK_PRESCALER_VALUE*TICK_UPDATE_RATE))

/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

void TickInitialize(void);
UINT64 TickGet(void);

#else
    #warning "Redundant include of tick.h"
#endif
