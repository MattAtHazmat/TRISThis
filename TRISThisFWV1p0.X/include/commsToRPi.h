/* 
 * File:   commsToRPi.h
 * Author: mjb
 *
 * Created on January 30, 2013, 8:37 PM
 */

#ifndef _COMMSTORPI_H_
#define	_COMMSTORPI_H_

/******************************************************************************/

#if (RPI_SPI_CHANNEL==1)

    #define SPI_RX_INTERRUPT_ENABLE         IEC0bits.SPI1RXIE
    #define SPI_RX_INTERRUPT_FLAG           IFS0bits.SPI1RXIF
    #define SPI_RX_INTERRUPT_FLAG_CLEAR     IFS0CLR=_IFS0_SPI1RXIF_MASK

    #define SPI_TX_INTERRUPT_ENABLE         IEC0bits.SPI1TXIE
    #define SPI_TX_INTERRUPT_FLAG           IFS0bits.SPI1TXIF
    #define SPI_TX_INTERRUPT_FLAG_CLEAR     IFS0CLR=_IFS0_SPI1TXIF_MASK

    #define SPI_INTERRUPT_ERROR_ENABLE      IEC0bits.SPI1EIE
    #define SPI_INTERRUPT_ERROR_FLAG        IFS0bits.SPI1EIF
    #define SPI_INTERRUPT_ERROR_FLAG_CLEAR  IFS0CLR=_IFS0_SPI1EIF_MASK

    #define RPI_SPI_INTERRUPT               _SPI_1_VECTOR
    #define RPI_SPI_BUF                     SPI1BUF
    #define RPI_SPI_RX_BUF_FULL             SPI1STATbits.SPIRBF

    #define RPI_SPI_RX_OVERFLOW_CLEAR       SPI1STATbits.SPIROV=FALSE;//SPI1STATCLR=_SPI1STAT_SPIROV_MASK

#elif (RPI_SPI_CHANNEL==2)

    #define SPI_RX_INTERRUPT_ENABLE         IEC1bits.SPI2RXIE
    #define SPI_RX_INTERRUPT_FLAG           IFS1bits.SPI2RXIF
    #define SPI_RX_INTERRUPT_FLAG_CLEAR     IFS1CLR=_IFS1_SPI2RXIF_MASK

    #define SPI_TX_INTERRUPT_ENABLE         IEC1bits.SPI2TXIE
    #define SPI_TX_INTERRUPT_FLAG           IFS1bits.SPI2TXIF
    #define SPI_TX_INTERRUPT_FLAG_CLEAR     IFS1CLR=_IFS1_SPI2TXIF_MASK

    #define SPI_INTERRUPT_ERROR_ENABLE      IEC1bits.SPI2EIE
    #define SPI_INTERRUPT_ERROR_FLAG        IFS1bits.SPI2EIF
    #define SPI_INTERRUPT_ERROR_FLAG_CLEAR  IFS1CLR=_IFS1_SPI2EIF

    #define RPI_SPI_INTERRUPT               _SPI_2_VECTOR
    #define RPI_SPI_BUF                     SPI2BUF
    #define RPI_SPI_RX_BUF_FULL             SPI2STATbits.SPIRBF
#else
    #error "RPI_SPI_CHANNEL not defined"
#endif

#define OVERRUN_BYTE    0xFF
#define NOT_YET_BYTE    0x00

/******************************************************************************/
/* local types                                                                */
typedef union
{
    struct
    {
        unsigned RXDataReady:1;
        unsigned CEStatus:1;
        unsigned inProgress:1;
        unsigned RXOverrunError:1;
        unsigned RXOverflow:1;
        unsigned RXOverrun:1;
        unsigned RXMysteryState:1;
        unsigned unknownCommandRX:1;
    };
    UINT32 w;
} SPI_STATUS;

enum SPI_RX_STATE
{
    STATE_SPI_RX_COMMAND=0,
    STATE_SPI_RX_ADDRESS_MSB,
    STATE_SPI_RX_ADDRESS_2SB,
    STATE_SPI_RX_ADDRESS_LSB,
    STATE_SPI_RX_DATA,
    STATE_SPI_RX_READING,
    STATE_SPI_RX_MYSTERY,
    STATE_SPI_RX_COMPLETE,
    STATE_SPI_RX_SPI_WRITE_COMPLETE
};

typedef struct
{
    UINT32_VAL  address;
    UINT8       command;
    UINT8       RXCount;
    UINT8       TXCount;
    SPI_STATUS  status;
    UINT8 RXData[SPI_RX_BUFFER_SIZE];
    UINT8 RXIndex;
    UINT8 TXBuffer;
    UINT8 TXIndex;
    enum SPI_RX_STATE RXState;
} SPI_TYPE;

/******************************************************************************/
/* commands                                                                   */
/******************************************************************************/

#define SPI_READ    (0b00000011)
#define SPI_WRITE   (0b00000010)

/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

BOOL ConfigSPIComms(void);
inline BOOL RPiSelectStatus(void);
BOOL SPIDataReady(void);
BOOL SPIDataGet(UINT8, UINT8*);

#else

    #warning "Redundant include of commsToRPi.h"

#endif	/* _COMMSTORPI_H_ */
