/* 
 * File:   MCP4461.h
 * Author: mjb
 *
 * Created on December 31, 2012, 4:14 PM
 */

#ifndef _MCP4461_H_
#define	_MCP4461_H_
#ifdef USE_DIGIPOT
/******************************************************************************/
/******************************************************************************/

typedef union
{
    struct
    {
        unsigned error:1;
        unsigned errorNoACK:1;
        unsigned errorOnRead:1;
        unsigned errorOnWrite:1;
        unsigned readAll:1;
        unsigned readIndividual:1;
        unsigned reading:1;
        unsigned readingReady:1;
        unsigned readStatus:1;
        unsigned channel:2;
    };
    UINT16 w;
} DIGIPOT_SUBSYSTEM_TYPE;

typedef union
{
    struct
    {
        unsigned EEPROMWriteProtect:1;
        unsigned :1;
        unsigned WiperLock0:1;
        unsigned WiperLock1:1;
        unsigned EEPROMWriteActive:1;
        unsigned WiperLock2:1;
        unsigned WiperLock3:1;
        unsigned :2;
    };
    UINT8 b;
} DIGIPOT_STATUS_TYPE;

typedef union
{
    struct
    {
        unsigned R0B:1;
        unsigned R0W:1;
        unsigned R0A:1;
        unsigned R0HW:1;
        unsigned R1B:1;
        unsigned R1W:1;
        unsigned R1A:1;
        unsigned R1HW:1;
    };
    UINT8 b;
} DIGIPOT_TCON0_TYPE;

typedef union
{
    struct
    {
        unsigned R2B:1;
        unsigned R2W:1;
        unsigned R2A:1;
        unsigned R2HW:1;
        unsigned R3B:1;
        unsigned R3W:1;
        unsigned R3A:1;
        unsigned R3HW:1;
    };
    UINT8 b;
} DIGIPOT_TCON1_TYPE;

typedef union
{
    struct
    {
        unsigned pot:9;
        unsigned :5;
        unsigned goodRead:1;
        unsigned dirty:1;
    };
    //UINT16 w;
    UINT16_VAL word;
} DIGIPOT_DATA_TYPE;

typedef union
{
    struct
    {
        unsigned NVdata:10;
        unsigned :4;
        unsigned goodRead:1;
        unsigned dirty:1;
    };
    //UINT16 w;
    UINT16_VAL word;
} DIGIPOT_EEPROM_TYPE;

typedef struct
{
    DIGIPOT_DATA_TYPE value[4];
    DIGIPOT_EEPROM_TYPE data[5];
    DIGIPOT_TCON1_TYPE TCON1;
    DIGIPOT_TCON0_TYPE TCON0;
    DIGIPOT_STATUS_TYPE STATUS;
} DIGIPOT_TYPE;

enum DIGIPOT_STATE_TYPE
{
    DIGIPOT_STATE_IDLE=0,
    DIGIPOT_STATE_READ,
    DIGIPOT_STATE_READ_WAIT,
    DIGIPOT_STATE_CLEANUP
};

/******************************************************************************/
/* register addresses- already shifted to the left as the high nybble is what */
/* is used- this has to be "or-ed" with the command operation bits            */
/******************************************************************************/

#define MCP4461_VOLATILE_WIPER_0    (0x00)
#define MCP4461_VOLATILE_WIPER_1    (0x10)
#define MCP4461_NV_WIPER_0          (0x20)
#define MCP4461_NV_WIPER_1          (0x30)
#define MCP4461_VOLATILE_TCON_0     (0x40)
#define MCP4461_STATUS              (0x50)
#define MCP4461_VOLATILE_WIPER_2    (0x60)
#define MCP4461_VOLATILE_WIPER_3    (0x70)
#define MCP4461_NV_WIPER_2          (0x80)
#define MCP4461_NV_WIPER_3          (0x90)
#define MCP4461_VOLATILE_TCON_1     (0xA0)
#define MCP4461_DATA_EEPROM_1       (0xB0)
#define MCP4461_DATA_EEPROM_2       (0xC0)
#define MCP4461_DATA_EEPROM_3       (0xD0)
#define MCP4461_DATA_EEPROM_4       (0xE0)
#define MCP4461_DATA_EEPROM_5       (0xF0)

#define MCP4461_COMMAND_WRITE       (0b00000000)
#define MCP4461_COMMAND_INCREMENT   (0b00000100)
#define MCP4461_COMMAND_DECREMENT   (0b00001000)
#define MCP4461_COMMAND_READ        (0b00001100)

/******************************************************************************/
/* prototypes                                                                 */
/******************************************************************************/

BOOL DigipotStartGetStatus(void);
UINT8 DigipotGetStatus(void);
BOOL DigipotGetReading(UINT8,UINT16*);
BOOL DigipotStartReadingStatus(void);
BOOL DigipotStartReadingAll(void);
BOOL DigipotStartReading(UINT8);
BOOL DigipotReadingReady(void);
BOOL DoDigipot(void);
BOOL DigipotSubsystemInitialize(void);

/******************************************************************************/
#endif /* #ifdef USE_DIGIPOT */
#else

    #warning "Redundant define of MCP4461.h"

#endif	/* _MCP4461_H_ */

