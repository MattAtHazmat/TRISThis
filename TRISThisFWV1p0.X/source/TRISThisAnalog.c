/******************************************************************************/
/* File:   TRISThisAnalog.c                                                   */
/* Author: Matt Bennett                                                       */
/*                                                                            */
/* Created on May 12, 2014, 8:20 PM                                           */
/******************************************************************************/

#include <common.h>
#include <MCP4461.h>
#include <TRISThis.h>
#include <TRISThisAnalog.h>

uint16_t analogGain[TRISTHIS_NUMBER_ANALOG_PORTS];
uint16_t analogReading[TRISTHIS_NUMBER_ANALOG_PORTS];
/******************************************************************************/


/******************************************************************************/
