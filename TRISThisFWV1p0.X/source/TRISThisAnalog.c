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
    switch (state)
    {
        case ANALOG_STATE_IDLE:
        {
            if(start.w!=0)
            {
                state=ANALOG_STATE_START0;
            }
            break;
        }
        case ANALOG_STATE_START0:
        {
            if(start.start0)
            {
                /* start ADC channel 0 */
                start.start0=FALSE;
                state=ANALOG_STATE_WAIT0;
            }
            else
            {
                /* check the next channel */
                state=ANALOG_STATE_START1;
            }
            break;
        }
        case ANALQG_STATE_WAIT0:
        {
            /* wait for ADC to complete */

            /* when the ADC is done, check the next channel */
            state=ANALOG_STATE_START1;
            break;
        }
        case ANALOG_STATE_START1:
        {
            if(start.start1)
            {
                /* start ADC channel 0 */
                start.start1=FALSE;
                state=ANALOG_STATE_WAIT1;
            }
            else
            {
                /* check the next channel */
                state=ANALOG_STATE_START2;
            }
            break;
        }
        case ANALOG_STATE_WAIT1:
        {
            /* wait for ADC to complete */

            /* when the ADC is done, check the next channel */
            state=ANALOG_STATE_START2;
            break;
        }
        case ANALOG_STATE_START2:
        {
            if(start.start2)
            {
                /* start ADC channel 0 */
                start.start2=FALSE;
                state=ANALOG_STATE_WAIT2;
            }
            else
            {
                /* check the next channel */
                state=ANALOG_STATE_START3;
            }
            break;
        }
        case ANALOG_STATE_WAIT2:
        {
            /* wait for ADC to complete */

            /* when the ADC is done, check the next channel */
            state=ANALOG_STATE_START3;
            break;
        }
        case ANALOG_STATE_START3:
        {
            if(start.start3)
            {
                /* start ADC channel 0 */
                start.start3=FALSE;
                state=ANALOG_STATE_WAIT3;
            }
            else
            {
                /* done, start over */
                state=ANALOG_STATE_IDLE;
            }
            break;
        }
        case ANALOG_STATE_WAIT3:
        {
            state=ANALOG_STATE_IDLE;
            break;
        }
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
