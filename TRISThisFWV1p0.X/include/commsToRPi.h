/* 
 * File:   commsToRPi.h
 * Author: mjb
 *
 * Created on January 30, 2013, 8:37 PM
 */

#ifndef _COMMSTORPI_H_
#define	_COMMSTORPI_H_

#if (RPI_SPI_CHANNEL==1)

    #define SPI_RX_INTERRUPT_ENABLE         IEC0bits.SPI1RXIE
    #define SPI_RX_INTERRUPT_FLAG           IFS0bits.SPI1RXIF

    #define SPI_TX_INTERRUPT_ENABLE         IEC0bits.SPI1TXIE
    #define SPI_TX_INTERRUPT_FLAG           IFS0bits.SPI1TXIF

    #define SPI_RX_INTERRUPT_ERROR_ENABLE   IEC0bits.SPI1EIE
    #define SPI_RX_INTERRUPT_ERROR_FLAG     IFS0bits.SPI1EIF

    #define RPI_SPI_INTERRUPT               _SPI_1_VECTOR
    #define RPI_SPI_BUF                     SPI1BUF
    #define RPI_SPI_RX_BUF_FULL                SPI1STATbits.SPIRBF

#elif (RPI_SPI_CHANNEL==2)

    #define SPI_RX_INTERRUPT_ENABLE         IEC1bits.SPI2RXIE
    #define SPI_RX_INTERRUPT_FLAG           IFS1bits.SPI2RXIF

    #define SPI_TX_INTERRUPT_ENABLE         IEC1bits.SPI2TXIE
    #define SPI_TX_INTERRUPT_FLAG           IFS1bits.SPI2TXIF

    #define SPI_RX_INTERRUPT_ERROR_ENABLE   IEC1bits.SPI2EIE
    #define SPI_RX_INTERRUPT_ERROR_FLAG     IFS1bits.SPI2EIF

    #define RPI_SPI_INTERRUPT               _SPI_2_VECTOR
    #define RPI_SPI_BUF                     SPI2BUF
    #define RPI_SPI_RX_BUF_FULL                SPI2STATbits.SPIRBF
#else
    #error "RPI_SPI_CHANNEL not defined"
#endif
typedef struct
{
    UINT32_VAL  address;
    UINT8       command;
    UINT8       RXCount;
} SPI_TYPE;

/* commands */

#define SPI_READ    (0b00000011)
#define SPI_WRITE   (0b11111111)//(0b00000010)

#define SPI_COMMAND     (0)
#define SPI_ADDRESS_MSB (1)
#define SPI_ADDRESS_2SB (2)
#define SPI_ADDRESS_LSB (3)

/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

BOOL ConfigSPIComms(void);


#else

    #warning "Redundant include of commsToRPi.h"

#endif	/* _COMMSTORPI_H_ */

