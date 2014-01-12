/******************************************************************************/
/* File:   firmwareConfiguration.h                                            */
/* Author: Matt Bennett                                                       */
/*                                                                            */
/* Created on December 16, 2012, 4:39 PM                                      */
/******************************************************************************/

#ifndef _FIRMWARE_CONFIGURATION_H_
#define	_FIRMWARE_CONFIGURATION_H_

#define DELAY_USE_CORE_TIMER

/* lower layer protocols */

//#define USE_I2C
#define USE_SPI

/* have to use certain protocols to talk, so if those protocols are not       */
/* defined, don't even bother                                                 */

#ifdef USE_SPI
    #define TALK_TO_RASPBERRY_PI
#endif /* #ifdef USE_SPI */

#ifdef USE_I2C
    #define USE_PAC1710
    #define USE_DIGIPOT
#endif /* #ifdef USE_I2C */

#ifdef USE_PAC1710
    #define HISTORY_SIZE            (100)
    #define CURRENT_HISTORY_SIZE    HISTORY_SIZE
    #define VOLTAGE_HISTORY_SIZE    HISTORY_SIZE
#endif /* #ifdef USE_PAC1710 */

/******************************************************************************/
/* LED Activity Definitions                                                   */
/******************************************************************************/

#define LED_CASCADE_DELAY   100*TICKS_PER_MS

/******************************************************************************/
/* I2C Definitions                                                            */
/******************************************************************************/

#ifdef USE_I2C
    /* I2C definitions */
    #define I2C_PORT                (2-1)   //(count from zero) I2C2
    #define I2CBUS_WORD_LENGTH      (10)
    #define I2CBUS_DATA_LENGTH      (10)
    #define Fsck                    (100000u)
    #define MI2C_INT_PRIORITY       INT_PRIORITY_LEVEL_6
    #define MI2C_INT_SUB_PRIORITY   INT_SUB_PRIORITY_LEVEL_1
    #define MI2C_INT_PRIORITY_ISR   IPL6SOFT
    #define I2C_STATUS              I2C2STAT
    #define I2C_USE_TIMEOUT
    #ifdef I2C_USE_TIMEOUT
        #define I2C_TIMEOUT_TIMER   (5-1)   //(count from zero)
        #define I2C_TIMEOUT_MS      (100)
        #define I2C_TIMEOUT_TIMER_INT_PRIORITY      INT_PRIORITY_LEVEL_4
        #define I2C_TIMEOUT_TIMER_INT_SUB_PRIORITY  INT_SUB_PRIORITY_LEVEL_1
        #define TIMEOUT_INT_PRIORITY_ISR IPL4SOFT
    #endif /* #ifdef I2C_USE_TIMEOUT */
#endif /* #ifdef USE_I2C */

/******************************************************************************/
/* SPI Definitions                                                            */
/******************************************************************************/

#ifdef USE_SPI
    #define RPI_SPI_CHANNEL         (1)
    #define RPI_COMMS_INT_PRIORITY  IPL3SOFT
    #define RPI_COMMS_CE_PRIORITY   IPL4SOFT
    #define SPI_RX_BUFFER_SIZE      0xFF
    //#define SPI_TX_BUFFER_SIZE    0x0F
#endif

/******************************************************************************/
/* tick definitions                                                           */
/******************************************************************************/

#define TICK_TIMER              (4-1) //(count from zero) 4
#define TICK_INT_PRIORITY       INT_PRIORITY_LEVEL_6 //T4_INT_PRIOR_6
#define TICK_INT_SUB_PRIORITY   INT_SUB_PRIORITY_LEVEL_2
#define TICK_INT_PRIORITY_ISR   IPL6SOFT

/******************************************************************************/
/* PAC1710 definitions                                                        */
/* only included if appropriate transport layer is also included              */
/******************************************************************************/

#ifdef USE_PAC1710
/* PAC1710 */
    //#define MONITOR_1_ADDRESS     (0b10011000) /* 0x98 */
    #define PAC1710_ADDRESS         (0b00110000) /* 0x30 */

    #define ALERT_INT_PRIORITY      INT_PRIORITY_LEVEL_4
    #define ALERT_INT_PRIORITY_ISR  ipl4
#endif

/******************************************************************************/
/* digipot definitions                                                        */
/* only included if appropriate transport layer is also included              */
/******************************************************************************/

#ifdef USE_DIGIPOT
    #define DIGIPOT_ADDRESS         (0b01011110) /* 0x58 */
#endif /* #ifdef USE_DIGIPOT */

#else

    #warning "Redundant include of firmwareConfiguration.h"

#endif	/* _FIRMWARE_CONFIGURATION_H */

