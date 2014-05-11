/******************************************************************************/
/*                                                                            */
/* File:   commsToRPi.c                                                       */
/* Author: Matt Bennett                                                       */
/*                                                                            */
/* Created on January 30, 2013                                                */
/*                                                                            */
/******************************************************************************/

#include <common.h>
#include <TRISThis.h>
#include <commsToRPi.h>
#include <peripheral/spi.h>
#include <peripheral/int.h>

SPI_TYPE SPI;
extern TRISTHIS_DATA_TYPE TRISThisData;
unsigned int CNTemp;

/******************************************************************************/

BOOL SPIByteGet(UINT8 address, UINT8 *data)
{
    if(address>=sizeof(SPI.RXData))
    {
        return FALSE;
    }
    else
    {
        *data=SPI.RXData[address];
        return TRUE;
    }
}

BOOL SPIWordGet(UINT8 address, UINT32 *data)
{

}
/******************************************************************************/

BOOL SPIDataReady(void)
{
    BOOL returnValue;
    unsigned int statusTemp;
    statusTemp = INTDisableInterrupts();
    returnValue=SPI.status.RXDataReady;
    SPI.status.RXDataReady=FALSE;
    INTRestoreInterrupts(statusTemp);
    return returnValue;
}

/******************************************************************************/

BOOL ConfigSPIComms(void)
{
    SpiChnClose(RPI_SPI_CHANNEL);
    /* do I need to configure this? */
    INTEnable(INT_SOURCE_SPI_RX(RPI_SPI_CHANNEL),INT_DISABLED);
    INTEnable(INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL),INT_DISABLED);
    INTEnable(INT_SOURCE_SPI_ERROR(RPI_SPI_CHANNEL),INT_DISABLED);
    INTEnable(INT_SOURCE_SPI(RPI_SPI_CHANNEL),INT_DISABLED);
    SPI_DATA_IN_DIRECTION = TRIS_IN;
    SPI_DATA_OUT_DIRECTION = TRIS_OUT;
    SPI_CLOCK_IN_DIRECTION = TRIS_IN;
    SPI_SELECT_IN_DIRECTION = TRIS_IN;
    SPI.RXCount=0;
    SPI.TXCount=0;
    SPI.address.Val=0;
    SPI.command=SPI_NO_COMMAND;
    SpiChnOpen(RPI_SPI_CHANNEL,
            SPI_OPEN_SLVEN|SPI_OPEN_CKE_REV|SPI_OPEN_MODE8|SPI_OPEN_SSEN,
            0);
    //TODO: Not acting consistently? RPI needs to send -b 8 -H parameters to spidev
    /* configure interrupts                                                   */
    INTSetVectorPriority(INT_VECTOR_SPI(RPI_SPI_CHANNEL), INT_PRIORITY_LEVEL_3);
    INTSetVectorSubPriority(INT_VECTOR_SPI(RPI_SPI_CHANNEL),
            INT_SUB_PRIORITY_LEVEL_1);
    INTClearFlag(INT_SOURCE_SPI_RX(RPI_SPI_CHANNEL));
    INTEnable(INT_SOURCE_SPI_RX(RPI_SPI_CHANNEL),INT_ENABLED);
    INTClearFlag(INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL));
    INTClearFlag(INT_SOURCE_SPI_ERROR(RPI_SPI_CHANNEL));
    INTClearFlag(INT_SOURCE_SPI(RPI_SPI_CHANNEL));
    //INTEnable(INT_SOURCE_SPI(RPI_SPI_CHANNEL),INT_ENABLED);
    /* configure change notice, as I can't figure out any other way to        */
    /* trigger the beginning of the slave select with just the SPI peripheral */
    /* buuut the change notice pins are not on the SS pins, so a white wire is*/
    /* needed                                                                 */
    /* tie chip enable CE0 to pin20/RE5 CE1 */
    SPI_SELECT_CN_DIRECTION=TRIS_IN;
    CNCONbits.w=0;
    CNCONSET=_CNCON_ON_MASK;
    CNENbits.w=0;
    CNENSET=_CNEN_CNEN7_MASK;
    CNTemp=CE_PORT; /* read for change notice */
    RPI_SPI_RX_OVERFLOW_CLEAR;
    SPI1CONbits.STXISEL=0b01;
    SPI.status.w=0;
    INTClearFlag(INT_CN);
    INTSetVectorPriority(INT_CHANGE_NOTICE_VECTOR, INT_PRIORITY_LEVEL_2);
    INTSetVectorSubPriority(INT_CHANGE_NOTICE_VECTOR, INT_SUB_PRIORITY_LEVEL_1);
    return TRUE;
}

