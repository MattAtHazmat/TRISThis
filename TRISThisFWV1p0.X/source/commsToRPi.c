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

BOOL ConfigSPIComms(void)
{
    SpiChnClose(RPI_SPI_CHANNEL);
    /* do I need to configure this? */
    SPI_DATA_IN_DIRECTION = TRIS_IN;
    SPI_DATA_OUT_DIRECTION = TRIS_OUT;
    SPI_CLOCK_IN_DIRECTION = TRIS_IN;
    SPI_SELECT_IN_DIRECTION = TRIS_IN;
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
    SpiChnOpen(RPI_SPI_CHANNEL,
               SPI_OPEN_SLVEN|SPI_OPEN_CKP_HIGH|SPI_OPEN_MODE8|SPI_OPEN_FRMEN|SPI_OPEN_FRM_CNT1|SPI_OPEN_SSEN,
               0);
    /* enable the interrupts */
    //IFS0=0;
    //IFS1=0;
    //IFS2=0;
    /* so interrupt doesn't immediately happen once the */
    SPI2BUF=0x55;
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
UINT8 inputData[4];
//UINT8 = 0;
SPI_TYPE SPI;
void __ISR(RPI_SPI_INTERRUPT , RPI_COMMS_INT_PRIORITY) RPiSPIInterrutpt(void)
{
    UINT8_VAL temp;
    if(SPI_RX_INTERRUPT_ENABLE&&SPI_RX_INTERRUPT_FLAG)
    {
        /* first byte is */
        if(SPI1STATbits.SPIRBF)
        {
            switch(SPI.RXCount)
            {
                case SPI_COMMAND:
                {
                    SPI.command=RPI_SPI_BUF;
                    break;
                }
                case SPI_ADDRESS_MSB:
                {
                    SPI.address.Val=0;
                    SPI.address.byte.UB=RPI_SPI_BUF;
                    break;
                }
                case SPI_ADDRESS_2SB:
                {
                    SPI.address.byte.HB=RPI_SPI_BUF;
                    break;
                }
                case SPI_ADDRESS_LSB:
                {
                    SPI.address.byte.HB=RPI_SPI_BUF;
                    break;
                }
                default:
                {
                    if(SPI.command==SPI_WRITE)
                    {
                        
                    }
                }
            }
            if(SPI.RXCount==0xFF)
            {
                /* error-- went too long*/
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
        SPI_TX_INTERRUPT_FLAG=FALSE;
    }
    if(SPI_RX_INTERRUPT_ERROR_ENABLE&&SPI_RX_INTERRUPT_ERROR_FLAG)
    {
        SPI_RX_INTERRUPT_ERROR_FLAG=FALSE;
        while(TRUE);
    }
}
