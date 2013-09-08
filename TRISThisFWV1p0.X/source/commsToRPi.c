/******************************************************************************/
/*                                                                            */
/* File:   commsToRPi.c                                                       */
/* Author: Matt Bennett                                                       */
/*                                                                            */
/* Created on January 30, 2013                                                */
/*                                                                            */
/******************************************************************************/

#include <common.h>
#include <commsToRPi.h>
#include <peripheral/spi.h>
#include <peripheral/int.h>

SPI_TYPE SPI;
UINT32 SPIIntCounter=0;
UINT32 SPIIntRXCounter=0;

BOOL ConfigSPIComms(void)
{
    SpiChnClose(RPI_SPI_CHANNEL);
    /* do I need to configure this? */
    INTEnable(INT_SOURCE_SPI_RX(RPI_SPI_CHANNEL),INT_DISABLED);
    INTEnable(INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL),INT_DISABLED);
    INTEnable(INT_SOURCE_SPI_ERROR(RPI_SPI_CHANNEL),INT_DISABLED);
    INTEnable(INT_SOURCE_SPI(RPI_SPI_CHANNEL),INT_DISABLED);
    RPI_SPI_BUF=0x00;
    SPI_DATA_IN_DIRECTION = TRIS_IN;
    SPI_DATA_OUT_DIRECTION = TRIS_OUT;
    SPI_CLOCK_IN_DIRECTION = TRIS_IN;
    SPI_SELECT_IN_DIRECTION = TRIS_IN;

    SPI.RXCount=0;
    SPI.address.Val=0;
    SPI.command=0;
    SpiChnOpen(RPI_SPI_CHANNEL,
            SPI_OPEN_SLVEN|/*SPI_OPEN_CKP_HIGH|*/SPI_OPEN_MODE8|SPI_OPEN_SSEN,
            0);
    RPI_SPI_BUF=0xFF;
    INTSetVectorPriority(INT_VECTOR_SPI(RPI_SPI_CHANNEL), INT_PRIORITY_LEVEL_3);
    INTSetVectorSubPriority(INT_VECTOR_SPI(RPI_SPI_CHANNEL),
            INT_SUB_PRIORITY_LEVEL_1);

    INTClearFlag(INT_SOURCE_SPI_RX(RPI_SPI_CHANNEL));
    INTEnable(INT_SOURCE_SPI_RX(RPI_SPI_CHANNEL),INT_ENABLED);
    
    INTClearFlag(INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL));
    INTEnable(INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL),INT_ENABLED);

    INTClearFlag(INT_SOURCE_SPI_ERROR(RPI_SPI_CHANNEL));
    INTEnable(INT_SOURCE_SPI_ERROR(RPI_SPI_CHANNEL),INT_ENABLED);

    INTClearFlag(INT_SOURCE_SPI(RPI_SPI_CHANNEL));
    INTEnable(INT_SOURCE_SPI(RPI_SPI_CHANNEL),INT_ENABLED);
    /* configure change notice, as I can't figure out any other way to        */
    /* trigger the beginning of the slave select with just the SPI peripheral */
    /* buuut the change notice pins are not on the SS pins, so a white wire is*/
    /* needed /
    /* tie chip enable CE0 to pin20/RE5 CE1 */
    SPI_SELECT_CN_DIRECTION=TRIS_IN;
    CNCONbits.w=0;
    CNCONbits.ON=TRUE;
    CNENbits.w=0;
    CNENbits.CNEN7=TRUE;
    SPI.status.w=0;
    INTClearFlag(INT_CN);
    INTSetVectorPriority(INT_CHANGE_NOTICE_VECTOR, INT_PRIORITY_LEVEL_2);
    INTSetVectorSubPriority(INT_CHANGE_NOTICE_VECTOR, INT_SUB_PRIORITY_LEVEL_1);
    INTEnable(INT_CN,INT_ENABLED);
    return TRUE;
}

