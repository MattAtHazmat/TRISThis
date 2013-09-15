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
#include <LED.h>
#include <commsToRPi.h>
#include <int.h>
#include <TRISThis.h>

TRISTHIS_DATA_TYPE TRISThisData;

/******************************************************************************/

BOOL TRISThisConfigure(void)
{
    int index;
    index=sizeof(TRISThisData);
    for(index=0;index<sizeof(TRISThisData);index++)
    {
        TRISThisData.data[index]=0;
    }
    TRISThisData.status.configured=FALSE;
    if(TRISThisDigitalConfigure())
    {
        TRISThisData.status.configured=TRUE;
    }
    return TRISThisData.status.configured;
}

/******************************************************************************/

BOOL TRISThisDigitalConfigure(void)
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
    TRISThisSetLEDAutoMode(TRUE);
    TRISThisReadDigitalInputs();
    TRISThisReadDigitalLatches();
    TRISThisReadDigitalDirection();
    return TRUE;
}

/******************************************************************************/

void TRISThisReadDigitalInputs(void)
{
    TRISThisData.digital[0].port.Val=(0xff&(PORTD>>1));
    TRISThisData.digital[1].port.Val=(0xff&(PORTE));
}

/******************************************************************************/

void TRISThisReadDigitalLatches(void)
{
    TRISThisData.digital[0].latch.Val=(0xff&(LATD>>1));
    TRISThisData.digital[1].latch.Val=(0xff&(LATE));
}

/******************************************************************************/

void TRISThisReadDigitalDirection(void)
{
    TRISThisData.digital[0].direction.Val=(0xff&(TRISD>>1));
    TRISThisData.digital[1].direction.Val=(0xff&(TRISE));
}

/******************************************************************************/

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
                UINT32_VAL tempToSet;
                tempToSet.byte.LB=toSet;
                LATD=tempToSet.Val<<1;
                returnValue=TRUE;
                break;
            }
            case 1:
            {
                LATE=toSet;
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

/******************************************************************************/

BOOL TRISThisSetDigitalDirection(UINT8 channel, UINT8 toSet)
{
    BOOL returnValue=FALSE;
    if(channel<TRISTHIS_NUMBER_DIGITAL_PORTS)
    {
        TRISThisData.digital[channel].direction.Val=toSet;
        switch(channel)
        {
            case 0:
            {
                UINT32_VAL tempToSet;
                tempToSet.byte.LB=toSet;
                TRISD=tempToSet.Val<<1;
                returnValue=TRUE;
                break;
            }
            case 1:
            {
                TRISE=toSet;
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

/******************************************************************************/

void DoTRISThis(void)
{
    if(SPIDataReady())
    {
        /* called a lot- save churn on the stack?                             */
        static UINT32_VAL tempData;
        /* check the data we read                                             */
        SPIDataGet(INDEX_STATUS_MB,&tempData.byte.MB);
        SPIDataGet(INDEX_STATUS_UB,&tempData.byte.UB);
        SPIDataGet(INDEX_STATUS_HB,&tempData.byte.HB);
        SPIDataGet(INDEX_STATUS_LB,&tempData.byte.LB);

        if(tempData.Val!=TRISThisReadStatus())
        {
            TRISThisSetStatus(tempData.Val);
            LEDAutoMode(TRISThisData.status.autoLEDmode);
        }
        SPIDataGet(INDEX_LED,&tempData.byte.LB);
        if(tempData.byte.LB!=ReadLEDs())
        {
            SetLEDs(tempData.byte.LB);
        }
        SPIDataGet(INDEX_DIGITAL_DIRECTION_0,&tempData.byte.LB);
        if(tempData.byte.LB!=(0xff&(TRISD>>1)))
        {
            TRISThisSetDigitalDirection(0,tempData.byte.LB);
        }
        SPIDataGet(INDEX_DIGITAL_DIRECTION_1,&tempData.byte.LB);
        if(tempData.byte.LB!=(0xff&(TRISE)))
        {
            TRISThisSetDigitalDirection(0,tempData.byte.LB);
        }
        SPIDataGet(INDEX_DIGITAL_LATCH_0,&tempData.byte.LB);
        if(tempData.byte.LB!=(0xff&(LATD>>1)))
        {
            TRISThisSetDigitalLatches(0,tempData.byte.LB);
        }
        SPIDataGet(INDEX_DIGITAL_LATCH_1,&tempData.byte.LB);
        if(tempData.byte.LB!=(0xff&(LATE)))
        {
            TRISThisSetDigitalLatches(1,tempData.byte.LB);
        }        
    }
}

/******************************************************************************/

UINT32 TRISThisReadStatus(void)
{
    return TRISThisData.status.w.Val;
}

/******************************************************************************/

UINT32 TRISThisSetStatus(UINT32 toSet)
{
    TRISThisData.status.w.Val=(toSet&!STATUS_READ_ONLY_MASK)|
            (STATUS_READ_ONLY_MASK & TRISThisData.status.w.Val);
    LEDAutoMode(TRISThisData.status.autoLEDmode);
    return TRISThisData.status.w.Val;
}

/******************************************************************************/

BOOL TRISThisReadLEDMode(void)
{
    return TRISThisData.status.autoLEDmode;
}

/******************************************************************************/

void TRISThisSetLEDAutoMode(BOOL autoLED)
{
    TRISThisData.status.autoLEDmode=LEDAutoMode(autoLED);
}

/******************************************************************************/
