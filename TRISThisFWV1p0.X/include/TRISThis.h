/******************************************************************************/
/* File:   TRISThis.h                                                         */
/* Author: matt                                                               */
/*                                                                            */
/* Created on September 14, 2013, 9:54 AM                                     */
/******************************************************************************/

#ifndef _TRISTHIS_H_
#define	_TRISTHIS_H_

//#define TRISTHIS_DATA_SIZE              (0x20)
#define TRISTHIS_NUMBER_DIGITAL_PORTS   (2)
#define TRISTHIS_NUMBER_ANALOG_PORTS    (4)
#define STATUS_READ_ONLY_MASK           (0x00000003)

/* TODO: can these be automatically generated? */
typedef enum {
    INDEX_STATUS_MB=0,
    INDEX_STATUS_UB,
    INDEX_STATUS_HB,
    INDEX_STATUS_LB,
    INDEX_LED_Z,
    INDEX_LED_Y,
    INDEX_LED_X,
    INDEX_LED,
    INDEX_DIGITAL_LATCH_MB,
    INDEX_DIGITAL_LATCH_UB,
    INDEX_DIGITAL_LATCH_HB,
    INDEX_DIGITAL_LATCH_LB,
    INDEX_DIGITAL_DIRECTION_MB,
    INDEX_DIGITAL_DIRECTION_UB,
    INDEX_DIGITAL_DIRECTION_HB,
    INDEX_DIGITAL_DIRECTION_LB,
    INDEX_DIGITAL_PORT_MB,
    INDEX_DIGITAL_PORT_UB,
    INDEX_DIGITAL_PORT_HB,
    INDEX_DIGITAL_PORT_LB,
    INDEX_ANALOG0_GAIN_HB,
    INDEX_ANALOG0_GAIN_LB,
    INDEX_ANALOG0_HB,
    INDEX_ANALOG0_LB,
    INDEX_ANALOG1_GAIN_HB,
    INDEX_ANALOG1_GAIN_LB,
    INDEX_ANALOG1_HB,
    INDEX_ANALOG1_LB,
    INDEX_ANALOG2_GAIN_HB,
    INDEX_ANALOG2_GAIN_LB,
    INDEX_ANALOG2_HB,
    INDEX_ANALOG2_LB,
    INDEX_ANALOG3_GAIN_HB,
    INDEX_ANALOG3_GAIN_LB,
    INDEX_ANALOG3_HB,
    INDEX_ANALOG3_LB,
    INDEX_BOARD_CURRENT_MB,
    INDEX_BOARD_CURRENT_UB,
    INDEX_BOARD_CURRENT_HB,
    INDEX_BOARD_CURRENT_LB,
    INDEX_BOARD_VOLTAGE_MB,
    INDEX_BOARD_VOLTAGE_UB,
    INDEX_BOARD_VOLTAGE_HB,
    INDEX_BOARD_VOLTAGE_LB,
    TRISTHIS_DATA_SIZE
} TRISTHIS_DATA_INDEX_TYPE;

typedef struct
{
    UINT32_VAL latch;
    UINT32_VAL port;
    UINT32_VAL direction;
} TRISTHIS_DIGITAL_PORT_TYPE;

typedef union
{
    struct
    {
        UINT16_VAL reading;
        UINT16_VAL gain;
    };
    UINT32_VAL w;
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
    UINT32_VAL w;
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
    };
    UINT32_VAL w;
} TRISTHIS_STATUS_TYPE;

typedef union
{
    UINT8 data[TRISTHIS_DATA_SIZE];
    struct
    {
        /* each member should be 32 bits wide */
        TRISTHIS_STATUS_TYPE status;
        TRISTHIS_LED_TYPE LEDs;
        TRISTHIS_DIGITAL_PORT_TYPE digital;
        TRISTHIS_ANALOG_PORT_TYPE analog[TRISTHIS_NUMBER_ANALOG_PORTS];
        UINT32_VAL supplyCurrent;
        UINT32_VAL supplyVoltage;
    };
} TRISTHIS_DATA_TYPE;

/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

BOOL TRISThisDigitalConfigure(void);
UINT32 TRISThisReadDigitalInputs(void);
UINT32 TRISThisReadDigitalLatches(void);
UINT32 TRISThisReadDigitalDirection(void);
UINT32 TRISThisReadLEDs(void);
BOOL TRISThisSetLEDs(UINT32);
BOOL TRISThisReadLEDMode(void);
void TRISThisSetLEDAutoMode(BOOL);
UINT32 TRISThisReadStatus(void);
UINT32 TRISThisSetStatus(UINT32);
BOOL TRISThisConfigure(void);

#else /* #ifndef TRISTHIS_H */

#warning "Redundant include of TRISThis.h"

#endif	/* #ifndef TRISTHIS_H */