/******************************************************************************/

/* want CN interrupt on de-assertion of the CE signal to indicate the end of  */
/* the SPI transaction */

void __ISR(_CHANGE_NOTICE_VECTOR , RPI_COMMS_CE_PRIORITY) RPiSPICNInterrutpt(void)
{
    INTClearFlag(INT_CN);
    /* read of portb to reload the change notice registers for next time */
    CNTemp=CE_PORT;
    if(CNTemp&CE_MASK)
    {
        /* if CE is set (the SPI transaction is over) */
        /* disable the interrupt */
        INTEnable(INT_CN,INT_DISABLED);
        /* flag that data is ready */
        SPI.status.RXDataReady=TRUE;
        /* prepare for the next cycle */
        SPI.RXState=STATE_SPI_RX_COMMAND;
        /* to make sure that the port returns 0x00 the next time */
        RPI_SPI_BUF=0x00;
    }   
}

/******************************************************************************/

inline BOOL SPIFUBAR(void)
{
    BOOL returnValue;
    unsigned int intEnabled;
    intEnabled=INTDisableInterrupts();
    returnValue=FALSE;
    INTRestoreInterrupts(intEnabled);
    return returnValue;
}

/******************************************************************************/

void __ISR(RPI_SPI_INTERRUPT , RPI_COMMS_INT_PRIORITY) RPiSPIInterrupt(void)
{
    static UINT8 RXTemp;
    /* check for receive interrupt */
    if(INTGetEnable(INT_SOURCE_SPI_RX(RPI_SPI_CHANNEL))&&
       INTGetFlag(INT_SOURCE_SPI_RX(RPI_SPI_CHANNEL)))
    
    {
        INTClearFlag(INT_SOURCE_SPI_RX(RPI_SPI_CHANNEL));
        if(RPI_SPI_RX_BUF_FULL)
        {
            RXTemp=RPI_SPI_BUF;
            /* data in the buffer, read it */
            switch(SPI.RXState)
            {
                case STATE_SPI_RX_COMMAND:
                {
                    /* want to detect when CE is de-asserted */
                    CNTemp=CE_PORT; /* read for change notice */
                    INTClearFlag(INT_CN);
                    INTEnable(INT_CN,INT_ENABLED);
                    if(SPI.status.RXDataReady)
                    {
                        SPI.status.RXOverflow=TRUE;
                    }
                    SPI.status.RXDataReady=FALSE;
                    SPI.command=RXTemp;
                    SPI.TXIndex=0;
                    RPI_SPI_BUF=RXTemp;
                    SPI.RXState=STATE_SPI_RX_ADDRESS_MSB;
                    break;
                }
                case STATE_SPI_RX_ADDRESS_MSB:
                {
                    RPI_SPI_BUF=RXTemp;
                    RXTemp=RPI_SPI_BUF;
                    SPI.TXIndex=0;
                    SPI.RXState=STATE_SPI_RX_ADDRESS_LSB;
                    SPI.address.byte.HB=RXTemp;
                    break;
                }
                case STATE_SPI_RX_ADDRESS_LSB:
                {
                    SPI.TXIndex=0;
                    SPI.address.byte.LB=RXTemp;
                    /* now that we have address, what to do with it? */
                    switch(SPI.command)
                    {
                        case SPI_READ_COMMAND:
                        {
                            /* master is reading data from us, that is, we,   */
                            /* as the slave is transmitting                   */
                            unsigned int index;
                            /* the master is requesting data, make a copy and */
                            /* have it ready                                  */
                            index=0;
                            /* only really can use the low byte of the address*/
                            SPI.TXIndex=SPI.address.byte.LB;
                            /* copy data into outgoing array and bounds check */
                            while((index<sizeof(TRISThisData))&&
                                  (SPI.TXIndex<sizeof(SPI.TXData)))
                            {
                                SPI.TXData[SPI.TXIndex++]=TRISThisData.data[index++];
                            }
                            SPI.TXIndex=0;
                            /* the data to send on next TX interrupt */
                            SPI.TXBuffer=SPI.TXData[SPI.TXIndex];
                            SPI.status.TXEnd=FALSE;
                            SPI.status.TXDataReady=TRUE;
                            INTEnable(INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL),INT_ENABLED);
                            /* don't need to look for change notice any more */
                            INTEnable(INT_CN,INT_DISABLED);
                            SPI.RXState=STATE_SPI_RX_MASTER_READING;
                            break;
                        }
                        case SPI_WRITE_COMMAND:
                        {
                            /* master is writing data (slave is receiving)    */
                            SPI.status.RXOverflow=FALSE;
                            SPI.status.RXOverrun=FALSE;
                            /* the data to send on next TX interrupt */
                            SPI.TXBuffer=NOT_YET_BYTE;
                            SPI.RXState=STATE_SPI_RX_DATA;
                            break;
                        }
                        default:
                        {
                            /* dunno what happened. */
                            break;
                        }
                    }
                    break;
                }
                case STATE_SPI_RX_DATA:
                {
                    /* master is sending data, slave receiving */
                    if(!SPI.status.RXOverrun)
                    {
                        SPI.RXData[SPI.RXCount++]=RXTemp;
                        if(SPI.RXCount==SPI_RX_BUFFER_SIZE)
                        {
                            SPI.RXState=STATE_SPI_RX_COMMAND;
                            SPI.status.RXDataReady=TRUE;
                            INTEnable(INT_CN,INT_DISABLED);
                        }
                    }
                    RPI_SPI_BUF=0x00;
                    break;
                }
                case STATE_SPI_RX_COMPLETE:
                {
                    /* error-- went too long*/
                    SPI.status.RXOverrun=TRUE;
                    break;
                }
                case STATE_SPI_RX_MASTER_READING:
                    /* if the master is reading, nothing to do here */
                case STATE_SPI_RX_SPI_WRITE_COMPLETE:
                {
                    break;
                }
                default:
                {
                    SPI.status.RXMysteryState=TRUE;
                    break;
                }
            }
        }
    }
    /* and then check for transmit interrupt */
    if(INTGetEnable(INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL))&&
       INTGetFlag(INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL)))
    {        
        if(SPI.status.TXEnd)
        {
            RPI_SPI_BUF=OVERRUN_BYTE;
            INTEnable(INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL),INT_DISABLED);
        }
        else
        {
            if(SPI.status.TXDataReady)
            {
                /* send data and point at the next */
                RPI_SPI_BUF=SPI.TXData[SPI.TXIndex++];
                /* bounds check */
                if(SPI.TXIndex<sizeof(SPI.TXData))
                {
                    /* all is good, no bounds violation */
                }
                else
                {
                    /* there can be no more! */
                    INTEnable(INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL),INT_DISABLED);
                    SPI.status.TXEnd=TRUE;
                    SPI.status.TXDataReady=FALSE;
                }
            }
            else
            {
                /* harrumph. shouldn't even be here. disable this interrupt.  */
                RPI_SPI_BUF=NOT_YET_BYTE;
                INTEnable(INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL),INT_DISABLED);
            }
        }
    }
}

/******************************************************************************/
