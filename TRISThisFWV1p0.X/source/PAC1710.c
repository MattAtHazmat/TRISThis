/******************************************************************************/
/* File:   PAC1710.c                                                          */
/* Author: Matt Bennett                                                       */
/*                                                                            */
/* Created on                                                                 */
/* Updated August 2013                                                        */
/******************************************************************************/
/* code to talk to the PAC1710 power/voltage/current monitor                  */
/******************************************************************************/

#include <common.h>
#include <PAC1710.h>
#include <I2C_Bus_Master.h>

BOOL INTalertAsserted;
PAC1710_STATUS_FLAGS_TYPE PAC1710SubsystemFlags;

PAC1710_Subsystem_TYPE PAC1710subsystem;

UINT16_VAL monitorCurrentHolding;
UINT16_VAL monitorVoltageHolding;

/******************************************************************************/
/* PAC1710SubsystemInitialize(UINT8 address)                                  */

BOOL PAC1710SubsystemInitialize(UINT8 address)
{
    if(MasterI2CAvailable()&&MasterI2CClaimPort(POWER_MONITOR))
    {
        PAC1710SubsystemFlags.w=0;
        if(PAC1710Present(address))
        {
            if(PAC1710Configure(address))
            {
                PAC1710SubsystemFlags.monitorConfigured=TRUE;
                /* Yay! */
            }
        }
        else
        {
            //while(TRUE);
        }
        PAC1710AlertConfigure();
        /* is at least one configured? */
        PAC1710SubsystemFlags.subsystemConfigured=
                PAC1710SubsystemFlags.monitorConfigured;
        MasterI2CReleasePort();
        return PAC1710SubsystemFlags.subsystemConfigured;
    }
}

/******************************************************************************/

BOOL PAC1710Present(UINT8 address)
{
    UINT8 productID=0;
    UINT8 SMSCID=0;
    UINT8 revision=0;
    BOOL productIDGoodRead=FALSE;
    BOOL SMSCIDGoodRead=FALSE;
    BOOL revisionGoodRead=FALSE;
    BOOL returnValue=FALSE;
    if(MasterI2CAvailable()&&MasterI2CClaimPort(POWER_MONITOR))
    {
        if(MasterI2CReadByte(address,PAC1710_REG_PRODUCT_ID,&productID))
        {
            productIDGoodRead=TRUE;
        }
        if(MasterI2CReadByte(address,PAC1710_REG_SMSC_ID,&SMSCID))
        {
            SMSCIDGoodRead=TRUE;
        }
        if(MasterI2CReadByte(address,PAC1710_REG_REVISION,&revision))
        {
            revisionGoodRead=TRUE;
        }
    }
    if ((productIDGoodRead&&(productID==PAC1710_PRODUCT_ID))&&
        (SMSCIDGoodRead&&(SMSCID==PAC1710_SMSC_ID))&&
        (revisionGoodRead&&(revision==PAC1710_REVISION)))
    {
        returnValue=TRUE;
    }
    MasterI2CReleasePort();
    return returnValue;
}

/******************************************************************************/

BOOL PAC1710Configure(UINT8 address)
{
    UINT8 dataRead;
    PAC1710_CONFIGURATION_REG_TYPE config;
    PAC1710_VSENSE_REG_TYPE vsense;
    PAC1710_VSOURCE_SAMPLING_CONFIG_REG_TYPE vsourceConfig;
    BOOL returnValue=FALSE;
    if(MasterI2CAvailable()&&MasterI2CClaimPort(POWER_MONITOR))
    {
        vsourceConfig.b=0;
        vsense.b=0;
        config.b=0;
        config.b=0;
        vsourceConfig.VSRC_AVG=VSRC_AVERAGE_DISABLED;
        vsourceConfig.VSRC_SAMP_TIME=VSRC_SAMPLE_TIME_20_MS;
        vsense.CS_RNG=CS_RANGE_10MV;
        vsense.CS_SAMP_AVG=CS_SAMP_DISABLED;
        vsense.CS_SAMP_TIME=CS_SAMPLE_TIME_10_MS;
        config.CONV_DONE_EN=TRUE;
        //config.MASK_ALL=TRUE;

        if(MasterI2CWriteVerifyByteNoRetry(address,PAC1710_REG_CONFIGURATION,config.b))
        {
            if(MasterI2CWriteVerifyByteNoRetry(address,PAC1710_REG_VSOURCE_CONFIG,vsourceConfig.b))
            {
                if(MasterI2CWriteVerifyByteNoRetry(address,PAC1710_REG_VSENSE_CONFIG,vsense.b))
                {
                    if(MasterI2CReadByte(address,PAC1710_REG_CONV_RATE,&dataRead))
                    {
                        if(dataRead==0x03)
                        {
                            returnValue= TRUE;
                        }
                    }
                }
            }
        }
    }
    MasterI2CReleasePort();
    return returnValue;
}

