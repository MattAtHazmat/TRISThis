#include <common.h>
#include <MCP4461.h>
#include <I2C_Bus_Master.h>

DIGIPOT_SUBSYSTEM_TYPE digipotStatus;
DIGIPOT_TYPE digipot;

BOOL DigipotStartGetStatus(void)
{
    if(!digipotStatus.reading&&!digipotStatus.readStatus)
    {
        digipotStatus.readStatus=TRUE;
        return TRUE;
    }
    return FALSE;
}

UINT8 DigipotGetStatus(void)
{
    return digipot.STATUS.b;
}

BOOL DigipotGetReading(UINT8 channel,UINT16 *data)
{
    if((channel<4)&&(digipot.value[channel].goodRead))
    {
        *data=digipot.value[channel].pot;
        return TRUE;
    }
    return FALSE;
}

BOOL DigipotReadingReady(void)
{
    return digipotStatus.readingReady;
}

BOOL DigipotStartReadingAll(void)
{
    if(!digipotStatus.reading&&!digipotStatus.readAll&&!digipotStatus.readIndividual)
    {
        digipotStatus.readingReady=FALSE;
        digipotStatus.readAll=TRUE;
        return TRUE;
    }
    return FALSE;
}

BOOL DigipotStartReading(UINT8 channelToRead)
{
    if(!digipotStatus.reading&&!digipotStatus.readAll&&!digipotStatus.readIndividual)
    {
        if(channelToRead<4)
        {
            digipotStatus.readingReady=FALSE;
            digipotStatus.channel=channelToRead;
            digipotStatus.readIndividual=TRUE;
            return TRUE;
        }
    }
    return FALSE;
}

BOOL DigipotSubsystemInitialize(void)
{
    int index;
    digipotStatus.w=0;
    for(index=0;index<4;index++)
    {
        digipot.value[index].word.Val=0;
    }
    for(index=0;index<5;index++)
    {
        digipot.data[index].word.Val=0;
    }
    return TRUE;
}

BOOL DoDigipot(void)
{
    /* shouldn't need to be static- just a big structure that I see no need   */
    /* to build up and take down with every pass through this function */
    static I2CBUS_COMMAND_TYPE command;
    static enum DIGIPOT_STATE_TYPE state=DIGIPOT_STATE_IDLE;

    if(!MasterI2CHasPort(DIGIPOT))
    {
        if(MasterI2CAvailable())
        {
            /* if the port is available, claim it */
            if(!MasterI2CClaimPort(DIGIPOT))
            {
                return FALSE;
            }
        }
        else
        {
            /* port not available */
            return FALSE;
        }
    }
    /* only get here if the port is claimed by the digipot subsystem */

   switch(state)
    {
        case DIGIPOT_STATE_IDLE:
        {
            if (digipotStatus.readAll) {
                digipotStatus.reading = TRUE;
                digipotStatus.channel = 0;
                state = DIGIPOT_STATE_READ;
            } else if (digipotStatus.readIndividual || digipotStatus.readStatus) {
                digipotStatus.reading = TRUE;
                state = DIGIPOT_STATE_READ;
            } else {
                /* don't be greedy */
                MasterI2CReleasePort();
            }
            break;
        }
        case DIGIPOT_STATE_READ:
        {
            if (!MasterI2CIsBusy()) {
                UINT8 digipotCommand = 0;
                if (digipotStatus.readAll || digipotStatus.readIndividual) {
                    switch (digipotStatus.channel) {
                        case 0:
                        {
                            digipotCommand = MCP4461_VOLATILE_WIPER_0;
                            break;
                        }
                        case 1:
                        {
                            digipotCommand = MCP4461_VOLATILE_WIPER_1;
                            break;
                        }
                        case 2:
                        {
                            digipotCommand = MCP4461_VOLATILE_WIPER_2;
                            break;
                        }
                        case 3:
                        {
                            digipotCommand = MCP4461_VOLATILE_WIPER_3;
                            break;
                        }
                        default:
                        {
                            digipotStatus.channel = 0;
                            break;
                        }
                    }
                    digipotCommand |= MCP4461_COMMAND_READ;
                } else if (digipotStatus.readStatus) {
                    digipotCommand = MCP4461_STATUS;
                } else {
                    /* not quite sure what is happening */
                    state = DIGIPOT_STATE_CLEANUP;
                    break;
                }
                command.status.flags.I2C_read = TRUE;
                command.target_address = DIGIPOT_ADDRESS;
                command.Word[0] = digipotCommand;
                command.WordSize = 1;
                command.DataSize = 2;
                if (MasterI2CQueueCommand(&command)) {
                    state = DIGIPOT_STATE_READ_WAIT;
                }
                command.status.all = 0; /* just in case */
            }
            break;
        }
        case DIGIPOT_STATE_READ_WAIT:
        {
            if (MasterI2CIsQueuedCommandDone()) {
                if (MasterI2CUpdateQueuedCommand(&command)) {
                    if (digipotStatus.readStatus) {
                        digipot.STATUS.b = command.Data[1];
                        digipotStatus.readingReady = TRUE;
                        state = DIGIPOT_STATE_CLEANUP;
                    } else {
                        digipot.value[digipotStatus.channel].word.byte.HB = command.Data[0];
                        digipot.value[digipotStatus.channel].word.byte.LB = command.Data[1];
                        digipot.value[digipotStatus.channel].goodRead = TRUE;
                        if (digipotStatus.readIndividual) {
                            digipotStatus.readingReady = TRUE;
                            state = DIGIPOT_STATE_CLEANUP;
                        } else if (digipotStatus.readAll) {
                            if (digipotStatus.channel == 3) {
                                digipotStatus.readingReady = TRUE;
                                state = DIGIPOT_STATE_CLEANUP;
                            } else {
                                digipotStatus.channel++;
                                state = DIGIPOT_STATE_READ;
                            }
                        }
                    }
                } else if (command.status.flags.I2C_error) {
                    digipotStatus.error = TRUE;
                    digipotStatus.errorNoACK = command.status.flags.I2C_no_slave_addr_ack;
                    digipotStatus.errorOnRead = TRUE;
                    digipotStatus.readingReady = FALSE;
                    state = DIGIPOT_STATE_CLEANUP;
                }
            }
            break;
        }
        case DIGIPOT_STATE_CLEANUP:
        {
            digipotStatus.readIndividual = FALSE;
            digipotStatus.readAll = FALSE;
            digipotStatus.readStatus = FALSE;
            MasterI2CReleasePort();
            state = DIGIPOT_STATE_IDLE;
            break;
        }
        default:
        {
            MasterI2CReleasePort();
            state = DIGIPOT_STATE_IDLE;
            break;
        }
    }
    return TRUE;
}
