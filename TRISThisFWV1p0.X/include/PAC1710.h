/* 
 * File:   PAC1710.h
 * Author: mjb
 *
 * Created on December 27, 2012, 3:25 PM
 */

#ifndef _PAC1710_H_
#define	_PAC1710_H_
#ifdef USE_PAC1710
/* addresses from p 23-24 of PAC1710 datasheet */

#define PAC1710_REG_CONFIGURATION               0x00
#define PAC1710_REG_CONV_RATE                   0x01
#define PAC1710_REG_ONE_SHOT                    0x02
#define PAC1710_REG_CHANNEL_MASK                0x03
#define PAC1710_REG_HIGH_LIMIT_STATUS           0x04
#define PAC1710_REG_LOW_LIMIT_STATUS            0x05
#define PAC1710_REG_VSOURCE_CONFIG              0x0A
#define PAC1710_REG_VSENSE_CONFIG               0x0B
#define PAC1710_REG_SENSE_VOLTAGE_HIGH          0x0D
#define PAC1710_REG_SENSE_VOLTAGE_LOW           0x0E
#define PAC1710_REG_VSOURCE_VOLTAGE_HIGH        0x11
#define PAC1710_REG_VSOURCE_VOLTAGE_LOW         0x12
#define PAC1710_REG_POWER_RATIO_HIGH            0x15
#define PAC1710_REG_POWER_RATIO_LOW             0x16
#define PAC1710_REG_SENSE_VOLTAGE_HIGH_LIMIT    0x19
#define PAC1710_REG_SENSE_VOLTAGE_LOW_LIMIT     0x1B
#define PAC1710_REG_VSOURCE_VOLTAGE_HIGH_LIMIT  0x1D
#define PAC1710_REG_VSOURCE_VOLTAGE_LOW_LIMIT   0x1F
#define PAC1710_REG_PRODUCT_ID                  0xFD
#define PAC1710_REG_SMSC_ID                     0xFE
#define PAC1710_REG_REVISION                    0xFF

#define PAC1710_PRODUCT_ID                      0x58
#define PAC1710_SMSC_ID                         0x5D
#define PAC1710_REVISION                        0x81

#define CS_SAMP_DISABLED 0
#define CS_SAMP_2       0b01
#define CS_SAMP_4       0b10
#define CS_SAMP_8       0b11

#define CS_RANGE_10MV   (0)
#define CS_RANGE_20MV   (0b01)
#define CS_RANGE_40MV   (0b10)
#define CS_RANGE_80MV   (0b11)

#define CS_SAMPLE_TIME_2P5_MS  (0)
#define CS_SAMPLE_TIME_5_MS  (0b001)
#define CS_SAMPLE_TIME_10_MS  (0b010)
#define CS_SAMPLE_TIME_20_MS  (0b011)
#define CS_SAMPLE_TIME_40_MS  (0b100)
#define CS_SAMPLE_TIME_80_MS  (0b101)
#define CS_SAMPLE_TIME_160_MS  (0b110)
#define CS_SAMPLE_TIME_320_MS  (0b111)

#define VSRC_SAMPLE_TIME_2P5_MS (0b00)
#define VSRC_SAMPLE_TIME_5_MS   (0b01)
#define VSRC_SAMPLE_TIME_10_MS  (0b10)
#define VSRC_SAMPLE_TIME_20_MS  (0b11)

#define VSRC_AVERAGE_DISABLED   (0b00)
#define VSRC_AVERAGE_2   (0b01)
#define VSRC_AVERAGE_4   (0b10)
#define VSRC_AVERAGE_8   (0b11)

typedef union
{
    struct
    {
        unsigned CS_RNG:2;
        unsigned CS_SAMP_AVG:2;
        unsigned CS_SAMP_TIME:3;
        unsigned :1;
    };
    uint8_t b;
} PAC1710_VSENSE_REG_TYPE;

typedef union
{
    struct
    {
        unsigned PAC1710Present:1;
        unsigned PAC1710Address:7;
        //unsigned PAC17102Present:1;
        //unsigned PAC17102Address:7;
    };
    UINT16 word;
}PAC1710_Subsystem_TYPE;

typedef union
{
    struct
    {
        unsigned VSRC_SAMP_TIME:2;
        unsigned VSRC_AVG:2;
        unsigned :4;
    };
    uint8_t b;
} PAC1710_VSOURCE_SAMPLING_CONFIG_REG_TYPE;

typedef union
{
    struct
    {
        unsigned VMEAS_DIS:1;
        unsigned IMEAS_DIS:1;
        unsigned TIMEOUT:1;
        unsigned :2;
        unsigned MASK_ALL:1;
        unsigned CONV_DONE_EN:1;
        unsigned :1;
    };
    uint8_t b;
} PAC1710_CONFIGURATION_REG_TYPE;

typedef union
{
    struct
    {
        unsigned VSRC_HIGH:1;
        unsigned VSENSE_HIGH:1;
        unsigned :5;
        unsigned CONV_DONE:1;
    };
    uint8_t b;
} PAC1710_HIGH_LIMIT_STATUS_REG_TYPE;

typedef union
{
    struct
    {
        unsigned alertAsserted:1;
        unsigned monitorConfigured:1;
        unsigned monitorCurrentAvailable:1;
        unsigned monitorVoltageAvailable:1;
        //unsigned monitor2Configured:1;
        //unsigned monitor2CurrentAvailable:1;
        //unsigned monitor2VoltageAvailable:1;
        unsigned subsystemConfigured:1;
        unsigned newDataAvailable:1;
        unsigned unknownAlert;
    };
    UINT32 w;
} PAC1710_STATUS_FLAGS_TYPE;

//enum CS_SAMP_AVG_TYPE
//{
//    CS_SAMP_DISABLED=0,
//    CS_SAMP_2=0b01,
//    CS_SAMP_4=0b10,
//    CS_SAMP_8=0b11
//};

enum PAC1710_DATA_TYPE
{
    PAC1710_DATA_CURRENT=0,
    PAC1710_DATA_VOLTAGE
};

enum POWER_MONITOR_STATE_TYPE
{
    PM_STATE_IDLE=0,
    PM_STATE_CHECK_MONITOR,
    PM_STATE_CHECK_MONITOR_WAIT,
    PM_STATE_READ_MONITOR_VOLTAGE,
    PM_STATE_READ_MONITOR_VOLTAGE_WAIT,
    PM_STATE_READ_MONITOR_CURRENT,
    PM_STATE_READ_MONITOR_CURRENT_WAIT,
    PM_STATE_MONITOR_WRAP_UP,
    PM_STATE_ALERT_WRAP_UP
};

/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

BOOL PAC1710Present(UINT32);
BOOL PAC1710Configure(UINT32);
BOOL IsAlertAsserted(void);
void ClearAlertAsserted(void);
BOOL DoPowerMonState(void);
void PAC1710AlertConfigure(void);
BOOL PAC1710SubsystemInitialize(UINT32);
BOOL GetCurrentData(UINT32, INT16*);
BOOL GetVoltageData(UINT32, INT16*);
BOOL PAC1710GetData(enum PAC1710_DATA_TYPE, INT16 *);
#endif /* #ifdef USE_PAC1710 */
#else
    #warning "Redundant include of PAC1710.h"

#endif	/* PAC1710_H */

