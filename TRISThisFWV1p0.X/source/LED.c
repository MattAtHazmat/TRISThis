/****************************************************/
#include <common.h>
#include <tick.h>
#include <LED.h>
enum LED_STATE_TYPE LEDState;

void LEDInitialize(void)
{
    LEDState=LED_STATE_ALL_OFF;
    LED1_OUT=LED_OFF;
    LED2_OUT=LED_OFF;
    LED3_OUT=LED_OFF;
    LED4_OUT=LED_OFF;
    LED5_OUT=LED_OFF;
    LED6_OUT=LED_OFF;
    LED7_OUT=LED_OFF;
    LED8_OUT=LED_OFF;
    LED1_DIRECTION=TRIS_OUT;
    LED2_DIRECTION=TRIS_OUT;
    LED3_DIRECTION=TRIS_OUT;
    LED4_DIRECTION=TRIS_OUT;
    LED5_DIRECTION=TRIS_OUT;
    LED6_DIRECTION=TRIS_OUT;
    LED7_DIRECTION=TRIS_OUT;
    LED8_DIRECTION=TRIS_OUT;
}

void DoLEDs(void)
{
    static TICK_TYPE timeoutTime=0;
    TICK_TYPE now;
    now=TickGet();
    if(now<timeoutTime)// <editor-fold defaultstate="collapsed" desc="comment">
{
        return;
    }// </editor-fold>
    else// <editor-fold defaultstate="collapsed" desc="comment">
    {
        timeoutTime = now + LED_CASCADE_DELAY;
    }// </editor-fold>
    switch(LEDState)// <editor-fold defaultstate="collapsed" desc="comment">
    {
        case LED_STATE_ALL_OFF:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            LED1_OUT = LED_OFF;
            LED2_OUT = LED_OFF;
            LED3_OUT = LED_OFF;
            LED4_OUT = LED_OFF;
            LED5_OUT = LED_OFF;
            LED6_OUT = LED_OFF;
            LED7_OUT = LED_OFF;
            LED8_OUT = LED_OFF;
            LEDState = LED_STATE_LED1_TOGGLE;
            break;
        }// </editor-fold>
        case LED_STATE_LED1_TOGGLE:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            LED1_OUT ^= 1;
            LEDState = LED_STATE_LED2_TOGGLE;
            break;
        }// </editor-fold>
        case LED_STATE_LED2_TOGGLE:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            LED2_OUT ^= 1;
            LEDState = LED_STATE_LED3_TOGGLE;
            break;
        }// </editor-fold>
        case LED_STATE_LED3_TOGGLE:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            LED3_OUT ^= 1;
            LEDState = LED_STATE_LED4_TOGGLE;
            break;
        }// </editor-fold>
        case LED_STATE_LED4_TOGGLE:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            LED4_OUT ^= 1;
            LEDState = LED_STATE_LED5_TOGGLE;
            break;
        }// </editor-fold>
        case LED_STATE_LED5_TOGGLE:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            LED5_OUT ^= 1;
            LEDState = LED_STATE_LED6_TOGGLE;
            break;
        }// </editor-fold>
        case LED_STATE_LED6_TOGGLE:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            LED6_OUT ^= 1;
            LEDState = LED_STATE_LED7_TOGGLE;
            break;
        }// </editor-fold>
        case LED_STATE_LED7_TOGGLE:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            LED7_OUT ^= 1;
            LEDState = LED_STATE_LED8_TOGGLE;
            break;
        }// </editor-fold>
        case LED_STATE_LED8_TOGGLE:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            LED8_OUT ^= 1;
            LEDState = LED_STATE_LED1_TOGGLE;
            break;
        }// </editor-fold>
    }// </editor-fold>

}
