/******************************************************************************/
/* File: I2C_Bus_Master.c                                                     */
/* Author: Matt Bennett                                                       */
/* Date: December 26, 2011                                                    */
/* Version: 0.95                                                              */
/*                                                                            */
/* Description: Interrupt driven code for an I2C master. State based.         */
/*  Queue a command, wait for it to be complete, copy the data from the       */
/*  interrupt accessible variables.                                           */
/*                                                                            */
/******************************************************************************/

#include <common.h>
#ifdef USE_I2C
#include <delay.h>
#include <I2C_Bus_Master.h>

/******************************************************************************/

I2C_MASTER_PORT_TYPE MasterI2CPort;

/* just here for being able to see this in a watch window                     */
//extern I2CBUS_COMMAND_TYPE I2CCommand;

/******************************************************************************/

#ifdef I2C_USE_TIMEOUT
/******************************************************************************/
/* Timeout interrupt                                                          */
/******************************************************************************/

void __ISR(/*INT_TIMER_VECTOR(I2C_TIMEOUT_TIMER)*/_TIMER_5_VECTOR,TIMEOUT_INT_PRIORITY_ISR) I2CTimeoutInterrupt(void)
{
    INTClearFlag(INT_SOURCE_TIMER(I2C_TIMEOUT_TIMER));
    MasterI2CPort.status.flags.I2C_timeout=TRUE;
    MasterI2CPort.status.flags.I2C_error=TRUE;
    MasterI2CPort.status.flags.I2C_action_complete=TRUE;
    MasterI2CPort.status.flags.I2C_busy=FALSE;
    mMasterI2CTimeoutStopTimer();
    INTEnable(INT_SOURCE_I2C_MASTER(I2C_PORT),INT_DISABLED);
}
#endif

/******************************************************************************/
/* I2C Master interrupt                                                       */
/******************************************************************************/

