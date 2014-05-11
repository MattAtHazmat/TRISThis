/******************************************************************************/
/* File:   mainv1p0.c                                                         */
/* Author: Matt Bennett                                                       */
/*                                                                            */
/* Created on December 16, 2012, 3:51 PM                                      */
/* Updated August 2013                                                        */
/******************************************************************************/

#include <common.h>
#include <tick.h>
#include <LED.h>
#include <PAC1710.h>
#include <MCP4461.h>
#include <I2C_Bus_Master.h>
#include <TRISThis.h>
#include <configuration.h>
#include <mainv1p0.h>

/******************************************************************************/

#ifdef USE_PAC1710
    extern UINT16_VAL currentHolding;
    extern UINT16_VAL voltageHolding;
    /* file scope for DMCI */
    INT16 monitorCurrentReadings[CURRENT_HISTORY_SIZE];
    UINT16 monitorVoltageReadings[VOLTAGE_HISTORY_SIZE];
#endif

/******************************************************************************/

int main(void)
{
    /* variables local to main()                                              */
    UINT8 dataRead;
    TICK_TYPE timeoutTime;
    #ifdef USE_I2C
        I2CBUS_COMMAND_TYPE command;
    #endif
    UINT16_VAL vSource;
    //INT16 readingHoldingSigned;
    //UINT16 readingHoldingUnsigned;
    /* local to main() and initialized*/
    //int currentIndex=0;
    //int voltageIndex=0;
    #ifdef USE_DIGIPOT
        BOOL digipotGet=TRUE;
    #endif
    /**************************************************************************/
    InitializeSystem();
    #ifdef USE_I2C
    if(!MasterI2CStartup())
    {
        LED1_ON;
        LED2_OFF;
        LED3_ON;
        LED4_OFF;
        LED5_ON;
        LED6_OFF;
        LED7_ON;
        LED8_OFF;
        /* TODO: consistent LED notification of an error */
        while(TRUE);
    }
    #endif
    #ifdef USE_PAC1710
    if(!PAC1710SubsystemInitialize(PAC1710_ADDRESS))
    {
        LED1_ON;
        LED2_OFF;
        LED3_ON;
        LED4_OFF;
        LED5_ON;
        LED6_OFF;
        LED7_ON;
        LED8_OFF;
        /* TODO: consistent LED notification of an error */
        while(TRUE);
    }
    #endif
    #ifdef USE_DIGIPOT
    DigipotSubsystemInitialize();
    #endif
    if(!ConfigSPIComms())
    {
        /* TODO: consistent LED notification of an error */
        while(TRUE);
    }
    TRISThisConfigure();
    
    mEnableWatchdog();

    while(TRUE)
    {
        mClearWatchdog();
        if(!DoTRISThis())
        {
            /* TODO: consistent LED notification of an error */
            while(TRUE);
        }
        #ifdef USE_PAC1710
            DoPowerMonState();
        #endif
        DoLEDs();
        #ifdef USE_DIGIPOT
        DoDigipot();
        //DigipotStartReadingAll();
        if(digipotGet)
        {
            if(DigipotStartGetStatus())
            {
                digipotGet=FALSE;
            }
        }
        else
        {
            if(DigipotReadingReady())
            {
                UINT8 reading;
                reading=DigipotGetStatus();
                Nop();
                Nop();
                Nop();
                Nop();
                Nop();
                //if(DigipotGetReading(0,&reading))
                //{
                //    Nop();
                //}
                //else
                //{
                //    Nop();
                //}
            }
        }
        #endif /* USE_DIGIPOT */
//        if(PAC1710GetData(PAC1710_DATA_CURRENT,&monitorCurrentReadings[currentIndex]))
//        {
//            currentIndex++;
//            currentIndex%=CURRENT_HISTORY_SIZE;
//        }
//        if(PAC1710GetData(PAC1710_DATA_VOLTAGE,&monitorVoltageReadings[voltageIndex]))
//        {
//            voltageIndex++;
//            voltageIndex%=VOLTAGE_HISTORY_SIZE;
//        }
//        if(GetCurrentData(PAC1710_ADDRESS,&readingHoldingSigned))
//        {
//            monitorCurrentReadings[currentIndex++]=readingHoldingSigned>>4;
//            if(currentIndex>=100)
//            {
//                currentIndex=0;
//            }
//        }
//        if(GetVoltageData(PAC1710_ADDRESS,&readingHoldingUnsigned))
//        {
//            monitorVoltageReadings[voltageIndex++]=readingHoldingUnsigned>>5;
//            if(voltageIndex>=100)
//            {
//                voltageIndex=0;
//            }
//        }
    }
}

/******************************************************************************/

void __attribute__ ((interrupt(IPL0SOFT))) _DefaultInterrupt(void)
{
    /* TODO: consistent LED notification of an error */
    while(TRUE);
}

/******************************************************************************/

void InitializeSystem(void)
{
    /**************************************************************************/
    /* Configure, enable the cache for the best performance                   */
    OSCConfig(OSC_POSC_PLL,PLL_OUTPUT_MULT,PLL_OUTPUT_DIVIDER,0);
    SYSTEMConfig(GetSystemClock(), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    mOSCSetPBDIV(PBCLK_DIV);
    /* Enable multiple interrupt vectors */
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    AD1PCFG=0xFFFF;
    P5V_POWER_GOOD_DIRECTION=TRIS_IN;
    LEDInitialize();
    TickInitialize();
    INTEnableInterrupts();
}

/******************************************************************************/