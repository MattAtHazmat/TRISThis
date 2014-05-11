/******************************************************************************/
/* File: Delay.h                                                              */
/* Author: Matt Bennett                                                       */
/* Date: December 26, 2011                                                    */
/* Version: 0.9                                                               */
/*                                                                            */
/* Description: defines related to the delay functions                        */
/*                                                                            */
/******************************************************************************/

#ifndef __DELAY_H_
#define __DELAY_H_

#ifdef DELAY_USE_CORE_TIMER

#define CORE_TIMER_FREQUENCY            (GetSystemClock()/2)
#define CORE_TIMER_MILLISECONDS         (CORE_TIMER_FREQUENCY/1000)
#define CORE_TIMER_MICROSECONDS         (CORE_TIMER_FREQUENCY/1000000)

#define DelayUS CoreTimer_DelayUS
#endif

/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

void DelayMs(UINT32);
void DelayUS(UINT32);


#endif
