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
    UINT8 data[TRISTHIS_DATA_SIZE];
    struct
    {
        TRISTHIS_DIGITAL_PORT_TYPE digital[TRISTHIS_NUMBER_DIGITAL_PORTS];
        TRISTHIS_ANALOG_PORT_TYPE analog[TRISTHIS_NUMBER_ANALOG_PORTS];
    };
} TRISTHIS_DATA_TYPE;
/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

#else /* #ifndef TRISTHIS_H */

#warning "Redundant include of TRISThis.h"

#endif	/* #ifndef TRISTHIS_H */

