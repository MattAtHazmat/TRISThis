/******************************************************************************/
/* File:   TRISThisAnalog.c                                                   */
/* Author: Matt Bennett                                                       */
/*                                                                            */
/* Created on May 12, 2014, 8:20 PM                                           */
/******************************************************************************/

#include <common.h>
#include <MCP4461.h>
#include <TRISThis.h>
#include <TRISThisAnalog.h>

uint16_t analogGain[TRISTHIS_NUMBER_ANALOG_PORTS];
uint16_t analogReading[TRISTHIS_NUMBER_ANALOG_PORTS];
/******************************************************************************/

BOOL TRISThisGetAnalogGain(unsigned int channel,uint16_t *gain)
{
    BOOL returnValue=FALSE;
    if(channel<TRISTHIS_NUMBER_ANALOG_PORTS)
    {
        *gain=analogGain[channel];
        returnValue=TRUE;
    }
    return returnValue;
}

BOOL TRISThisGetAnalog(unsigned int channel,uint16_t *analog)
{
    BOOL returnValue=FALSE;
    if(channel<TRISTHIS_NUMBER_ANALOG_PORTS)
    {
        *analog=analogReading[channel];
        returnValue=TRUE;
    }
    return returnValue;
}

BOOL TRISThisSetAnalogGain(unsigned int channel,uint16_t tempGain)
{
    BOOL returnValue=FALSE;
    if(channel<TRISTHIS_NUMBER_ANALOG_PORTS)
    {
        analogGain[channel]=tempGain;
        returnValue=TRUE;
    }
    return returnValue;
}

BOOL DoTRISThisAnalog(void)
{
    BOOL returnValue=FALSE;
    
    return returnValue;
}
/******************************************************************************/
