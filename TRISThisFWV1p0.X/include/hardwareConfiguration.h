/******************************************************************************/
/* File:   hardwareConfiguration.h                                            */
/* Author: Matt Bennett                                                      */
/*                                                                            */
/* Created on December 16, 2012, 4:38 PM                                      */
/******************************************************************************/

#ifndef _HARDWARE_CONFIGURATION_H_
#define	_HARDWARE_CONFIGURATION_H_

#define CRYSTAL_FREQUENCY (8000000ul)

/******************************************************************************/
/* I2C                                                                        */
/******************************************************************************/

#define I2C1_SCL_IN         PORTAbits.RA14
#define I2C1_SCL_OUT        LATAbits.LATA14
#define I2C1_SCL_DIRECTION  TRISAbits.TRISA14

#define I2C1_SDA_IN         PORTAbits.RA15
#define I2C1_SDA_OUT        LATAbits.LATA15
#define I2C1_SDA_DIRECTION  TRISAbits.TRISA15

#define I2C2_SCL_IN         PORTAbits.RA2
#define I2C2_SCL_OUT        LATAbits.LATA2
#define I2C2_SCL_DIRECTION  TRISAbits.TRISA2

#define I2C2_SDA_IN         PORTAbits.RA3
#define I2C2_SDA_OUT        LATAbits.LATA3
#define I2C2_SDA_DIRECTION  TRISAbits.TRISA3

/******************************************************************************/
/* SPI pins                                                                   */
/******************************************************************************/

#define SPI_DATA_IN             PORTCbits.RC4
#define SPI_DATA_IN_DIRECTION   TRISCbits.TRISC4

#define SPI_DATA_OUT            LATDbits.LATD0
#define SPI_DATA_OUT_DIRECTION  TRISDbits.TRISD0

#define SPI_CLOCK_IN            PORTDbits.RD10
#define SPI_CLOCK_IN_DIRECTION  TRISDbits.TRISD10

#define SPI_SELECT_IN           PORTDbits.RD9
#define SPI_SELECT_IN_OUT       LATDbits.LATD9
#define SPI_SELECT_IN_DIRECTION TRISDbits.TRISD9

#define SPI_SELECT_CN_IN        PORTBbits.RB5
#define SPI_SELECT_CN_DIRECTION TRISBbits.TRISB5

/******************************************************************************/
/* */
/******************************************************************************/

#define P5V_POWER_GOOD   PORTEbits.RE9
#define P5V_POWER_GOOD_DIRECTION   TRISEbits.TRISE9

/******************************************************************************/
/* LEDs                                                                       */
/******************************************************************************/

#define LED1_OUT        LATDbits.LATD14
#define LED1_IN         PORTDbits.RD14
#define LED1_DIRECTION  TRISDbits.TRISD14

#define LED2_OUT        LATDbits.LATD15
#define LED2_IN         PORTDbits.RD15
#define LED2_DIRECTION  TRISDbits.TRISD15

#define LED3_OUT        LATFbits.LATF4
#define LED3_IN         PORTFbits.RF4
#define LED3_DIRECTION  TRISFbits.TRISF4

#define LED4_OUT        LATFbits.LATF5
#define LED4_IN         PORTFbits.RF5
#define LED4_DIRECTION  TRISFbits.TRISF5

#define LED5_OUT        LATFbits.LATF3
#define LED5_IN         PORTFbits.RF3
#define LED5_DIRECTION  TRISFbits.TRISF3

#define LED6_OUT        LATFbits.LATF2
#define LED6_IN         PORTFbits.RF2
#define LED6_DIRECTION  TRISFbits.TRISF2

#define LED7_OUT        LATFbits.LATF8
#define LED7_IN         PORTFbits.RF8
#define LED7_DIRECTION  TRISFbits.TRISF8

// DOH! RG3 is an input only! changed on version 2.0
#define LED8_OUT        LATDbits.LATD13
#define LED8_IN         PORTDbits.RD13
#define LED8_DIRECTION  TRISDbits.TRISD13

#define ALERT_N_OUT         LATEbits.LATE8
#define ALERT_N_IN          PORTEbits.RE8
#define ALERT_N_DIRECTION   TRISEbits.TRISE8
#define LED_ON  0
#define LED_OFF 1

#define IO_IN00         PORTDbits.RD1
#define IO_OUT00        LATDbits.LATD1
#define IO_DIRECTION00  TRISDbits.TRISD1

#define IO_IN01         PORTDbits.RD2
#define IO_OUT01        LATDbits.LATD2
#define IO_DIRECTION01  TRISDbits.TRISD2

#define IO_IN02         PORTDbits.RD3
#define IO_OUT02        LATDbits.LATD3
#define IO_DIRECTION02  TRISDbits.TRISD3

#define IO_IN03         PORTDbits.RD4
#define IO_OUT03        LATDbits.LATD4
#define IO_DIRECTION03  TRISDbits.TRISD4

#define IO_IN04         PORTDbits.RD5
#define IO_OUT04        LATDbits.LATD5
#define IO_DIRECTION04  TRISDbits.TRISD5

#define IO_IN05         PORTDbits.RD6
#define IO_OUT05        LATDbits.LATD6
#define IO_DIRECTION05  TRISDbits.TRISD6

