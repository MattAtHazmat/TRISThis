/******************************************************************************/
/* File:   TRISThisAnalog.h                                                   */
/* Author: Matt Bennett                                                       */
/*                                                                            */
/* Created on May 12, 2014, 8:22 PM                                           */
/******************************************************************************/

#ifndef _TRISTHIS_ANALOG_H_
#define	_TRISTHIS_ANALOG_H_

typedef enum
{
    ANALOG_STATE_IDLE=0,
    ANALOG_STATE_START0,
    ANALOG_STATE_WAIT0,
    ANALOG_STATE_START1,
    ANALOG_STATE_WAIT1,
    ANALOG_STATE_START2,
    ANALOG_STATE_WAIT2,
    ANALOG_STATE_START3,
    ANALOG_STATE_WAIT3
} TRISTHIS_ANALOG_STATE;

typedef union
{
    struct
    {
        unsigned ready0:1;
        unsigned ready1:1;
        unsigned ready2:1;
        unsigned ready3:1;
        unsigned start0:1;
        unsigned start1:1;
        unsigned start2:1;
        unsigned start3:1;
    };
    uint8_t w;
} TRISTHIS_ANALOG_START_TYPE;

BOOL TRISThisGetAnalogGain(unsigned int,uint16_t *);
BOOL TRISThisSetAnalogGain(unsigned int,uint16_t);
BOOL TRISThisGetAnalog(unsigned int ,uint16_t *);
BOOL TRISThisStart(unsigned int);
BOOL TRISThisDone(unsigned int channel);
BOOL TRISThisSetAnalog(unsigned int, uint16_t);
BOOL DoTRISThisAnalog(void);
BOOL TRISThisStartADCConversion(unsigned int);
BOOL TRISThisAnalogConversionDone(void);
BOOL TRISThisAnalogConfigure(void);

#else
    #warning "Redundant include of TRISThisAnalog.h"

#endif	/* _TRISTHIS_ANALOG_H_ */

