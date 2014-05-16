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

/******************************************************************************/

uint16_t analogGain[TRISTHIS_NUMBER_ANALOG_PORTS];
uint16_t analogReading[TRISTHIS_NUMBER_ANALOG_PORTS];
TRISTHIS_ANALOG_PORT_STATUS_TYPE status;
TRISTHIS_DATA_TYPE TRISThisData;

/******************************************************************************/
BOOL TRISThisAnalogConfigure(void)
{
    BOOL returnValue=FALSE;
    /* TODO: this */
    return returnValue;
}

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

/******************************************************************************/

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

/******************************************************************************/

BOOL TRISThisSetAnalogGain(unsigned int channel,uint16_t tempGain)
{
    BOOL returnValue=FALSE;
    if(channel<TRISTHIS_NUMBER_ANALOG_PORTS)
    {
        TRISThisData.analog[channel].gain=tempGain;
        returnValue=TRUE;
    }
    return returnValue;
}

/******************************************************************************/

BOOL TRISThisStartADCConversion(unsigned int channel)
{
    BOOL returnValue=FALSE;
    if(channel<TRISTHIS_NUMBER_ANALOG_PORTS)
    {
        
    }
    return returnValue;
}

/******************************************************************************/

BOOL TRISThisAnalogConversionDone(void)
{
    return TRUE;
}

/******************************************************************************/

BOOL TRISThisSetAnalog(unsigned int channel, uint16_t analogValue)
{
    BOOL returnValue=FALSE;
    if(channel<TRISTHIS_NUMBER_ANALOG_PORTS)
    {
        /* get the analog value from the ADC register */
        TRISThisData.analog[channel].reading=analogValue;
        /* write the value into the SPI output directory*/

    }
    return returnValue;
}

/******************************************************************************/

BOOL DoTRISThisAnalog(void)
{
    BOOL returnValue=FALSE;
    static TRISTHIS_ANALOG_STATE state=ANALOG_STATE_IDLE;
    switch (state)
    {
        case ANALOG_STATE_IDLE:
        {
            if(status.w!=0)
            {
                state=ANALOG_STATE_START0;
            }
            break;
        }
        case ANALOG_STATE_START0:
        {
            if(status.start0)
            {
                /* status ADC channel 0 */
                status.start0=FALSE;
                if(TRISThisStartADCConversion(0))
                {
                    state=ANALOG_STATE_WAIT0;
                    break;
                }
            }
            /* check the next channel */
            state=ANALOG_STATE_START1;
            
            break;
        }
        case ANALOG_STATE_WAIT0:
        {
            /* wait for ADC to complete */
            if(TRISThisAnalogConversionDone())
            {
                status.ready0=FALSE;
                /* when the ADC is done, check the next channel */
                state=ANALOG_STATE_START1;
            }
            break;
        }
        case ANALOG_STATE_START1:
        {
            if(status.start1)
            {
                /* status ADC channel 1 */
                status.start1=FALSE;
                if(TRISThisStartADCConversion(1))
                {
                    state=ANALOG_STATE_WAIT1;
                    break;
                }
            }
            /* check the next channel */
            state=ANALOG_STATE_START2;
            break;
        }
        case ANALOG_STATE_WAIT1:
        {
            /* wait for ADC to complete */
            if(TRISThisAnalogConversionDone())
            {
                /* when the ADC is done, check the next channel */
                state=ANALOG_STATE_START2;
            }
            break;
        }
        case ANALOG_STATE_START2:
        {
            if(status.start2)
            {
                /* status ADC channel 2 */
                status.start2=FALSE;
                if(TRISThisStartADCConversion(2))
                {
                    state=ANALOG_STATE_WAIT2;
                    break;
                }
            }
            /* check the next channel */
            state=ANALOG_STATE_START3;
            break;
        }
        case ANALOG_STATE_WAIT2:
        {
            /* wait for ADC to complete */
            if(TRISThisAnalogConversionDone())
            {
                /* when the ADC is done, check the next channel */
                state=ANALOG_STATE_START3;
            }
            break;
        }
        case ANALOG_STATE_START3:
        {
            if(status.start3)
            {
                /* status ADC channel 3 */
                status.start3=FALSE;
                if(TRISThisStartADCConversion(3))
                {
                    state=ANALOG_STATE_WAIT3;
                    break;
                }
            }
            /* done, start over */
            state=ANALOG_STATE_IDLE;
            break;
        }
        case ANALOG_STATE_WAIT3:
        {
            if(TRISThisAnalogConversionDone())
            {
                state=ANALOG_STATE_IDLE;
            }
            break;
        }
        default:
        {
            state = ANALOG_STATE_IDLE;
            break;
        }
    }
    return returnValue;
}



/******************************************************************************/
