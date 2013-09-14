/******************************************************************************/
/* File: I2C_Bus_Master.h                                                     */
/* Author: Matt Bennett                                                       */
/* Date: December 26, 2011                                                    */
/* Version: 0.9                                                               */
/*                                                                            */
/* Description:                                                               */
/*                                                                            */
/******************************************************************************/

#ifndef _I2C_BUS_MASTER_H_
#define _I2C_BUS_MASTER_H_



/******************************************************************************/
/* I2C_receive: read with no write before it                                  */
/* I2C_read:    write a command word first (which can be more than one byte)  */
/*              (from Word)                                                   */
/*      send a repeated start,                                                */
/* 	send read address,                                                    */
/*      read data into Data                                                   */
/* I2C_write:	write data from Word to the port                              */
/******************************************************************************/

/* defines used for convenience. I can never really remember these things.    */

#define	I2C_READ_BIT                0x01
#define	I2C_WRITE_BIT               0x00
#define	I2C_ACK                     0
#define	I2C_NAK                     1

#define I2C_RECOVER_TOGGLE_COUNT    16

/* I2CBRG = (PBCLK / (2 *FSCK)) - 2                                           */

#define BRG_VAL     ((GetPeripheralClock()/(2*Fsck))-2)

/******************************************************************************/
/* types that are associated with the I2C transactions                        */
/******************************************************************************/

enum MASTER_I2C_OWNER_TYPE
{
    NONE=0,
    DIGIPOT,
    POWER_MONITOR
};

enum MASTER_I2C_INTERRUPT_STATE_TYPE
{
    MI2CINT_START=0,
    MI2CINT_TX_ADDRESS_ACK,
    MI2CINT_TX_DATA_ACK,
    MI2CINT_RX_ADDRESS_ACK,
    MI2CINT_RESTART_END,
    MI2CINT_RX_DATA,
    MI2CINT_RX_DATA_ACK,
    MI2CINT_RX_DATA_NAK,
    MI2CINT_STOP
};

typedef union
{
    struct
    {
        unsigned I2C_receive:1;
        unsigned I2C_write:1;
        unsigned I2C_read:1;
        unsigned I2C_busy:1; /* indicates I2C transaction has been started but*/
                             /* is not yet complete */
        unsigned I2C_no_slave_addr_ack:1;
        unsigned I2C_no_slave_data_ack:1;
        unsigned I2C_error:1;
        unsigned I2C_FUBAR_error:1;
        unsigned I2C_error_default_state:1;
        unsigned I2C_error_overrun:1;
        unsigned I2C_action_complete:1; /* indicates I2C transaction is done */
        #ifdef I2C_USE_TIMEOUT
        unsigned I2C_timeout:1;
        #endif
    } flags;
    unsigned int all;
} I2CBus_master_I2C_status_type;

/* only exists within the scope of the master I2C C file, accessed indirectly */
typedef struct
{
    I2CBus_master_I2C_status_type status;
    UINT8 data_index;     /* pointer to where we are in the transmit/receive  */
                          /* buffers                                          */
    UINT8 target_address; /* address of what we're talking to. left justified:*/
                          /* LSB must always be '0' as this is where the read/*/
                          /* write bit is put (as appropriate)                */
    UINT8 *Word;	  /* points to arrays in I2CBUS_COMMAND_TYPE variable */
    UINT8 *Data;
    UINT8 DataSize;       /* length of what I want to receive                 */
    UINT8 WordSize;       /* length of what I want to transmit                */
    enum MASTER_I2C_INTERRUPT_STATE_TYPE state;
    __I2C2STATbits_t STATShadow;
} I2C_MASTER_PORT_TYPE;

/* used to start and retrieve data from the port                              */

typedef struct
{
    I2CBus_master_I2C_status_type status;
    UINT8 target_address;           /*                                        */
    UINT8 Word[I2CBUS_WORD_LENGTH]; /* what to send                           */
    UINT8 Data[I2CBUS_DATA_LENGTH]; /* location for data to be received       */
    UINT8 DataSize;                 /* length of what I want to receive       */
    UINT8 WordSize;                 /* length of what I want to transmit      */
} I2CBUS_COMMAND_TYPE;

/* Macros to give a consistent look/feel for I2C commands.  Also, if you need */
/* to change I2C ports, a lot of what you'll need to change is here           */

#define mMasterI2CStartStart()          I2C2CONbits.SEN=TRUE
#define mMasterI2CStartRepeatStart()    I2C2CONbits.RSEN=TRUE
#define mMasterI2CStartACKNACK()        I2C2CONbits.ACKEN=TRUE
#define mMasterI2CStopStart()           I2C2CONbits.PEN=TRUE
#define mMasterI2CReceiveEnable()       I2C2CONbits.RCEN=TRUE
#define mMasterI2CClearInterruptFlag()  IFS1bits.I2C2MIF=FALSE
#define mMasterI2CClearRBF()            temp=I2C2RCV /* dummy read to clear RBF as specified in FRM */
#define mMasterI2CDisableInterrupt()    DisableIntMI2C2
#define mMasterI2CEnableInterrupt()     EnableIntMI2C2

