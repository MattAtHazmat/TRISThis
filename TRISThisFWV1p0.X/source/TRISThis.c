/******************************************************************************/
/* File:   TRISThis.c                                                         */
/* Author: matt                                                               */
/*                                                                            */
/* Created on September 14, 2013, 4:19 PM                                     */
/******************************************************************************/

/******************************************************************************/
/* Software License Agreement                                                 */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/******************************************************************************/


#include <common.h>
#include <LED.h>
#include <PAC1710.h>
#include <TRISThis.h>
/* usually I try to keep the .h file include that matches with the .c file at */
/* the very end of the include file list, but the SPI type needs the size of  */
/* TRISTHIS_DATA_TYPE                                                         */
#include <commsToRPi.h>
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
    UINT32 index;
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
    /* clear out the data array */
    for(index=0;index<TRISTHIS_DATA_SIZE;index++)
    {
        TRISThisData.data[index]=0;
    }
    /* read in the current state */
    TRISThisData.digital.port.Val=TRISThisReadDigitalInputs();
    TRISThisData.digital.latch.Val=TRISThisReadDigitalLatches();
    TRISThisData.digital.direction.Val=TRISThisReadDigitalDirection();
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

BOOL DoTRISThis(void)
{
    static UINT32_VAL tempHolding;
    BOOL returnValue=TRUE;
    TRISThisData.digital.port.Val=TRISThisReadDigitalInputs();
    TRISThisData.digital.latch.Val=TRISThisReadDigitalLatches();
    TRISThisData.digital.direction.Val=TRISThisReadDigitalDirection();
    TRISThisData.status.autoLEDmode=GetLEDAutoMode();
    TRISThisData.status.V5p0Good=P5V_POWER_GOOD;
    #ifdef USE_SPI
    if(SPIDataReady())
    {
        /* if there is data available from the SPI, figure out what it is, and*/
        /* put it */
        INTEnable( INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL),INT_DISABLED);
        /* called a lot- save churn on the stack?                             */
        static UINT32_VAL tempData;
        /* check the data we read                                             */
        SPIByteGet(INDEX_STATUS_MB,&tempData.byte.MB);
        SPIByteGet(INDEX_STATUS_UB,&tempData.byte.UB);
        SPIByteGet(INDEX_STATUS_HB,&tempData.byte.HB);
        SPIByteGet(INDEX_STATUS_LB,&tempData.byte.LB);
        /* tempdata is the status */
        tempData.Val|=STATUS_READ_ONLY_MASK;
        if(tempData.Val!=(TRISThisReadStatus()|STATUS_READ_ONLY_MASK))
        {
            TRISThisSetStatus(tempData.Val);            
        }
        SPIByteGet(INDEX_LED,&tempData.byte.LB);
        if(tempData.byte.LB!=ReadLEDs())
        {
            SetLEDs(tempData.byte.LB);
        }
        tempData.Val=0;
        SPIByteGet(INDEX_DIGITAL_DIRECTION_LB,&tempData.byte.LB);
        SPIByteGet(INDEX_DIGITAL_DIRECTION_HB,&tempData.byte.HB);
        if(tempData.Val!=TRISThisReadDigitalDirection())
        {
            TRISThisSetDigitalDirection(tempData);
        }
        tempData.Val=0;
        SPIByteGet(INDEX_DIGITAL_LATCH_LB,&tempData.byte.LB);
        SPIByteGet(INDEX_DIGITAL_LATCH_HB,&tempData.byte.HB);
        if(tempData.Val!=TRISThisReadDigitalLatches())
        {
            TRISThisSetDigitalLatches(tempData);
        }
        INTEnable( INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL),INT_ENABLED);
    }
    if(SPIFUBAR())
    {
        /* try and reset the SPI */
        returnValue=ConfigSPIComms();
    }
    #endif /* USE_SPI */
    /* update the data that the SPI might read */
    #ifdef USE_PAC1710
    if(PAC1710GetData(PAC1710_DATA_CURRENT,&tempHolding.w[0]))
    {
        TRISThisData.supplyCurrent.w[0]=tempHolding.w[0];
        TRISThisData.status.freshSupplyCurrent=TRUE;
    }
    if(PAC1710GetData(PAC1710_DATA_VOLTAGE,&tempHolding.w[0]))
    {
        TRISThisData.supplyVoltage.w[0]=tempHolding.w[0];
        TRISThisData.status.freshSupplyVoltage=TRUE;
    }
    TRISThisData.status.autoLEDmode=GetLEDAutoMode();
    #endif /* #ifdef USE_PAC1710 */
    return returnValue;
}

/******************************************************************************/

UINT32 TRISThisReadStatus(void)
{
    TRISThisData.status.V5p0Good=P5V_POWER_GOOD;
    return TRISThisData.status.w;
}

/******************************************************************************/

UINT32 TRISThisSetStatus(UINT32 toSet)
{
    TRISThisData.status.w=(toSet & ~STATUS_READ_ONLY_MASK)|
            (STATUS_READ_ONLY_MASK & TRISThisData.status.w);
    LEDAutoMode(TRISThisData.status.autoLEDmode);
    return TRISThisData.status.w;
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
