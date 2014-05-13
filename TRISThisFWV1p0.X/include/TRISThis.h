/******************************************************************************/
/* File:   TRISThis.h                                                         */
/* Author: matt                                                               */
/*                                                                            */
/* Created on September 14, 2013, 9:54 AM                                     */
/******************************************************************************/

#ifndef _TRISTHIS_H_
#define	_TRISTHIS_H_

#define CONFIGURED_BIT_POSITION         (0)
#define V5P0GOOD_BIT_POSITION           (1)
#define TRISTHIS_NUMBER_DIGITAL_PORTS   (2)
#define TRISTHIS_NUMBER_ANALOG_PORTS    (4)
#define STATUS_READ_ONLY_MASK           ((1<<CONFIGURED_BIT_POSITION)&(1<<V5P0GOOD_BIT_POSITION))

/* TODO: can these be automatically generated? */
typedef enum {
    INDEX_STATUS_UB =0,  /* index = 0 */
    INDEX_STATUS_HB,
    INDEX_STATUS_LB,
    INDEX_LED,
    INDEX_DIGITAL_LATCH_MB,     /* index = 4 */
    INDEX_DIGITAL_LATCH_UB,
    INDEX_DIGITAL_LATCH_HB,
    INDEX_DIGITAL_LATCH_LB,
    INDEX_DIGITAL_DIRECTION_MB, /* index = 8 */
    INDEX_DIGITAL_DIRECTION_UB,
    INDEX_DIGITAL_DIRECTION_HB,
    INDEX_DIGITAL_DIRECTION_LB,
    INDEX_DIGITAL_PORT_MB,      /* index = 12 */
    INDEX_DIGITAL_PORT_UB,
    INDEX_DIGITAL_PORT_HB,
    INDEX_DIGITAL_PORT_LB,
    INDEX_ANALOG0_GAIN_HB,      /* index = 16 */
    INDEX_ANALOG0_GAIN_LB,
    INDEX_ANALOG0_HB,
    INDEX_ANALOG0_LB,
    INDEX_ANALOG1_GAIN_HB,      /* index = 20 */
    INDEX_ANALOG1_GAIN_LB,
    INDEX_ANALOG1_HB,
    INDEX_ANALOG1_LB,
    INDEX_ANALOG2_GAIN_HB,      /* index = 24 */
    INDEX_ANALOG2_GAIN_LB,
    INDEX_ANALOG2_HB,
    INDEX_ANALOG2_LB,
    INDEX_ANALOG3_GAIN_HB,      /* index = 28 */
    INDEX_ANALOG3_GAIN_LB,
    INDEX_ANALOG3_HB,
    INDEX_ANALOG3_LB,
    INDEX_BOARD_CURRENT_MB,     /* index = 32 */
    INDEX_BOARD_CURRENT_UB,
    INDEX_BOARD_CURRENT_HB,
    INDEX_BOARD_CURRENT_LB,
    INDEX_BOARD_VOLTAGE_MB,     /* index = 36 */
    INDEX_BOARD_VOLTAGE_UB,
    INDEX_BOARD_VOLTAGE_HB,
    INDEX_BOARD_VOLTAGE_LB,
    TRISTHIS_DATA_SIZE          /* 40         */
} TRISTHIS_DATA_INDEX_TYPE;

typedef struct
{    
    uint32_t    latch;   
    uint32_t    port;
    uint32_t    direction;
} TRISTHIS_DIGITAL_PORT_TYPE;

typedef union
{
    struct
    {
        uint16_t reading;
        uint16_t gain;
    };
    //UINT32_VAL
    uint32_t    w;
} TRISTHIS_ANALOG_PORT_TYPE;

typedef union
{
    struct
    {
        unsigned LED1:1;
        unsigned LED2:1;
        unsigned LED3:1;
        unsigned LED4:1;
        unsigned LED5:1;
        unsigned LED6:1;
        unsigned LED7:1;
        unsigned LED8:1;
    };
    uint8_t w;
} TRISTHIS_LED_TYPE;

typedef union
{
    struct
    {
        unsigned configured:1; /* read only */
        unsigned V5p0Good:1;   /* read only */
        unsigned autoLEDmode:1;
        unsigned freshSupplyVoltage:1;
        unsigned freshSupplyCurrent:1;
        unsigned :1;
        unsigned :1;
        unsigned :1;
        unsigned :16;
    };
    struct
    {
        unsigned :24;
        TRISTHIS_LED_TYPE led;
    };
    uint32_t w;
} TRISTHIS_STATUS_TYPE;

typedef union
{
    uint8_t data[TRISTHIS_DATA_SIZE];
    struct
    {
        TRISTHIS_STATUS_TYPE status;        /* one 32 bit word */
        TRISTHIS_DIGITAL_PORT_TYPE digital; /* three 32 bit words */
        TRISTHIS_ANALOG_PORT_TYPE analog[TRISTHIS_NUMBER_ANALOG_PORTS];
        UINT32_VAL supplyCurrent;
        UINT32_VAL supplyVoltage;
    };
} TRISTHIS_DATA_TYPE;

/******************************************************************************/
/* commands                                                                   */
/******************************************************************************/

#define TRISTHIS_SPI_READ_COMMAND    (0x03)
#define TRISTHIS_SPI_WRITE_COMMAND   (0x02)
#define TRISTHIS_SPI_NO_COMMAND      (0b10101010)

/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/
#ifdef PIC32_CODE
BOOL TRISThisDigitalConfigure(void);
UINT32 TRISThisReadDigitalInputs(void);
UINT32 TRISThisReadDigitalLatches(void);
UINT32 TRISThisReadDigitalDirection(void);
BOOL TRISThisReadDigital(TRISTHIS_DIGITAL_PORT_TYPE*);
UINT32 TRISThisReadLEDs(void);
BOOL TRISThisSetLEDs(UINT32);
BOOL TRISThisReadLEDMode(void);
void TRISThisSetLEDAutoMode(BOOL);
BOOL TRISThisReadStatus(TRISTHIS_STATUS_TYPE *);
UINT32 TRISThisSetStatus(UINT32);
BOOL TRISThisConfigure(void);
BOOL TRISThisSetDigitalLatches(UINT32_VAL);
BOOL TRISThisSetDigitalDirection(UINT32_VAL);
#endif
#else /* #ifndef TRISTHIS_H */

#warning "Redundant include of TRISThis.h"

#endif	/* #ifndef TRISTHIS_H */