#ifdef I2C_USE_TIMEOUT

    /* keep all the timeout stuff in this define- if I2C_USE_TIMEOUT is not   */
    /* defined, using any of these will cause a compilation error. Keeping    */
    /* the general theory of "If it isn't used, don't include it" at least    */
    /* with respect to the code *I* write. Dead code will confuse the hell    */
    /* out of you.                                                            */

    #define mMasterI2CTimeoutClearInterruptFlag()   IFS0bits.T5IF=FALSE
    #define mMasterI2CTimeoutDisableInterrupt()     IEC0bits.T5IE=FALSE
    #define mMasterI2CTimeoutEnableInterrupt()      IEC0bits.T5IE=TRUE
    #define mMasterI2CTimeoutClearTimer()           T5CONbits.ON=FALSE;TMR5=0;T5CONbits.ON=TRUE
    #define mMasterI2CTimeoutStopTimer()            T5CONbits.ON=FALSE
    #define mMasterI2CTimeoutStartTimer()           T5CONbits.ON=TRUE

    /* calculate the best prescaler for the timeout                           */

    #if (((I2C_TIMEOUT_MS*GetPeripheralClock())/(1000*0xffff))<1)
        #define I2C_TIMEOUT_PRESCALER_VALUE 1
    #elif (((I2C_TIMEOUT_MS*GetPeripheralClock())/(4000*0xffff))<1)
        #define I2C_TIMEOUT_PRESCALER_VALUE 4
    #elif (((I2C_TIMEOUT_MS*GetPeripheralClock())/(8000*0xffff))<1)
        #define I2C_TIMEOUT_PRESCALER_VALUE 8
    #elif (((I2C_TIMEOUT_MS*GetPeripheralClock())/(16000*0xffff))<1)
        #define I2C_TIMEOUT_PRESCALER_VALUE 16
    #elif (((I2C_TIMEOUT_MS*GetPeripheralClock())/(32000*0xffff))<1)
        #define I2C_TIMEOUT_PRESCALER_VALUE 32
    #elif (((I2C_TIMEOUT_MS*GetPeripheralClock())/(64000*0xffff))<1)
        #define I2C_TIMEOUT_PRESCALER_VALUE 64
    #elif (((I2C_TIMEOUT_MS*GetPeripheralClock())/(256000*0xffff))<1)
        #define I2C_TIMEOUT_PRESCALER_VALUE 256
    #else
        #error "No valid value for I2C Timeout rescaler"
    #endif

    #define I2C_TIMEOUT_INTERVAL ((I2C_TIMEOUT_MS*GetPeripheralClock())/(1000*I2C_TIMEOUT_PRESCALER_VALUE))

    #if (I2C_TIMEOUT_INTERVAL>0xFFFF)
        #error "Can't fit I2C timeout in timer"
    #endif

    /* figure out the prescaler register setting label                        */
    #if (I2C_TIMEOUT_PRESCALER_VALUE==1)
        #define I2C_TIMEOUT_PRESCALER   T5_PS_1_1
    #elif (I2C_TIMEOUT_PRESCALER_VALUE==4)
        #define I2C_TIMEOUT_PRESCALER   T5_PS_1_4
    #elif (I2C_TIMEOUT_PRESCALER_VALUE==8)
        #define I2C_TIMEOUT_PRESCALER   T5_PS_1_8
    #elif (I2C_TIMEOUT_PRESCALER_VALUE==16)
        #define I2C_TIMEOUT_PRESCALER   T5_PS_1_16
    #elif (I2C_TIMEOUT_PRESCALER_VALUE==32)
        #define I2C_TIMEOUT_PRESCALER   T5_PS_1_32
    #elif (I2C_TIMEOUT_PRESCALER_VALUE==64)
        #define I2C_TIMEOUT_PRESCALER   T5_PS_1_64
    #elif (I2C_TIMEOUT_PRESCALER_VALUE==256)
        #define I2C_TIMEOUT_PRESCALER   T5_PS_1_256
    #else
        #error "I2C_TIMEOUT_PRESCALER_VALUE invalid"
    #endif
#endif

/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

BOOL MasterI2CStartup(void);
BOOL MasterI2CUpdateQueuedCommand(I2CBUS_COMMAND_TYPE*);
inline BOOL MasterI2CIsQueuedCommandDone(void);
BOOL MasterI2CQueueCommand(I2CBUS_COMMAND_TYPE*);
void MasterI2CRecover(void);
BOOL MasterI2CIOCheck(void);
#ifdef I2C_PARANOID_INIT
void I2CInitCommand(I2CBUS_COMMAND_TYPE*);
#endif
inline BOOL MasterI2CIsBusy(void);
//BOOL  MasterI2CWriteVerifyByte(UINT8, UINT8, UINT8, UINT8);
BOOL  MasterI2CWriteVerifyByteNoRetry(UINT8, UINT8, UINT8);
BOOL MasterI2CReadByte(UINT8, UINT8, UINT8 *);
BOOL MasterI2CReadGPIO(UINT16*);
BOOL  MasterI2CWriteVerifyWordNoRetry(UINT8, UINT8, UINT16);

BOOL MasterI2CClaimPort(enum MASTER_I2C_OWNER_TYPE);
void MasterI2CReleasePort(void);
BOOL MasterI2CAvailable(void);
BOOL MasterI2CHasPort(enum MASTER_I2C_OWNER_TYPE);



#endif
