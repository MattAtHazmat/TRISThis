/******************************************************************************/
/* File:   TRISThis.h                                                         */
/* Author: matt                                                               */
/*                                                                            */
/* Created on September 14, 2013, 9:54 AM                                     */
/******************************************************************************/

#ifndef _TRISTHIS_H_
#define	_TRISTHIS_H_

#define TRISTHIS_DATA_SIZE (16)
#define TRISTHIS_NUMBER_DIGITAL_PORTS 2
#define TRISTHIS_NUMBER_ANALOG_PORTS 4

/* TODO: can these be automatically generated? */
#define INDEX_DIGITAL_DIRECTION_0   (1)
#define INDEX_DIGITAL_DIRECTION_1   (2)
#define INDEX_DIGITAL_LATCH_0       (3)
#define INDEX_DIGITAL_LATCH_1       (4)

typedef struct
{
    UINT8_VAL latch;
    UINT8_VAL port;
    UINT8_VAL direction;
} TRISTHIS_DIGITAL_PORT_TYPE;

typedef struct
{
    UINT16 reading;
    UINT16 gain;
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
    UINT8 w;
} TRISTHIS_LED_TYPE;

typedef union
{
    UINT8 data[TRISTHIS_DATA_SIZE];
    struct
    {
        TRISTHIS_DIGITAL_PORT_TYPE digital[TRISTHIS_NUMBER_DIGITAL_PORTS];
        TRISTHIS_ANALOG_PORT_TYPE analog[TRISTHIS_NUMBER_ANALOG_PORTS];
        TRISTHIS_LED_TYPE LEDs;
    };
} TRISTHIS_DATA_TYPE;

/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

void TRISThisDigitalConfigure(void);
void TRISThisReadDigitalInputs(void);
void TRISThisReadDigitalLatches(void);
void TRISThisReadDigitalDirection(void);

#else /* #ifndef TRISTHIS_H */

#warning "Redundant include of TRISThis.h"

#endif	/* #ifndef TRISTHIS_H */

