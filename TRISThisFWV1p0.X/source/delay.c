/******************************************************************************/
/* File: delay.c                                                              */
/* Author: Matt Bennett                                                       */
/* Date: December 26, 2011                                                    */
/* Version: 0.9                                                               */
/*                                                                            */
/* Description: Functions to access a real time timer, derived from 'tick'    */
/*                                                                            */
/******************************************************************************/

#include "common.h"
#include "tick.h"
#include "delay.h"

/******************************************************************************/
/* DelayMs(int toWait)                                                        */
/*  wait between toWait and toWait+1 milliseconds. Added the +1 in there since*/
/*  we don't know where within the 'tick' this starts.                        */
/* NB: this is a blocking function!                                           */
/******************************************************************************/
#ifdef DELAY_USE_CORE_TIMER


void DelayUs(UINT32 delay_us)
{
    UINT32   DelayStartTime;
    DelayStartTime = ReadCoreTimer();
    while((ReadCoreTimer() - DelayStartTime) < (delay_us * CORE_TIMER_MICROSECONDS));
}

void DelayMs(UINT32 delay_ms)
{
    UINT32   DelayStartTime;
    DelayStartTime = ReadCoreTimer();
    while((ReadCoreTimer() - DelayStartTime) < (delay_ms * CORE_TIMER_MILLISECONDS));
}

#else

void DelayMS(int ms)
{
    UINT64 when;
    when=TickGet()+ms+1;
    while(TickGet()<when);
}

#endif