#include <common.h>

typedef enum
{                       /******************************************************/
	EXCEP_IRQ = 0,	/* 0 - interrupt                                      */
	EXCEP_AdEL = 4,	/* 4 - address error exception (load or ifetch)       */
	EXCEP_AdES,	/* 5 - address error exception (store)                */
	EXCEP_IBE,	/* 6 - bus error (ifetch)                             */
	EXCEP_DBE,	/* 7 - bus error (load/store)                         */
	EXCEP_Sys,	/* 8 - syscall                                        */
	EXCEP_Bp,	/* 9 - breakpoint                                     */
	EXCEP_RI,	/* 10 - reserved instruction                          */
	EXCEP_CpU,	/* 11 - coprocessor unusable                          */
	EXCEP_Overflow,	/* 12 - arithmetic overflow                           */
	EXCEP_Trap,	/* 13 - trap (possible divide by zero)                */
	EXCEP_IS1 = 16,	/* 16 - implementation specfic                        */
	EXCEP_CEU,	/* 17 - CorExtend Unuseable                           */
	EXCEP_C2E	/* 18 - coprocessor 2                                 */
} _excep_code;          /******************************************************/

/******************************************************************************/
/* void _general_exception_handler(unsigned int Cause, unsigned int Status)   */
/*                                                                            */
/* PreCondition:    None                                                      */
/*                                                                            */
/* Input:           None                                                      */
/*                                                                            */
/* Output:          None                                                      */
/*                                                                            */
/* Side Effects:    None                                                      */
/*                                                                            */
/*  Overview:       Overrides (weak) general exception handler provided by    */
/*                  C32. Uses C32 macros to read epc and cause registers.     */
/*                  Application code can then do something useful with them.  */
/*                                                                            */
/******************************************************************************/

void __attribute__((naked, nomips16)) _general_exception_handler(UINT32 cause, UINT32 status)
{
    UINT32 count=0;
    UINT32 _epc=0;
    UINT32 _status = 0;
    _excep_code _cause = 0;

    _status = status;
    _cause = ((cause & 0x0000007C) >> 2);
    _epc = _CP0_GET_EPC();
    while(TRUE)
    {
        Nop();
    }
} 
