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
/******************************************************************************/


#include <common.h>
#include <LED.h>
#include <commsToRPi.h>
#include <int.h>
#include <PAC1710.h>
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
    TRISThisData.digital.port=TRISThisReadDigitalInputs();
    TRISThisData.digital.latch=TRISThisReadDigitalLatches();
    TRISThisData.digital.direction=TRISThisReadDigitalDirection();
    return TRUE;
}

/******************************************************************************/

UINT32 TRISThisReadDigitalInputs(void)
{
    UINT32_VAL readTemp;
    readTemp.Val=0;
    readTemp.byte.LB=(0xff&(PORTD>>1));
    readTemp.byte.HB=(0xff&(PORTE));
    return readTemp.Val;
}

/******************************************************************************/

UINT32 TRISThisReadDigitalLatches(void)
{
    UINT32_VAL readTemp;
    readTemp.Val=0;
    readTemp.byte.LB=(0xff&(LATD>>1));
    readTemp.byte.HB=(0xff&(LATE));
    return readTemp.Val;
}

/******************************************************************************/

UINT32 TRISThisReadDigitalDirection(void)
{
    UINT32_VAL readTemp;
    readTemp.Val=0;
    readTemp.byte.LB=(0xff&(TRISD>>1));
    readTemp.byte.HB=(0xff&(TRISE));
    return readTemp.Val;
}

/******************************************************************************/

BOOL TRISThisSetDigitalLatches(UINT32_VAL toSet)
{
    BOOL returnValue=FALSE;
    LATD=toSet.byte.LB<<1;
    LATE=toSet.byte.HB;
    return returnValue;
}

/******************************************************************************/

BOOL TRISThisSetDigitalDirection(UINT32_VAL toSet)
{
    BOOL returnValue=FALSE;
    TRISD=toSet.byte.LB<<1;
    TRISE=toSet.byte.HB;
    return returnValue;
}

/******************************************************************************/

void DoTRISThis(void)
{
    static UINT32_VAL tempHolding;
    if(SPIDataReady())
    {
        /* if there is data available from the SPI, figure out what it is, and*/
        /* put it */
        INTEnable( INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL),INT_DISABLED);
        /* called a lot- save churn on the stack?                             */
        static UINT32_VAL tempData;
        /* check the data we read                                             */
        SPIDataGet(INDEX_STATUS_MB,&tempData.byte.MB);
        SPIDataGet(INDEX_STATUS_UB,&tempData.byte.UB);
        SPIDataGet(INDEX_STATUS_HB,&tempData.byte.HB);
        SPIDataGet(INDEX_STATUS_LB,&tempData.byte.LB);
        /* tempdata is the status */
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
        INTEnable( INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL),INT_ENABLED);
    }
    /* update the data that the SPI might read */
    if(PAC1710GetData(PAC1710_DATA_CURRENT,&tempHolding.w[0]))
    {
        TRISThisData.current.w[0]=tempHolding.w[0];
        TRISThisData.status.freshCurrent=TRUE;
    }
    if(PAC1710GetData(PAC1710_DATA_VOLTAGE,&tempHolding.w[0]))
    {
        TRISThisData.voltage.w[0]=tempHolding.w[0];
        TRISThisData.status.freshVoltage=TRUE;
    }
    TRISThisData.status.autoLEDmode=GetLEDAutoMode();
    TRISThisReadDigitalInputs();
    TRISThisReadDigitalLatches();
    TRISThisReadDigitalDirection();

}

/******************************************************************************/

UINT32 TRISThisReadStatus(void)
{
    TRISThisData.status.V5p0Good=P5V_POWER_GOOD;
    return TRISThisData.status.w.Val;
}

/******************************************************************************/

UINT32 TRISThisSetStatus(UINT32 toSet)
{
    TRISThisData.status.w.Val=(toSet & ~STATUS_READ_ONLY_MASK)|
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
