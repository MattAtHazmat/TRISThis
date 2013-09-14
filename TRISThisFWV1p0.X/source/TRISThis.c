/******************************************************************************/
/* File:   TRISThis.c                                                         */
/* Author: matt                                                               */
/*                                                                            */
/* Created on September 14, 2013, 4:19 PM                                     */
/******************************************************************************/

// <editor-fold defaultstate="collapsed" desc="SLA">
/******************************************************************************/
/* Software License Agreement                                                 */
/*                                                                            */
/*                                                                            */
/******************************************************************************/// </editor-fold>


#include <common.h>
#include <commsToRPi.h>
#include <int.h>
#include <TRISThis.h>

TRISTHIS_DATA_TYPE TRISThisData;

void TRISThisDigitalConfigure(void)
{
    IO_OUT00=FALSE;
    IO_OUT01=FALSE;
    IO_OUT02=FALSE;
    IO_OUT03=FALSE;
    IO_OUT04=FALSE;
    IO_OUT05=FALSE;
    IO_OUT06=FALSE;
    IO_OUT07=FALSE;
    IO_OUT08=FALSE;
    IO_OUT09=FALSE;
    IO_OUT10=FALSE;
    IO_OUT11=FALSE;
    IO_OUT12=FALSE;
    IO_OUT13=FALSE;
    IO_OUT14=FALSE;
    IO_OUT15=FALSE;
    IO_DIRECTION00=TRIS_IN;
    IO_DIRECTION01=TRIS_IN;
    IO_DIRECTION02=TRIS_IN;
    IO_DIRECTION03=TRIS_IN;
    IO_DIRECTION04=TRIS_IN;
    IO_DIRECTION05=TRIS_IN;
    IO_DIRECTION06=TRIS_IN;
    IO_DIRECTION07=TRIS_IN;
    IO_DIRECTION08=TRIS_IN;
    IO_DIRECTION09=TRIS_IN;
    IO_DIRECTION10=TRIS_IN;
    IO_DIRECTION11=TRIS_IN;
    IO_DIRECTION12=TRIS_IN;
    IO_DIRECTION13=TRIS_IN;
    IO_DIRECTION14=TRIS_IN;
    IO_DIRECTION15=TRIS_IN;
    TRISThisReadDigitalInputs();
    TRISThisReadDigitalLatches();
    TRISThisReadDigitalDirection();
}

void TRISThisReadDigitalInputs(void)
{
    TRISThisData.digital[0].port.Val=(0xff&(PORTD>>1));
    TRISThisData.digital[1].port.Val=(0xff&(PORTE));
}

void TRISThisReadDigitalLatches(void)
{
    TRISThisData.digital[0].latch.Val=(0xff&(LATD>>1));
    TRISThisData.digital[1].latch.Val=(0xff&(LATE));
}

void TRISThisReadDigitalDirection(void)
{
    TRISThisData.digital[0].direction.Val=(0xff&(TRISD>>1));
    TRISThisData.digital[1].direction.Val=(0xff&(TRISE));
}

BOOL TRISThisSetDigitalLatches(UINT8 channel, UINT8 toSet)
{
    BOOL returnValue=FALSE;
    if(channel<TRISTHIS_NUMBER_DIGITAL_PORTS)
    {
        TRISThisData.digital[channel].latch.Val=toSet;
        switch(channel)
        {
            case 0:
            {
                
                returnValue=TRUE;
                break;
            }
            case 1:
            {
                returnValue=TRUE;
                break;
            }
            default:
            {
                break;
            }
        }
        
    }
    return returnValue;
}

void DoTRISThis(void)
{
    static unsigned int statusTemp;
    if(SPI.status.RXDataReady)
    {
        statusTemp = INTDisableInterrupts();

        SPI.status.RXDataReady=FALSE;
        INTRestoreInterrupts(statusTemp);
    }
}
