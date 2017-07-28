//########################################################################### 
// 
// FILE:   F2805x_Devemu.h 
// 
// TITLE:  F2805x Device DEVEMU Register Definitions. 
// 
//########################################################################### 
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//########################################################################### 

#ifndef F2805x_DEVEMU_H 
#define F2805x_DEVEMU_H 

#ifdef __cplusplus 
extern "C" {
#endif 


//--------------------------------------------------------------------------- 
// DEVEMU Individual Register Bit Definitions: 

struct DEVICECNF_BITS {                    // bits description
    Uint16  rsvd1:3;                       // 2:0 Reserved 
    Uint16  VMAPS:1;                       // 3 VMAP Configure Status 
    Uint16  rsvd2:1;                       // 4 Reserved 
    Uint16  XRSn:1;                        // 5 Reset Input Signal Status 
    Uint16  rsvd3:10;                      // 15:6 Reserved 
    Uint16  rsvd4:3;                       // 18:16 Reserved 
    Uint16  ENPROT:1;                      // 19 Enable Write-Read Protection Mode Bit 
    Uint16  rsvd5:1;                       // 20 Reserved 
    Uint16  rsvd6:6;                       // 26:21 Reserved 
    Uint16  TRSTn:1;                       // 27 Read Status of TRSTn Signal 
    Uint16  rsvd7:4;                       // 31:28 Reserved 
};

union DEVICECNF_REG {
    Uint32  all;  
    struct  DEVICECNF_BITS  bit;  
};

struct PARTID_BITS {                       // bits description
    Uint16  PARTNO:8;                      // 7:0 Part Number 
    Uint16  CLASSTYPE:8;                   // 15:8 Class Type 
};

union PARTID_REG {
    Uint16  all;  
    struct  PARTID_BITS  bit;  
};

struct DEV_EMU_REGS {
    union   DEVICECNF_REG    DEVICECNF;    // Device Configuration Register 
    union   PARTID_REG       PARTID;       // Device ID Register 
    Uint16                   REVID;        // Revision ID Register 
    Uint16                   rsvd1[2];     // Reserved 
    Uint16                   rsvd2;        // Reserved 
    Uint16                   rsvd3;        // Reserved 
    Uint16                   rsvd4;        // Reserved 
};

//---------------------------------------------------------------------------
// Devemu External References & Function Declarations:
//
extern volatile struct DEV_EMU_REGS DevEmuRegs;

#ifdef __cplusplus
}
#endif                                     /* extern "C" */


#endif                                     // end of F2805x_DEVEMU_H definition
//===========================================================================
// End of file.
//===========================================================================