void __ISR (_I2C_2_VECTOR,MI2C_INT_PRIORITY_ISR) _MI2C2Interrupt(void)
{
    static uint8_t temp; /* used by dummy read to clear RBF flag */
    INTClearFlag(INT_SOURCE_I2C_MASTER(I2C_PORT));
    /* save a copy of I2C2STAT */
    MasterI2CPort.STATShadow.w=I2C_STATUS;
    #ifdef I2C_USE_TIMEOUT
        mMasterI2CTimeoutClearTimer();
        /* if we get an I2C interrupt, there wasn't a timeout*/
        INTClearFlag(INT_SOURCE_TIMER(I2C_TIMEOUT_TIMER));
    #endif /* #ifdef I2C_USE_TIMEOUT */
    if((MasterI2CPort.STATShadow.I2COV==TRUE) ||
       (MasterI2CPort.STATShadow.IWCOL==TRUE))
    {
        MasterI2CPort.status.flags.I2C_error = TRUE;
        MasterI2CPort.status.flags.I2C_error_overrun = TRUE;
        /* the STOP state does all the shutdown we need                       */
        MasterI2CPort.state = MI2CINT_STOP;
    }
    switch(MasterI2CPort.state)
    {
        case MI2CINT_START:
        {
            /* send the address ... which one?                                */
            if (MasterI2CPort.status.flags.I2C_receive)
            {
                /* send read address                                          */
                I2C2TRN = MasterI2CPort.target_address | I2C_READ_BIT;
                MasterI2CPort.state = MI2CINT_RX_ADDRESS_ACK;
            } 
            else
            {
                /* send write address                                         */
                I2C2TRN = MasterI2CPort.target_address | I2C_WRITE_BIT;
                MasterI2CPort.state = MI2CINT_TX_ADDRESS_ACK;
            }
            break;
        }
        case MI2CINT_TX_ADDRESS_ACK:
        {
            if (MasterI2CPort.STATShadow.ACKSTAT == I2C_NAK)
            {
                /* if NAK, nobody acknowledged                                */
                MasterI2CPort.status.flags.I2C_error = TRUE;
                MasterI2CPort.status.flags.I2C_no_slave_addr_ack = TRUE;
                I2CStop(I2C_PORT);
                MasterI2CPort.state = MI2CINT_STOP;
            } 
            else
            {
                /* there was an acknowledge, send the first byte              */
                I2C2TRN = MasterI2CPort.Word[0];
                /* point to the next piece of data to send                    */
                MasterI2CPort.data_index = 1;
                MasterI2CPort.state = MI2CINT_TX_DATA_ACK;
            }
            break;
        }
        case MI2CINT_TX_DATA_ACK:
        {
            if (MasterI2CPort.STATShadow.ACKSTAT == I2C_NAK)
            {
                /* if NAK, nobody acknowledged                                */
                MasterI2CPort.status.flags.I2C_error = TRUE;
                MasterI2CPort.status.flags.I2C_no_slave_data_ack = TRUE;
                I2CStop(I2C_PORT);
                //mMasterI2CStopStart(); /* Send the Stop condition            */
                MasterI2CPort.state = MI2CINT_STOP;
            } 
            else /* there was an ACK                                          */
            {
                /* have I written all the data?                               */
                if (MasterI2CPort.data_index >= MasterI2CPort.WordSize)
                {
                    /* done with what we're going to write                    */
                    if (MasterI2CPort.status.flags.I2C_read)
                    {
                        mMasterI2CClearRBF();
                        I2CRepeatStart(I2C_PORT);
                        MasterI2CPort.state = MI2CINT_RESTART_END;
                    } 
                    else
                    {
                        /* must be a write, and we're done                    */
                        I2CStop(I2C_PORT);
                        MasterI2CPort.state = MI2CINT_STOP;
                    }
                } 
                else
                {
                    /* bounds check so we don't overrun the .Word array       */
                    if (MasterI2CPort.data_index < I2CBUS_WORD_LENGTH)
                    {
                        I2C2TRN = MasterI2CPort.Word[MasterI2CPort.data_index];
                        /* point at next bit of data to send                  */
                        MasterI2CPort.data_index++;
                        /* and stay in this state                             */
                    } 
                    else
                    {
                        /* something is making us overrun the .Word array     */
                        MasterI2CPort.status.flags.I2C_error = TRUE;
                        MasterI2CPort.status.flags.I2C_FUBAR_error = TRUE;
                        I2CStop(I2C_PORT);
                        MasterI2CPort.state = MI2CINT_STOP;
                    }
                }
            }
            break;
        }
        case MI2CINT_RESTART_END:
        {
            /* send read address                                              */
            I2C2TRN = MasterI2CPort.target_address | I2C_READ_BIT;
            MasterI2CPort.state = MI2CINT_RX_ADDRESS_ACK;
            break;
        }
        case MI2CINT_RX_ADDRESS_ACK:
        {
            if (MasterI2CPort.STATShadow.ACKSTAT == I2C_NAK)
            {
                /* if NAK, nobody acknowledged                                */
                MasterI2CPort.status.flags.I2C_error = TRUE;
                MasterI2CPort.status.flags.I2C_no_slave_addr_ack = TRUE;
                /* Send the Stop condition                                    */
                I2CStop(I2C_PORT);
                MasterI2CPort.state = MI2CINT_STOP;
            } 
            else
            {
                MasterI2CPort.data_index = 0;
                mMasterI2CClearRBF();
                I2CReceiverEnable(I2C_PORT,TRUE);
                MasterI2CPort.state = MI2CINT_RX_DATA;
            }
            break;
        }
        case MI2CINT_RX_DATA:
        {
            /* Bounds check data_index for safe access of .Data[]             */
            if (MasterI2CPort.data_index < I2CBUS_DATA_LENGTH)
            {
                MasterI2CPort.Data[MasterI2CPort.data_index++] = I2C2RCV;
                if (MasterI2CPort.data_index == MasterI2CPort.DataSize) 
                {
                    I2CAcknowledgeByte(I2C_PORT,FALSE);
                    MasterI2CPort.state = MI2CINT_RX_DATA_NAK;
                } 
                else
                {
                    /* send ACK to signify there will be more                 */
                    I2CAcknowledgeByte(I2C_PORT,TRUE);
                    MasterI2CPort.state = MI2CINT_RX_DATA_ACK;
                }
            } 
            else
            {
                MasterI2CPort.state = MI2CINT_RX_DATA_NAK;
                MasterI2CPort.status.flags.I2C_error = TRUE;
                MasterI2CPort.status.flags.I2C_FUBAR_error = TRUE;
                I2CAcknowledgeByte(I2C_PORT,FALSE);
            }
            break;
        }
        case MI2CINT_RX_DATA_ACK:
        {
            /* still have more to recieve- start another RX cycle             */
            I2CReceiverEnable(I2C_PORT,TRUE);
            MasterI2CPort.state = MI2CINT_RX_DATA;
            break;
        }
        case MI2CINT_RX_DATA_NAK:
        {
            /* No more to send, or an error case- send the Stop condition     */
            I2CStop(I2C_PORT);
            MasterI2CPort.state = MI2CINT_STOP;
            break;
        }
        case MI2CINT_STOP:
        {
            MasterI2CPort.status.flags.I2C_action_complete = TRUE;
            MasterI2CPort.status.flags.I2C_busy = FALSE;
            INTEnable(INT_SOURCE_I2C_MASTER(I2C_PORT),INT_DISABLED);
            #ifdef I2C_USE_TIMEOUT
                mMasterI2CTimeoutStopTimer();
                INTEnable(INT_SOURCE_TIMER(I2C_TIMEOUT_TIMER),INT_DISABLED);
                INTClearFlag(INT_SOURCE_TIMER(I2C_TIMEOUT_TIMER));
            #endif
            /* prepare the state machine for next round                       */
            MasterI2CPort.state = MI2CINT_START;
            break;
        }
        default:
        {
            mMasterI2CClearRBF();
            /* Start a 'STOP' cycle                                           */
            I2CStop(I2C_PORT);
            MasterI2CPort.status.flags.I2C_error = TRUE;
            /* set a flag for debugging                                       */
            MasterI2CPort.status.flags.I2C_error_default_state = TRUE;
            MasterI2CPort.state = MI2CINT_STOP;
            break;
        }
    }
}

