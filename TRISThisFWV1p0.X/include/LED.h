/* 
 * File:   LED.h
 * Author: mjb
 *
 * Created on December 22, 2012, 7:27 PM
 */

#ifndef _LED_H_
#define	_LED_H_

enum LED_STATE_TYPE
{
    LED_STATE_ALL_OFF=0,
    LED_STATE_LED1_TOGGLE,
    LED_STATE_LED2_TOGGLE,
    LED_STATE_LED3_TOGGLE,
    LED_STATE_LED4_TOGGLE,
    LED_STATE_LED5_TOGGLE,
    LED_STATE_LED6_TOGGLE,
    LED_STATE_LED7_TOGGLE,
    LED_STATE_LED8_TOGGLE,
    LED_STATE_MANUAL
};

/* prototypes */

BOOL LEDInitialize(void);
void DoLEDs(void);
UINT8 ReadLEDs(void);
void SetLEDs(UINT8);
BOOL GetLEDAutoMode(void);

#else
    #warning "Redundant include of LED.h"

#endif	/* LED_H */

