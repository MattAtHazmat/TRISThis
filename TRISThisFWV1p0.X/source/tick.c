/******************************************************************************/
/*                                                                            */
/* File:   tick.c                                                             */
/* Author: Matt Bennett                                                       */
/*                                                                            */
/* Created on June 13, 2012                                                   */
/*                                                                            */
/******************************************************************************/


#include <common.h>
#include <peripheral/timer.h>
#include <tick.h>

/******************************************************************************/
/* there are 31536000 seconds in a year. With a 64 bit ms counter, it will    */
/* take 584 million years for the counter to roll over.                       */
/******************************************************************************/

TICK_TYPE tick;

/******************************************************************************/
/* timer interrupt, provides an independent clock for real-time timing        */
/* purposes                                                                   */
/******************************************************************************/

void __ISR(_TIMER_4_VECTOR,TICK_INT_PRIORITY_ISR) T4_Interrupt_Handler(void)
{
    mTickClearInterruptFlag();
    tick++;
}

/******************************************************************************/
/* UINT64 TickGet(void)                                                       */
/* interrupt safe accessor function for the tick variable                     */
/******************************************************************************/

TICK_TYPE TickGet(void)
{
    TICK_TYPE returnValue;
    mTickDisableInterrupt();
    returnValue=tick;
    mTickEnableInterrupt();
    return returnValue;
}

/******************************************************************************/
/* void TickInitialize(void)                                                  */
/******************************************************************************/

void TickInitialize(void)
{
    OpenTimer4(
        T4_ON|
        T4_IDLE_CON|
        T4_GATE_OFF|
        TICK_PRESCALER|
        T4_32BIT_MODE_OFF|
        T4_SOURCE_INT,
        TICK_UPDATE_INTERVAL);
    TMR4=0;
    tick=0;
    mTickClearInterruptFlag();
    ConfigIntTimer4(T4_INT_ON | TICK_INT_PRIORITY | T4_INT_SUB_PRIOR_1);
}