/******************************************************************************/
/* BOOL MasterI2CQueueCommand(I2CBUS_COMMAND_TYPE *command)                   */
/* kicks off an I2C transaction as specified by the *command structure        */
/******************************************************************************/

BOOL MasterI2CQueueCommand(I2CBUS_COMMAND_TYPE *command)
{
    if(!MasterI2CPort.status.flags.I2C_busy)
    {
        /* this port is not already doing something                           */
        /* just in case, disable interrupts                                   */
        INTEnable(INT_SOURCE_I2C_MASTER(I2C_PORT),INT_DISABLED);
        #ifdef I2C_USE_TIMEOUT
            mMasterI2CTimeoutStopTimer();
            INTEnable(INT_SOURCE_TIMER(I2C_TIMEOUT_TIMER),INT_DISABLED);
        #endif
        /* clear out the status                                               */
        MasterI2CPort.status.all = 0;
        /* copy the relevant portions to the port's status register           */
        MasterI2CPort.status.flags.I2C_action_complete = FALSE;
        MasterI2CPort.status.flags.I2C_busy = TRUE;
        MasterI2CPort.status.flags.I2C_receive = command->status.flags.I2C_receive;
        MasterI2CPort.status.flags.I2C_write = command->status.flags.I2C_write;
        MasterI2CPort.status.flags.I2C_read = command->status.flags.I2C_read;
        MasterI2CPort.target_address = command->target_address;
        MasterI2CPort.DataSize = command->DataSize;
        MasterI2CPort.WordSize = command->WordSize;
        MasterI2CPort.Word = command->Word; /* just make these pointers to the  */
        MasterI2CPort.Data = command->Data; /* data in the structure that was   */
        /* sent here                        */
        MasterI2CPort.data_index = 0;
        #ifdef I2C_USE_TIMEOUT
            mMasterI2CTimeoutClearTimer();
            mMasterI2CTimeoutStartTimer();
            INTClearFlag(INT_SOURCE_TIMER(I2C_TIMEOUT_TIMER));
            //mMasterI2CTimeoutClearInterruptFlag();
            //mMasterI2CTimeoutEnableInterrupt();
            INTEnable(INT_SOURCE_TIMER(I2C_TIMEOUT_TIMER),INT_ENABLED);
        #endif

        INTClearFlag(INT_SOURCE_I2C_MASTER(I2C_PORT));
        INTEnable(INT_SOURCE_I2C_MASTER(I2C_PORT),INT_ENABLED);
        if (I2CBusIsIdle(I2C_PORT))
        {
            I2CStart(I2C_PORT);
            return SUCCESS;
        }
    }
    return FAIL;
}

