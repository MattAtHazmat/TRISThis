/******************************************************************************/
/* File:   TRISThis.h                                                         */
/* Author: matt                                                               */
/*                                                                            */
/* Created on September 14, 2013, 9:54 AM                                     */
/******************************************************************************/

#ifndef _TRISTHIS_H_
#define	_TRISTHIS_H_

#define TRISTHIS_DATA_SIZE              (0x20)
#define TRISTHIS_NUMBER_DIGITAL_PORTS   (2)
#define TRISTHIS_NUMBER_ANALOG_PORTS    (4)
#define STATUS_READ_ONLY_MASK           (0x00000001)

/* TODO: can these be automatically generated? */
#define INDEX_STATUS_MB             (0)
#define INDEX_STATUS_UB             (1)
#define INDEX_STATUS_HB             (2)
#define INDEX_STATUS_LB             (3)
#define INDEX_LED_X                 (4)
#define INDEX_LED_Y                 (5)
#define INDEX_LED_Z                 (6)
#define INDEX_LED                   (7)
#define INDEX_DIGITAL_LATCH_0       (8)
#define INDEX_DIGITAL_PORT_0        (9)
#define INDEX_DIGITAL_DIRECTION_0   (10)
#define INDEX_DIGITAL_X_0           (11)
#define INDEX_DIGITAL_LATCH_1       (12)
#define INDEX_DIGITAL_PORT_1        (13)
#define INDEX_DIGITAL_DIRECTION_1   (14)
#define INDEX_DIGITAL_X_1           (15)

typedef union
{
    struct
    {
        UINT8_VAL latch;
        UINT8_VAL port;
        UINT8_VAL direction;
    };
    UINT32_VAL w;
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
        unsigned configured:1;
        unsigned autoLEDmode:1;
    };
    UINT32_VAL w;
} TRISTHIS_STATUS_TYPE;

typedef union
{
    UINT8 data[TRISTHIS_DATA_SIZE];
    struct
    {
        TRISTHIS_STATUS_TYPE status;
        TRISTHIS_LED_TYPE LEDs;
        TRISTHIS_DIGITAL_PORT_TYPE digital[TRISTHIS_NUMBER_DIGITAL_PORTS];
        TRISTHIS_ANALOG_PORT_TYPE analog[TRISTHIS_NUMBER_ANALOG_PORTS];
    };
} TRISTHIS_DATA_TYPE;

/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

BOOL TRISThisDigitalConfigure(void);
void TRISThisReadDigitalInputs(void);
void TRISThisReadDigitalLatches(void);
void TRISThisReadDigitalDirection(void);
BOOL TRISThisReadLEDMode(void);
void TRISThisSetLEDAutoMode(BOOL);
UINT32 TRISThisReadStatus(void);
UINT32 TRISThisSetStatus(UINT32);
BOOL TRISThisConfigure(void);

#else /* #ifndef TRISTHIS_H */

#warning "Redundant include of TRISThis.h"

#endif	/* #ifndef TRISTHIS_H */

