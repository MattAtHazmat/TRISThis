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
TRISTHIS_ANALOG_START_TYPE start;
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
    static TRISTHIS_ANALOG_STATE state=ANALOG_STATE_IDLE;
    switch (TRISTHIS_ANALOG_STATE)
    {
        case ANALOG_STATE_IDLE:
        {
            if(AnalogStartTupe)
            TRISTHIS_ANALOG_START_TYPE;
            break:
        };
        case ANALOG_STATE_START0:
        {

            break;
        };
        case ANALOG_STATE_WAIT0:
        {

            break;
        };
        case ANALOG_STATE_START1:
        {

            break;
        };
        case ANALOG_STATE_WAIT1:
        {

            break;
        };
        case ANALOG_STATE_START2:
        {

            break;
        };
        case ANALOG_STATE_WAIT2:
        {

            break;
        };
        case ANALOG_STATE_START3:
        {

            break;
        };
        case ANALOG_STATE_WAIT3:
        {

            break;
        };
        default:
        {
           TRISTHIS_ANALOG_STATE= ANALOG_STATE_IDLE:
            break;
        }
    }
    return returnValue;
}

BOOL TRISThisStart(unsigned int channel)
BOOL TRISThisDone(unsigned int channel);
BOOL TRISThisSetAnalog(unsigned int channel, uint16_t *analogValue);
/******************************************************************************/