#define IO_IN06         PORTDbits.RD7
#define IO_OUT06        LATDbits.LATD7
#define IO_DIRECTION06  TRISDbits.TRISD7

#define IO_IN07         PORTDbits.RD8
#define IO_OUT07        LATDbits.LATD8
#define IO_DIRECTION07  TRISDbits.TRISD8

#define IO_IN08         PORTEbits.RE0
#define IO_OUT08        LATEbits.LATE0
#define IO_DIRECTION08  TRISEbits.TRISE0

#define IO_IN09         PORTEbits.RE1
#define IO_OUT09        LATEbits.LATE1
#define IO_DIRECTION09  TRISEbits.TRISE1

#define IO_IN10         PORTEbits.RE2
#define IO_OUT10        LATEbits.LATE2
#define IO_DIRECTION10  TRISEbits.TRISE2

#define IO_IN11         PORTEbits.RE3
#define IO_OUT11        LATEbits.LATE3
#define IO_DIRECTION11  TRISEbits.TRISE3

#define IO_IN12         PORTEbits.RE4
#define IO_OUT12        LATEbits.LATE4
#define IO_DIRECTION12  TRISEbits.TRISE4

#define IO_IN13         PORTEbits.RE5
#define IO_OUT13        LATEbits.LATE5
#define IO_DIRECTION13  TRISEbits.TRISE5

#define IO_IN14         PORTEbits.RE6
#define IO_OUT14        LATEbits.LATE6
#define IO_DIRECTION14  TRISEbits.TRISE6

#define IO_IN15         PORTEbits.RE7
#define IO_OUT15        LATEbits.LATE7
#define IO_DIRECTION15  TRISEbits.TRISE7

/******************************************************************************/
/* Pin definitions fromt the net names from the schematic. Yes, I know that   */
/* it isn't in order- the order was taken from the schematic where the refdes */
/* are grouped by port/function                                               */
/******************************************************************************/

#define PIN013  MCLR_N
#define PIN017  JTAG_TMS
#define PIN038  JTAG_TCK
#define PIN058  I2C2_SCL
#define PIN059  I2C2_SDA
#define PIN060  JTAG_TDI
#define PIN061  JTAG_TDO
#define PIN091  TRCLK
#define PIN092  TRD3
#define PIN028  NC
#define PIN029  VREF
#define PIN066  I2C1_SCL
#define PIN067  I2C1_SDA
#define PIN025  ANALOG0
#define PIN024  ANALOG1
#define PIN023  ANALOG2
#define PIN022  ANALOG3
#define PIN021  NC
#define PIN020  NC
#define PIN026  PGC
#define PIN027  PGD
#define PIN032  NC
#define PIN033  NC
#define PIN034  NC
#define PIN035  NC
#define PIN041  NC
#define PIN042  NC
#define PIN043  NC
#define PIN044  NC
#define PIN006  NC
#define PIN007  NC
#define PIN008  NC
#define PIN009  SPI_SDI /* RC4 */
#define PIN063  OSCI
#define PIN073  NC
#define PIN074  NC
#define PIN064  OSCO
#define PIN054  NC /* VBUS */
#define PIN055  NC /* VUSB */
#define PIN085  VCAP
#define PIN030  AVDD
#define PIN002  VDD
#define PIN016  VDD
#define PIN037  VDD
#define PIN046  VDD
#define PIN062  VDD
#define PIN086  VDD
#define PIN072  SPI_SDO     /* RD0 */
#define PIN076  INOUT00
#define PIN077  INOUT01
#define PIN078  INOUT02
#define PIN081  INOUT03
#define PIN082  INOUT04
#define PIN083  INOUT05
#define PIN084  INOUT06
#define PIN068  INOUT07
#define PIN069  SPI_CE      /* RD9  */
#define PIN070  SPI_SCK     /* RD10 */
#define PIN071  NC
#define PIN079  NC
#define PIN080  NC
#define PIN047  LED1_N
#define PIN048  LED2_N
#define PIN093  INOUT08
#define PIN094  INOUT09
#define PIN098  INOUT10
#define PIN099  INOUT11
#define PIN100  INOUT12
#define PIN003  INOUT13
#define PIN004  INOUT14
#define PIN005  INOUT15
#define PIN018  ALERT_N
#define PIN019  5V_POWER_GOOD
#define PIN087  NC
#define PIN088  NC
#define PIN052  LED6_N
#define PIN051  LED5_N
#define PIN049  LED3_N
#define PIN050  LED4_N
#define PIN053  LED7_N
#define PIN040  NC
#define PIN039  NC
#define PIN090  NC
#define PIN089  NC
#define PIN057  NC
#define PIN056  LED8_N
#define PIN010  NC
#define PIN011  NC
#define PIN012  NC
#define PIN014  NC
#define PIN096  TRD1
#define PIN097  TRD0
#define PIN095  TRD2
#define PIN001  NC
#define PIN031  AVSS
#define PIN015  VSS
#define PIN036  VSS
#define PIN045  VSS
#define PIN065  VSS
#define PIN075  VSS

#else
    #warning "Redundant include of hardwareConfiguration.h"
#endif	/* _HARDWARECONFIGURATION_H_ */

