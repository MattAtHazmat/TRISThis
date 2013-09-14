/******************************************************************************/
/* File:   firmwareConfiguration.h                                            */
/* Author: Matt Bennett                                                       */
/*                                                                            */
/* Created on December 16, 2012, 4:39 PM                                      */
/******************************************************************************/

#ifndef _FIRMWARE_CONFIGURATION_H_
#define	_FIRMWARE_CONFIGURATION_H_


//#define GetInstructionClock()   (GetSystemClock())

#define DELAY_USE_CORE_TIMER

/* LED Activity definitions */

#define LED_CASCADE_DELAY   100*TICKS_PER_MS

/* I2C definitions */
#define I2CBUS_WORD_LENGTH      (10)
#define I2CBUS_DATA_LENGTH      (10)
#define Fsck                    (100000u)
#define MI2C_INTERRUPT          INT_I2C2M
#define MI2C_INT_PRIORITY       I2C_INT_PRI_6
#define MI2C_INT_PRIORITY_ISR   IPL6SOFT //ipl6
#define I2C_USE_TIMEOUT
#ifdef I2C_USE_TIMEOUT
    #define I2C_TIMEOUT_MS      (100)
    #define TIMEOUT_INT_PRIORITY 4
    #define TIMEOUT_INT_PRIORITY_ISR IPL4SOFT
#endif
/* SPI Definitions */

#define RPI_SPI_CHANNEL         (1)
#define RPI_COMMS_INT_PRIORITY  IPL3SOFT
#define RPI_COMMS_CE_PRIORITY   IPL4SOFT

/* tick */
#define TICK_INT_PRIORITY               T4_INT_PRIOR_6
#define TICK_INT_PRIORITY_ISR           IPL6SOFT

/* PAC1710 */
//#define MONITOR_1_ADDRESS   (0b10011000) /* 0x98 */
#define PAC1710_ADDRESS  (0b00110000) /* 0x30 */

#define ALERT_INT_PRIORITY          INT_PRIORITY_LEVEL_4
#define ALERT_INT_PRIORITY_ISR      ipl4

/* digipot */

#define DIGIPOT_ADDRESS                 (0b01011110) /* 0x58 */

#else
    #warning "Redundant include of firmwareConfiguration.h"

#endif	/* _FIRMWARE_CONFIGURATION_H */

