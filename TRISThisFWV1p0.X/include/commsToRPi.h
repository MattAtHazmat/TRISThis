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

    #define SPI_INTERRUPT                   _SPI_1_VECTOR

#elif (RPI_SPI_CHANNEL==2)

    #define SPI_RX_INTERRUPT_ENABLE         IEC1bits.SPI2RXIE
    #define SPI_RX_INTERRUPT_FLAG           IFS1bits.SPI2RXIF

    #define SPI_TX_INTERRUPT_ENABLE         IEC1bits.SPI2TXIE
    #define SPI_TX_INTERRUPT_FLAG           IFS1bits.SPI2TXIF

    #define SPI_RX_INTERRUPT_ERROR_ENABLE   IEC1bits.SPI2EIE
    #define SPI_RX_INTERRUPT_ERROR_FLAG     IFS1bits.SPI2EIF

    #define SPI_INTERRUPT                _SPI_2_VECTOR

#else
    #error "RPI_SPI_CHANNEL not defined"
#endif
/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

BOOL ConfigSPIComms(void);


#else

    #warning "Redundant include of commsToRPi.h"

#endif	/* _COMMSTORPI_H_ */

