//########################################################################### 
// 
// FILE:   F2805x_Nmiintrupt.h 
// 
// TITLE:  F2805x Device NmiIntrupt Register Definitions. 
// 
//########################################################################### 
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//########################################################################### 

#ifndef F2805x_NmiIntrupt_H 
#define F2805x_NmiIntrupt_H 

#ifdef __cplusplus 
extern "C" {
#endif 


//--------------------------------------------------------------------------- 
// NmiIntrupt Individual Register Bit Definitions: 

struct NMICFG_BITS {                       // bits description
    Uint16  rsvd1:1;                       // 0 Reserved 
    Uint16  CLOCKFAIL:1;                   // 1 CLOCKFAIL NMI Interrupt Enable 
    Uint16  rsvd2:14;                      // 15:2 Reserved 
};

union NMICFG_REG {
    Uint16  all;  
    struct  NMICFG_BITS  bit;  
};

struct NMIFLG_BITS {                       // bits description
    Uint16  NMIINT:1;                      // 0 NMI Interrupt Flag 
    Uint16  CLOCKFAIL:1;                   // 1 CLOCKFAIL NMI Flag 
    Uint16  rsvd1:14;                      // 15:2 Reserved 
};

union NMIFLG_REG {
    Uint16  all;  
    struct  NMIFLG_BITS  bit;  
};

struct NMIFLGCLR_BITS {                    // bits description
    Uint16  NMIINT:1;                      // 0 NMI Interrupt Flag Clear 
    Uint16  CLOCKFAIL:1;                   // 1 CLOCKFAIL NMI Flag Clear 
    Uint16  rsvd1:14;                      // 15:2 Reserved 
};

union NMIFLGCLR_REG {
    Uint16  all;  
    struct  NMIFLGCLR_BITS  bit;  
};

struct NMIFLGFRC_BITS {                    // bits description
    Uint16  rsvd1:1;                       // 0 Reserved 
    Uint16  CLOCKFAIL:1;                   // 1 CLOCKFAIL NMI Flag Force 
    Uint16  rsvd2:14;                      // 15:2 Reserved 
};

union NMIFLGFRC_REG {
    Uint16  all;  
    struct  NMIFLGFRC_BITS  bit;  
};

struct NMI_INTRUPT_REGS {
    union   NMICFG_REG       NMICFG;       // C28 NMI Configuration Register 
    union   NMIFLG_REG       NMIFLG;       // C28 NMI Flag Register 
    union   NMIFLGCLR_REG    NMIFLGCLR;    // C28 NMI Flag Clear Register 
    union   NMIFLGFRC_REG    NMIFLGFRC;    // C28 NMI Flag Force Register 
    Uint16                   NMIWDCNT;     // C28 NMI Watchdog Counter Register 
    Uint16                   NMIWDPRD;     // C28 NMI Watchdog Period Register 
};

//---------------------------------------------------------------------------
// Nmiintrupt External References & Function Declarations:
//
extern volatile struct NMI_INTRUPT_REGS NmiIntruptRegs;

#ifdef __cplusplus
}
#endif                                     /* extern "C" */


#endif                                     // end of F2805x_NmiIntrupt_H definition
//===========================================================================
// End of file.
//===========================================================================