void __ISR(_CHANGE_NOTICE_VECTOR , RPI_COMMS_CE_PRIORITY) RPiSPICNInterrutpt(void)
{
    IFS1CLR=_IFS1_CNIF_MASK;
    if((SPI.status.CEStatus==FALSE)&&(SPI_SELECT_CN_IN==FALSE))
    {
        RPI_SPI_BUF=0x55;
        if(SPI.status.RXDataReady)
        {
            /* we missed some data */
            SPI.status.RXDataReady=FALSE;
            SPI.status.RXOverrun=TRUE;
        }
        SPI.RXState=STATE_SPI_RX_COMMAND;
        SPI.status.CEStatus=TRUE;
        SPI.RXCount=0;
    }
    else if((SPI.status.CEStatus==TRUE)&&(SPI_SELECT_CN_IN==TRUE))
    {
        SPI.RXState=STATE_RX_SPI_COMPLETE;
        SPI.status.RXDataReady=TRUE;
        SPI.status.CEStatus=FALSE;
    }
}

inline BOOL RPiSelectStatus(void)
{
    BOOL returnValue;
    unsigned int intEnabled;
    intEnabled=INTGetEnable(INT_CN);
    INTEnable(INT_CN,INT_DISABLED);
    returnValue=SPI.status.CEStatus;
    if(intEnabled)
    {
        INTEnable(INT_CN,INT_ENABLED);
    }
    return returnValue;
}

void __ISR(RPI_SPI_INTERRUPT , RPI_COMMS_INT_PRIORITY) RPiSPIInterrutpt(void)
{
    static UINT8 SPITemp;
    SPIIntCounter++;
    if(SPI_RX_INTERRUPT_ENABLE&&SPI_RX_INTERRUPT_FLAG)
    {
        
        SPI_RX_INTERRUPT_FLAG_CLEAR;
        if(RPI_SPI_RX_BUF_FULL)
        {
            SPIIntRXCounter++;
            /* data in the buffer, read it */
            SPITemp=RPI_SPI_BUF;
            switch(SPI.RXState)
            {
                case STATE_SPI_RX_COMMAND:
                {
                    SPI.command=SPITemp;
                    SPI.RXState=STATE_SPI_RX_ADDRESS_MSB;
                    break;
                }
                case STATE_SPI_RX_ADDRESS_MSB:
                {
                    SPI.address.Val=0;
                    SPI.RXState=STATE_SPI_RX_ADDRESS_2SB;
                    SPI.address.byte.UB=SPITemp;
                    break;
                }
                case STATE_SPI_RX_ADDRESS_2SB:
                {
                    SPI.RXState=STATE_SPI_RX_ADDRESS_LSB;
                    SPI.address.byte.HB=SPITemp;
                    break;
                }
                case STATE_SPI_RX_ADDRESS_LSB:
                {
                    SPI.RXState=STATE_SPI_RX_DATA;
                    SPI.address.byte.LB=SPITemp;
                    break;
                }
                case STATE_SPI_RX_DATA:
                {
                    if(!SPI.status.RXOverrunError)
                    {
                        if(SPI.command==0x00)//SPI_WRITE)
                        {
                            SPI.RXData[SPI.RXCount++]=SPITemp;
                            if(SPI.RXCount==0)
                            {
                                /* error-- went too long*/
                                SPI.status.RXOverrunError=TRUE;
                            }
                        }
                    }
                    break;
                }
                default:
                {
                    SPI.status.RXMysteryState=TRUE;
                    break;
                }
            }
        }        
        //SPI_RX_INTERRUPT_FLAG_CLEAR;
    }
    if(SPI_TX_INTERRUPT_ENABLE&&SPI_TX_INTERRUPT_FLAG)
    {
        SPI_TX_INTERRUPT_FLAG_CLEAR;
        RPI_SPI_BUF=SPI.RXCount;
    }
    if(SPI_INTERRUPT_ERROR_ENABLE&&SPI_INTERRUPT_ERROR_FLAG)
    {
        SPI_INTERRUPT_ERROR_FLAG_CLEAR;
        RPI_SPI_RX_OVERFLOW_CLEAR;
        SPI.status.RXOverflow=TRUE;
    }
}
