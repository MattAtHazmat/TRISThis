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

//    SPI_DATA_OUT_DIRECTION = TRIS_IN;
//    SPI_SELECT_IN_DIRECTION = TRIS_OUT;
//    while(TRUE)
//    {
//        SPI_SELECT_IN_OUT^=1;
//    }

    //    while(SPI_SELECT_IN)
//    {
//        Nop();
//    }
//    while(!SPI_SELECT_IN)
//    {
//        Nop();
//    }
//    while(SPI_SELECT_IN)
//    {
//        Nop();
//    }
    SPI.RXCount=0;
    SPI.address.Val=0;
    SPI.command=0;
    SpiChnOpen(RPI_SPI_CHANNEL,
               SPI_OPEN_SLVEN|SPI_OPEN_CKP_HIGH|SPI_OPEN_MODE8|SPI_OPEN_FRMEN|SPI_OPEN_FRM_CNT1|SPI_OPEN_SSEN,
               0);
    /* enable the interrupts */
    //IFS0=0;
    //IFS1=0;
    //IFS2=0;
    /* so interrupt doesn't immediately happen once the */
    RPI_SPI_BUF=0x55;
    INTSetVectorPriority(INT_VECTOR_SPI(RPI_SPI_CHANNEL), INT_PRIORITY_LEVEL_3);
    INTSetVectorSubPriority(INT_VECTOR_SPI(RPI_SPI_CHANNEL),INT_SUB_PRIORITY_LEVEL_1);

    INTClearFlag(INT_SOURCE_SPI_RX(RPI_SPI_CHANNEL));
    INTEnable(INT_SOURCE_SPI_RX(RPI_SPI_CHANNEL),INT_ENABLED);
    
    INTClearFlag(INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL));
    INTEnable(INT_SOURCE_SPI_TX(RPI_SPI_CHANNEL),INT_DISABLED);

    INTClearFlag(INT_SOURCE_SPI_ERROR(RPI_SPI_CHANNEL));
    INTEnable(INT_SOURCE_SPI_ERROR(RPI_SPI_CHANNEL),INT_ENABLED);

    INTClearFlag(INT_SOURCE_SPI(RPI_SPI_CHANNEL));
    INTEnable(INT_SOURCE_SPI(RPI_SPI_CHANNEL),INT_ENABLED);
    return TRUE;
}
UINT8 inputData[255];
UINT8 inputDataIndex;
//UINT8 = 0;

void __ISR(RPI_SPI_INTERRUPT , RPI_COMMS_INT_PRIORITY) RPiSPIInterrutpt(void)
{
    static UINT8 txVal=0;
    UINT8 temp;
    if(SPI_RX_INTERRUPT_ENABLE&&SPI_RX_INTERRUPT_FLAG)
    {   
        if(RPI_SPI_RX_BUF_FULL)
        {
            /* data in the buffer, read it */
            temp=RPI_SPI_BUF;
            switch(SPI.RXCount)
            {
                case SPI_COMMAND:
                {
                    SPI.command=temp;
                    break;
                }
                case SPI_ADDRESS_MSB:
                {
                    SPI.address.Val=0;
                    SPI.address.byte.UB=temp;
                    break;
                }
                case SPI_ADDRESS_2SB:
                {
                    SPI.address.byte.HB=temp;
                    break;
                }
                case SPI_ADDRESS_LSB:
                {
                    SPI.address.byte.LB=temp;
                    break;
                }
                default:
                {
                    if(SPI.command==SPI_WRITE)
                    {
                        inputData[inputDataIndex++]=temp;
                    }
                    break;
                }
            }
            if(SPI.RXCount==0xFF)
            {
                /* error-- went too long*/
                Nop();
            }
            else
            {
                SPI.RXCount++;
            }
        }
        SPI_RX_INTERRUPT_FLAG=FALSE;
    }
    if(SPI_TX_INTERRUPT_ENABLE&&SPI_TX_INTERRUPT_FLAG)
    {
        RPI_SPI_BUF=txVal++;
        SPI_TX_INTERRUPT_FLAG=FALSE;
    }
    if(SPI_RX_INTERRUPT_ERROR_ENABLE&&SPI_RX_INTERRUPT_ERROR_FLAG)
    {
        SPI_RX_INTERRUPT_ERROR_FLAG=FALSE;
        while(TRUE);
    }
}
