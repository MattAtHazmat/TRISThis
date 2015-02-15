/******************************************************************************/
/* File:   clockomatic.h                                                      */
/* Author: matt                        `                                      */
/*                                                                            */
/* Created on September 13, 2013, 8:42 PM                                     */
/******************************************************************************/

#ifndef _CLOCKOMATIC_H_
#define	_CLOCKOMATIC_H_

//#define ALLOW_TURBO_MODE
#define BOUNDS_CHECK_CLOCKS

/******************************************************************************/
/* Oscillator info */

#define PLL_INPUT_DIVIDER   (2) /* set via configuration bits only */
#define PLL_MULTIPLIER      (20)
#define PLL_DIVIDER         (1)
#define PERIPHERAL_DIVIDER  (1)

/******************************************************************************/
/* for some reason the following won't work with a pragma- doing it in        */
/* configuration.h instead                                                    */
//#if PLL_INPUT_DIVIDER==12
// #define CONFIG_PLL_INPUT_DIVIDER DIV_12
//#elif PLL_INPUT_DIVIDER==10
// #define CONFIG_PLL_INPUT_DIVIDER DIV_10
//#elif PLL_INPUT_DIVIDER==6
// #define CONFIG_PLL_INPUT_DIVIDER DIV_6
//#elif PLL_INPUT_DIVIDER==5
// #define CONFIG_PLL_INPUT_DIVIDER DIV_5
//#elif PLL_INPUT_DIVIDER==4
// #define CONFIG_PLL_INPUT_DIVIDER DIV_4
//#elif PLL_INPUT_DIVIDER==3
// #define CONFIG_PLL_INPUT_DIVIDER DIV_3
//#elif PLL_INPUT_DIVIDER==2
// #define CONFIG_PLL_INPUT_DIVIDER DIV_2
//#elif PLL_INPUT_DIVIDER==1
// #define CONFIG_PLL_INPUT_DIVIDER DIV_1
//#else
// #error "PLL_INPUT_DIVIDER not correctly defined"
//#endif

#if PLL_MULTIPLIER==24
    #define PLL_OUTPUT_MULT OSC_PLL_MULT_24
#elif PLL_MULTIPLIER==21
    #define PLL_OUTPUT_MULT OSC_PLL_MULT_21
#elif PLL_MULTIPLIER==20
    #define PLL_OUTPUT_MULT OSC_PLL_MULT_20
#elif PLL_MULTIPLIER==19
    #define PLL_OUTPUT_MULT OSC_PLL_MULT_19
#elif PLL_MULTIPLIER==18
    #define PLL_OUTPUT_MULT OSC_PLL_MULT_18
#elif PLL_MULTIPLIER==17
    #define PLL_OUTPUT_MULT OSC_PLL_MULT_17
#elif PLL_MULTIPLIER==16
    #define PLL_OUTPUT_MULT OSC_PLL_MULT_16
#elif PLL_MULTIPLIER==15
    #define PLL_OUTPUT_MULT OSC_PLL_MULT_15
#else
    #error "PLL_MULTIPLIER not correctly defined"
#endif

#if PLL_DIVIDER==256
    #define PLL_OUTPUT_DIVIDER OSC_PLL_POST_256
#elif PLL_DIVIDER==64
    #define PLL_OUTPUT_DIVIDER OSC_PLL_POST_64
#elif PLL_DIVIDER==32
    #define PLL_OUTPUT_DIVIDER OSC_PLL_POST_32
#elif PLL_DIVIDER==16
    #define PLL_OUTPUT_DIVIDER OSC_PLL_POST_16
#elif PLL_DIVIDER==8
    #define PLL_OUTPUT_DIVIDER OSC_PLL_POST_8
#elif PLL_DIVIDER==4
    #define PLL_OUTPUT_DIVIDER OSC_PLL_POST_4
#elif PLL_DIVIDER==2
    #define PLL_OUTPUT_DIVIDER OSC_PLL_POST_2
#elif PLL_DIVIDER==1
    #define PLL_OUTPUT_DIVIDER OSC_PLL_POST_1
#else
    #error "PLL_DIVIDER not correctly defined"
#endif

#if PERIPHERAL_DIVIDER==1
    #define PBCLK_DIV OSC_PB_DIV_1
#elif PERIPHERAL_DIVIDER==2
    #define PBCLK_DIV OSC_PB_DIV_2
#elif PERIPHERAL_DIVIDER==4
    #define PBCLK_DIV OSC_PB_DIV_4
#elif PERIPHERAL_DIVIDER==8
    #define PBCLK_DIV OSC_PB_DIV_8
#else
    #error "PERIPHERAL_DIVIDER not correctly defined"
#endif

#define GetSystemClock()        ((CRYSTAL_FREQUENCY*PLL_MULTIPLIER)/(PLL_INPUT_DIVIDER*PLL_DIVIDER))
#define GetPeripheralClock()    (GetSystemClock()/PERIPHERAL_DIVIDER)


#ifdef BOUNDS_CHECK_CLOCKS
    #ifdef ALLOW_TURBO_MODE
        #define MAXIMUM_CLOCK   (96000000ul)
    #else
        #define MAXIMUM_CLOCK   (80000000ul)
    #endif
    #define PLL_INPUT (CRYSTAL_FREQUENCY/PLL_INPUT_DIVIDER)
    #if PLL_INPUT<(3920000ul)
        #warning "Input to PLL is below specification"
    #endif
    #if PLL_INPUT>(5000000ul)
        #warning "Input to PLL is above specification"
    #endif
    #if GetSystemClock()>MAXIMUM_CLOCK
        #warning "System clock is above specification"
    #endif
#endif /*#ifdef BOUNDS_CHECK_CLOCKS*/


/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

#else /* #ifndef CLOCKOMATIC_H */

#warning "Redundant include of clockomatic.h"

#endif	/* #ifndef CLOCKOMATIC_H */