/******************************************************************************/
/* BOOL MasterI2CUpdateQueuedCommand(I2CBUS_COMMAND_TYPE *command)            */
/* if the I2C transaction is complete, copies the status and the size of the  */
/* data read into the *command structure. The *command structure was already  */
/* where the interrupt had written the data to.                               */
/******************************************************************************/

BOOL MasterI2CUpdateQueuedCommand(I2CBUS_COMMAND_TYPE *command)
{
    BOOL returnValue=FAIL;
    if(MasterI2CPort.status.flags.I2C_action_complete)
    {
        /* just in case */
        #ifdef I2C_USE_TIMEOUT
        mMasterI2CTimeoutStopTimer();
        #endif
        command->status=MasterI2CPort.status;
        command->DataSize=MasterI2CPort.data_index;
        returnValue= !MasterI2CPort.status.flags.I2C_error;
        
    }
//    else
//    {
//            /* this port has not gone through a full I2C transaction cycle */
//    }
    return returnValue;
}

#ifdef I2C_PARANOID_INIT
/******************************************************************************/
/* void I2CInitCommand(I2CBUS_COMMAND_TYPE *command)                          */
/* initializes and clears out the I2C command structure passed by *command    */
/* could be simplified, but is useful to clear out the structure in the       */
/* development process to be absolutely sure of what data is being written    */
/* into the structure by the I2C engine                                       */
/******************************************************************************/

void I2CInitCommand(I2CBUS_COMMAND_TYPE *command)
{
    int index;
    command->status.all=0;
    for(index=0;index<I2CBUS_WORD_LENGTH;index++)
    {
        command->Word[index]=0;
    }
    for(index=0;index<I2CBUS_DATA_LENGTH;index++)
    {
        command->Data[index]=0;
    }
    command->DataSize=0;
    command->WordSize=0;
    command->target_address=0;
}
#endif
/******************************************************************************/
/* BOOL MasterI2CStartup(BOOL repairIO)                                       */
/* configures I2C port and timeout timer. if repairIO is TRUE, check to see   */
/* if the I2C pins are high- if they are not, attempt to fix it. Returns      */
/* FALSE if there was a recovery attempt that was unsuccessful                */
/******************************************************************************/

BOOL MasterI2CStartup(void)
{
    I2CEnable(I2C_PORT,FALSE);
    //I2C2CONbits.ON=FALSE;
    INTEnable(INT_SOURCE_I2C_MASTER(I2C_PORT),INT_DISABLED);
    if(!MasterI2CIOCheck())
    {
        return FALSE;
    }
    MasterI2CPort.status.all=0;
    #ifdef I2C_USE_TIMEOUT
    OpenTimer5(
        T5_OFF|
        T5_IDLE_CON|
        T5_GATE_OFF|
        I2C_TIMEOUT_PRESCALER|
        T5_SOURCE_INT,
        I2C_TIMEOUT_INTERVAL);
    INTClearFlag(INT_SOURCE_TIMER(I2C_TIMEOUT_TIMER));
    INTSetVectorPriority(INT_VECTOR_TIMER(I2C_TIMEOUT_TIMER),I2C_TIMEOUT_TIMER_INT_PRIORITY);
    INTSetVectorSubPriority(INT_VECTOR_I2C(I2C_TIMEOUT_TIMER),I2C_TIMEOUT_TIMER_INT_SUB_PRIORITY);
    INTEnable(INT_SOURCE_TIMER(I2C_TIMEOUT_TIMER),INT_DISABLED);
    //SetPriorityIntT5(T5_INT_OFF|TIMEOUT_INT_PRIORITY|T5_INT_SUB_PRIOR_1);
    #endif
    MasterI2CPort.state=MI2CINT_START;
    //I2C2CON=0; /* clear to a known state */
    //DelayMs(10);
    //I2C2BRG=BRG_VAL;
    //I2C2STAT=0;
    //I2C2CONbits.SIDL=TRUE;   /* stop when in idle mode */
    //I2C2CONbits.SCLREL=TRUE; /* SCL release (doesn't really matter as master) */
    //I2C2CONbits.STRICT=FALSE;/* do not strictly interpret I2C addresses*/
    //I2C2CONbits.A10M=FALSE;  /* use 7 bit addressing */
    //I2C2CONbits.DISSLW=TRUE; /* disable slew rate control */
    //I2C2CONbits.SMEN=FALSE;  /* do not use SMBUS levels */
    I2CConfigure(I2C_PORT,0);
    I2CSetFrequency(I2C_PORT, GetPeripheralClock(), Fsck);
    I2CEnable(I2C_PORT, TRUE);
    //I2C2CONbits.ON=TRUE;     /* turn I2C module on */
    INTClearFlag(INT_SOURCE_I2C_MASTER(I2C_PORT));
    INTSetVectorPriority(INT_VECTOR_I2C(I2C_PORT),MI2C_INT_PRIORITY);
    INTSetVectorSubPriority(INT_VECTOR_I2C(I2C_PORT),MI2C_INT_SUB_PRIORITY);
    //SetPriorityIntI2C2(I2C_INT_OFF|MI2C_INT_PRIORITY|I2C_INT_SUB_PRI_1);
    return TRUE;
}

