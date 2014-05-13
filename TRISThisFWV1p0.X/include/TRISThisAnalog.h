/******************************************************************************/
/* File:   TRISThisAnalog.h                                                   */
/* Author: Matt Bennett                                                       */
/*                                                                            */
/* Created on May 12, 2014, 8:22 PM                                           */
/******************************************************************************/

#ifndef _TRISTHIS_ANALOG_H_
#define	_TRISTHIS_ANALOG_H_

typedef union
{
    struct
    {
        unsigned :4;
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
BOOL DoTRISThisAnalog(void);

#else
    #warning "Redundant include of TRISThisAnalog.h"

#endif	/* _TRISTHIS_ANALOG_H_ */