/******************************************************************************/

void PAC1710AlertConfigure(void)
{
    ALERT_N_DIRECTION=TRIS_IN;
    INTalertAsserted=FALSE;
    PAC1710SubsystemFlags.alertAsserted=FALSE;
    INTCONbits.INT1EP=FALSE; /* set for falling edge interrupt */
    INTSetVectorPriority(INT_INT1,ALERT_INT_PRIORITY);
    INTClearFlag(INT_INT1);
    INTEnable(INT_INT1,INT_ENABLED);
}

/******************************************************************************/

BOOL IsAlertAsserted(void)
{
    BOOL returnValue;
    INTEnable(INT_INT1,INT_DISABLED);
    returnValue=INTalertAsserted;
    /* if alert is not asserted, re-enable the interrupt */
    if(!returnValue)
    {
        INTEnable(INT_INT1,INT_ENABLED);
    }
    return returnValue;
}

/******************************************************************************/

void ClearAlertAsserted(void)
{
    INTEnable(INT_INT1,INT_DISABLED);
    INTalertAsserted=FALSE;
    INTEnable(INT_INT1,INT_ENABLED);
}

/******************************************************************************/

void __ISR (_EXTERNAL_1_VECTOR,ALERT_INT_PRIORITY_ISR) _INT1Interrupt(void)
{
    INTEnable(INT_INT1,INT_DISABLED);
    INTClearFlag(INT_INT1);
    INTalertAsserted=TRUE;
}

/******************************************************************************/