/******************************************************************************/
/* MasterI2CIOCheck()                                                         */
/******************************************************************************/

BOOL MasterI2CIOCheck(void)
{
    BOOL returnValue=FALSE;
    /* make sure I2C port is off */
    I2CEnable(I2C_PORT,FALSE);
    //I2C2CONbits.ON=FALSE;
    I2C2_SCL_DIRECTION=TRIS_IN;
    I2C2_SDA_DIRECTION=TRIS_IN;
    /* wait a little while */
    DelayMs(10);
    returnValue=((I2C2_SCL_IN==1)&&(I2C2_SDA_IN==1));
    return returnValue;
}

/******************************************************************************/
/* accessor function for I2C_busy                                             */
/*   attempting to be interrupt safe                                          */
/******************************************************************************/

inline BOOL MasterI2CIsBusy(void)
{
    BOOL returnValue;
    if(INTGetEnable(INT_SOURCE_I2C_MASTER(I2C_PORT)))
    {
        INTEnable(INT_SOURCE_I2C_MASTER(I2C_PORT),INT_DISABLED);
        returnValue=MasterI2CPort.status.flags.I2C_busy;
        INTEnable(INT_SOURCE_I2C_MASTER(I2C_PORT),INT_ENABLED);
    }
    else
    {
        returnValue=MasterI2CPort.status.flags.I2C_busy;
    }
    return returnValue;
}

/******************************************************************************/
/* accessor function for I2C_action_complete                                  */
/******************************************************************************/

inline BOOL MasterI2CIsQueuedCommandDone(void)
{
    BOOL returnValue;
    if(INTGetEnable(INT_SOURCE_I2C_MASTER(I2C_PORT)))
    {
        INTEnable(INT_SOURCE_I2C_MASTER(I2C_PORT),INT_DISABLED);
        returnValue=MasterI2CPort.status.flags.I2C_action_complete;
        INTEnable(INT_SOURCE_I2C_MASTER(I2C_PORT),INT_ENABLED);
    }
    else
    {
        returnValue = MasterI2CPort.status.flags.I2C_action_complete;
    }
    return returnValue;
}

BOOL MasterI2CReadByte(uint8_t address, uint8_t toReadRegister, uint8_t *dataRead)
{
    I2CBUS_COMMAND_TYPE RI2CCommand;
    #ifdef I2C_PARANOID_INIT
        I2CInitCommand(&RI2CCommand);
    #else
        RI2CCommand.status.all=0;
    #endif
    RI2CCommand.status.flags.I2C_read=TRUE;
    RI2CCommand.target_address=address;
    RI2CCommand.Word[0]=toReadRegister;
    RI2CCommand.WordSize=1;
    RI2CCommand.DataSize=1;
    if(MasterI2CQueueCommand(&RI2CCommand))
    {
        while (MasterI2CIsBusy());
        if (MasterI2CUpdateQueuedCommand(&RI2CCommand))
        {
            /* was there an error? */
            if (!RI2CCommand.status.flags.I2C_error)
            {
                *dataRead = RI2CCommand.Data[0];
                return TRUE;
            }
        }
    }
    return FALSE;
}

