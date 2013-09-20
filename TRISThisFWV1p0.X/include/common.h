/******************************************************************************/
/* File:   common.h                                                           */
/* Author: Matt Bennett                                                       */
/*                                                                            */
/* Created on December 16, 2012, 5:07 PM                                      */
/******************************************************************************/

#ifndef _COMMON_H_
    #define _COMMON_H_
#define _PLIB_DISABLE_LEGACY
    #include <p32xxxx.h>
    #include <GenericTypeDefs.h>
    #include <plib.h>
    #include <limits.h>
    
    #include <hardwareConfiguration.h>
    #include <firmwareConfiguration.h>
    #include <clockomatic.h>

    #define TRIS_OUT    0
    #define TRIS_IN     1

    #define FAIL        0
    #define SUCCESS     1

    #ifdef __DEBUG
        #define mClearWatchdog()
        #define mEnableWatchdog()
    #else
        #define mClearWatchdog()    WDTCONSET = _WDTCON_WDTCLR_MASK
        #define mEnableWatchdog()   WDTCONSET = _WDTCON_ON_MASK
    #endif
#else
    #warning "Redundant include of common.h"

#endif	/* _COMMON_H */