BOOL DoPowerMonState(void)
{
    static enum POWER_MONITOR_STATE_TYPE state=PM_STATE_IDLE;
    static I2CBUS_COMMAND_TYPE command;
    if(!PAC1710SubsystemFlags.subsystemConfigured)
    {
        return FALSE;
    }
    if(!MasterI2CHasPort(POWER_MONITOR))
    {
        if(MasterI2CAvailable())
        {
            /* if the port is available, claim it */
            if(!MasterI2CClaimPort(POWER_MONITOR))
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
    /* only get here if the port is claimed by the power monitor subsystem */
    PAC1710SubsystemFlags.alertAsserted=IsAlertAsserted();
    switch (state)
    {
        case PM_STATE_IDLE:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            if (PAC1710SubsystemFlags.alertAsserted) {
                if (PAC1710SubsystemFlags.monitorConfigured) {
                    state = PM_STATE_CHECK_MONITOR;
                } else {
                    state = PM_STATE_ALERT_WRAP_UP;
                }
            }
            break;
        }// </editor-fold>
        case PM_STATE_CHECK_MONITOR:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            if (!MasterI2CIsBusy()) {
                command.status.flags.I2C_read = TRUE;
                command.target_address = PAC1710_ADDRESS;
                command.Word[0] = PAC1710_REG_HIGH_LIMIT_STATUS;
                command.WordSize = 1;
                command.DataSize = 1;
                if (MasterI2CQueueCommand(&command)) {
                    state = PM_STATE_CHECK_MONITOR_WAIT;
                }
            }
            break;
        }// </editor-fold>
        case PM_STATE_CHECK_MONITOR_WAIT:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            if (MasterI2CUpdateQueuedCommand(&command)) {
                PAC1710_HIGH_LIMIT_STATUS_REG_TYPE reg;
                reg.b = command.Data[0];
                if (reg.CONV_DONE) {
                    state = PM_STATE_READ_MONITOR_VOLTAGE;
                } else {
                    state = PM_STATE_ALERT_WRAP_UP;
                }
            } else if (command.status.flags.I2C_error) {
                /* check the other current monitor */
                state = PM_STATE_ALERT_WRAP_UP;
            }
            break;
        }// </editor-fold>
        case PM_STATE_READ_MONITOR_VOLTAGE:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            if (!MasterI2CIsBusy()) {
                command.status.flags.I2C_read = TRUE;
                command.target_address = PAC1710_ADDRESS;
                command.Word[0] = PAC1710_REG_VSOURCE_VOLTAGE_HIGH;
                command.WordSize = 1;
                command.DataSize = 2;
                if (MasterI2CQueueCommand(&command)) {
                    state = PM_STATE_READ_MONITOR_VOLTAGE_WAIT;
                }
            }
            break;
        }// </editor-fold>
        case PM_STATE_READ_MONITOR_VOLTAGE_WAIT:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            if (MasterI2CUpdateQueuedCommand(&command)) {
                monitorVoltageHolding.byte.HB = command.Data[0];
                monitorVoltageHolding.byte.LB = command.Data[1];
                PAC1710SubsystemFlags.monitorVoltageAvailable = TRUE;
                state = PM_STATE_READ_MONITOR_CURRENT;
            } else if (command.status.flags.I2C_error) {
                /* check the other current monitor */
                state = PM_STATE_ALERT_WRAP_UP;
            }
            break;
        }// </editor-fold>
        case PM_STATE_READ_MONITOR_CURRENT:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            if (!MasterI2CIsBusy()) {
                command.status.flags.I2C_read = TRUE;
                command.target_address = PAC1710_ADDRESS;
                command.Word[0] = PAC1710_REG_SENSE_VOLTAGE_HIGH;
                command.WordSize = 1;
                command.DataSize = 2;
                if (MasterI2CQueueCommand(&command)) {
                    state = PM_STATE_READ_MONITOR_CURRENT_WAIT;
                }
            }
            break;
        }// </editor-fold>
        case PM_STATE_READ_MONITOR_CURRENT_WAIT:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            if (MasterI2CUpdateQueuedCommand(&command)) {
                monitorCurrentHolding.byte.HB = command.Data[0];
                monitorCurrentHolding.byte.LB = command.Data[1];
                PAC1710SubsystemFlags.monitorCurrentAvailable = TRUE;
                state = PM_STATE_ALERT_WRAP_UP;
            } else if (command.status.flags.I2C_error) {
                /* check the other current monitor */
                state = PM_STATE_ALERT_WRAP_UP;
            }
            break;
        }// </editor-fold>
        case PM_STATE_MONITOR_WRAP_UP:
        case PM_STATE_ALERT_WRAP_UP:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            MasterI2CReleasePort();
            if (PAC1710SubsystemFlags.monitorVoltageAvailable ||
                    PAC1710SubsystemFlags.monitorCurrentAvailable) {
                PAC1710SubsystemFlags.newDataAvailable = TRUE;
            }
            ClearAlertAsserted();
            PAC1710SubsystemFlags.alertAsserted = FALSE;
            state = PM_STATE_IDLE;
            break;
        }// </editor-fold>
        default:// <editor-fold defaultstate="collapsed" desc="comment">
        {
            MasterI2CReleasePort();
            state = PM_STATE_IDLE;
            break;
        }// </editor-fold>
    }
    return TRUE;
}

/******************************************************************************/

BOOL GetCurrentData(UINT8 address, INT16 *current)
{
    BOOL returnValue=FALSE;
    switch(address)
    {
        case PAC1710_ADDRESS:
        {
            if(PAC1710SubsystemFlags.monitorCurrentAvailable)
            {
                PAC1710SubsystemFlags.monitorCurrentAvailable=FALSE;
                *current=(INT16)monitorCurrentHolding.Val;
                returnValue=TRUE;
            }
            break;
        }
        default:
        {
            break;
        }
    }
    return returnValue;
}

/******************************************************************************/

BOOL GetVoltageData(UINT8 address, INT16 *voltage)
{
    BOOL returnValue=FALSE;
    switch(address)
    {
        case PAC1710_ADDRESS:
        {
            if(PAC1710SubsystemFlags.monitorVoltageAvailable)
            {
                PAC1710SubsystemFlags.monitorVoltageAvailable=FALSE;
                *voltage=(INT16)monitorVoltageHolding.Val;
                returnValue=TRUE;
            }
            break;
        }
        default:
        {
            break;
        }
    }
    return returnValue;
}

/******************************************************************************/