BOOL MasterI2CReadWord(uint8_t address, uint8_t toReadRegister, UINT16 *dataRead)
{
    I2CBUS_COMMAND_TYPE RI2CCommand;
    UINT16_VAL tempDataRead;
    #ifdef I2C_PARANOID_INIT
        I2CInitCommand(&RI2CCommand);
    #else
        RI2CCommand.status.all=0;
    #endif
    RI2CCommand.status.flags.I2C_read=TRUE;
    RI2CCommand.target_address=address;
    RI2CCommand.Word[0]=toReadRegister;
    RI2CCommand.WordSize=1;
    RI2CCommand.DataSize=2;
    if(MasterI2CQueueCommand(&RI2CCommand))
    {
        while(MasterI2CIsBusy());
        if(MasterI2CUpdateQueuedCommand(&RI2CCommand))
        {
            /* was there an error? */
            if(!RI2CCommand.status.flags.I2C_error)
            {
                tempDataRead.byte.LB=RI2CCommand.Data[0];
                tempDataRead.byte.HB=RI2CCommand.Data[1];
                *dataRead=tempDataRead.Val;
                return TRUE;
            }
        }
    }
    return FALSE;
}

BOOL  MasterI2CWriteVerifyByteNoRetry(uint8_t address, uint8_t toWriteRegister, uint8_t toWriteData)
{
    I2CBUS_COMMAND_TYPE WVI2CCommand;
    uint8_t dataRead;
    #ifdef I2C_PARANOID_INIT
        I2CInitCommand(&WVI2CCommand);
    #else
        WVI2CCommand.status.all=0;
    #endif
    WVI2CCommand.status.flags.I2C_write=TRUE;
    WVI2CCommand.target_address=address;
    WVI2CCommand.Word[0]=toWriteRegister;
    WVI2CCommand.Word[1]=toWriteData;
    WVI2CCommand.WordSize=2;
    if(MasterI2CQueueCommand(&WVI2CCommand))
    {
        /* wait for the transaction to be done */
        while(MasterI2CIsBusy());
        if(MasterI2CUpdateQueuedCommand(&WVI2CCommand))
        {
            /* was there an error? */
            if(!WVI2CCommand.status.flags.I2C_error)
            {
                /* no error, now verify */
                if(MasterI2CReadByte(address,toWriteRegister,&dataRead))
                {
                    if(dataRead==toWriteData)
                    {
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
}

BOOL  MasterI2CWriteVerifyWordNoRetry(uint8_t address, uint8_t toWriteRegister, UINT16 toWriteData)
{
    I2CBUS_COMMAND_TYPE WVI2CCommand;
    UINT16_VAL tempWord;
    tempWord.Val=toWriteData;
    #ifdef I2C_PARANOID_INIT
        I2CInitCommand(&WVI2CCommand);
    #else
        WVI2CCommand.status.all=0;
    #endif
    WVI2CCommand.status.flags.I2C_write=TRUE;
    WVI2CCommand.target_address=address;
    WVI2CCommand.Word[0]=toWriteRegister;
    WVI2CCommand.Word[1]=tempWord.byte.LB;
    WVI2CCommand.Word[2]=tempWord.byte.HB;
    WVI2CCommand.WordSize=3;
    if(MasterI2CQueueCommand(&WVI2CCommand))
    {
        /* wait for the transaction to be done */
        while(MasterI2CIsBusy());
        if(MasterI2CUpdateQueuedCommand(&WVI2CCommand))
        {
            /* was there an error? */
            if(!WVI2CCommand.status.flags.I2C_error)
            {
                /* no error, now verify */
                if(MasterI2CReadWord(address,toWriteRegister,&tempWord.Val))
                {
                    if(tempWord.Val==toWriteData)
                    {
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
}

enum MASTER_I2C_OWNER_TYPE currentOwner=NONE;

BOOL MasterI2CClaimPort(enum MASTER_I2C_OWNER_TYPE owner)
{
    BOOL returnValue=FALSE;
    if(currentOwner==NONE)
    {
        switch(owner)
        {
            case DIGIPOT:
            case POWER_MONITOR:
            {
                currentOwner = owner;
                returnValue = TRUE;
                break;
            }
            case NONE:
            default:
            {
                returnValue = TRUE;
                break;
            }
        }
    }
    return returnValue;
}

void MasterI2CReleasePort(void)
{
    /* maybe check to see if the Master I2C is busy? */
    currentOwner=NONE;
}

BOOL MasterI2CAvailable(void)
{
    BOOL returnValue=FALSE;
    if(currentOwner==NONE)
    {
        returnValue=TRUE;
    }
    return returnValue;
}

BOOL MasterI2CHasPort(enum MASTER_I2C_OWNER_TYPE owner)
{
    if(owner==currentOwner)
    {
        return TRUE;
    }
    return FALSE;
}
#endif /* #ifdef USE_I2C */