/******************************************************************************/
#include <common.h>
#include <tick.h>
#include <TRISThis.h>
#include <LED.h>
enum LED_STATE_TYPE LEDState;
extern TRISTHIS_DATA_TYPE TRISThisData;

/******************************************************************************/

BOOL LEDInitialize(void)
{
    LED_ALL_OFF;
    SET_LED_DIRECTION;
    //LED1_DIRECTION=TRIS_OUT;
    //LED2_DIRECTION=TRIS_OUT;
    //LED3_DIRECTION=TRIS_OUT;
    //LED4_DIRECTION=TRIS_OUT;
    //LED5_DIRECTION=TRIS_OUT;
    //LED6_DIRECTION=TRIS_OUT;
    //LED7_DIRECTION=TRIS_OUT;
    //LED8_DIRECTION=TRIS_OUT;
    //LEDState=LED_STATE_MANUAL;
    LEDState=LED_STATE_ALL_OFF;
    TRISThisData.status.autoLEDmode=TRUE;
    TRISThisData.LEDs.w.Val=0;
    return TRUE;
}

/******************************************************************************/

UINT8 ReadLEDs(void)
{
    UINT8_VAL LEDTemp;
    LEDTemp.bits.b0=!LED1_OUT;
    LEDTemp.bits.b1=!LED2_OUT;
    LEDTemp.bits.b2=!LED3_OUT;
    LEDTemp.bits.b3=!LED4_OUT;
    LEDTemp.bits.b4=!LED5_OUT;
    LEDTemp.bits.b5=!LED6_OUT;
    LEDTemp.bits.b6=!LED7_OUT;
    LEDTemp.bits.b7=!LED8_OUT;
    return LEDTemp.Val;
}

/******************************************************************************/

void SetLEDs(UINT8 toSet)
{
    UINT8_VAL tempLEDs;
    tempLEDs.Val=toSet;
    LED1_OUT=!tempLEDs.bits.b0;
    LED2_OUT=!tempLEDs.bits.b1;
    LED3_OUT=!tempLEDs.bits.b2;
    LED4_OUT=!tempLEDs.bits.b3;
    LED5_OUT=!tempLEDs.bits.b4;
    LED6_OUT=!tempLEDs.bits.b5;
    LED7_OUT=!tempLEDs.bits.b6;
    LED8_OUT=!tempLEDs.bits.b7;
}

/******************************************************************************/

void DoLEDs(void)
{
    static TICK_TYPE timeoutTime=0;
    TICK_TYPE now;
    if(LEDState!=LED_STATE_MANUAL)
    {
        now=TickGet();
        if(now<timeoutTime)
        {
            return;
        }
        else
        {
            timeoutTime = now + LED_CASCADE_DELAY;
        }
        switch(LEDState)
        {
            case LED_STATE_LED1_TOGGLE:
            {
                LED1_TOGGLE;
                LEDState = LED_STATE_LED2_TOGGLE;
                break;
            }
            case LED_STATE_LED2_TOGGLE:
            {
                LED2_TOGGLE;
                LEDState = LED_STATE_LED3_TOGGLE;
                break;
            }
            case LED_STATE_LED3_TOGGLE:
            {
                LED3_TOGGLE;
                LEDState = LED_STATE_LED4_TOGGLE;
                break;
            }
            case LED_STATE_LED4_TOGGLE:
            {
                LED4_TOGGLE;
                LEDState = LED_STATE_LED5_TOGGLE;
                break;
            }
            case LED_STATE_LED5_TOGGLE:
            {
                LED5_TOGGLE;
                LEDState = LED_STATE_LED6_TOGGLE;
                break;
            }
            case LED_STATE_LED6_TOGGLE:
            {
                LED6_TOGGLE;
                LEDState = LED_STATE_LED7_TOGGLE;
                break;
            }
            case LED_STATE_LED7_TOGGLE:
            {
                LED7_TOGGLE;
                LEDState = LED_STATE_LED8_TOGGLE;
                break;
            }
            case LED_STATE_LED8_TOGGLE:
            {
                LED8_TOGGLE;
                LEDState = LED_STATE_LED1_TOGGLE;
                break;
            }
            case LED_STATE_ALL_OFF:
            default:
            {
                LED_ALL_OFF;
                LEDState = LED_STATE_LED1_TOGGLE;
                break;
            }
        }
    }
    TRISThisData.LEDs.w.byte.LB=ReadLEDs();
}

/******************************************************************************/

BOOL LEDAutoMode(BOOL toSet)
{
    BOOL returnValue=FALSE;
    if(toSet)
    {
        returnValue=TRUE;
        LEDState=LED_STATE_ALL_OFF;
    }
    else
    {
        LEDState=LED_STATE_MANUAL;
    }
    return returnValue;
}

/******************************************************************************/
