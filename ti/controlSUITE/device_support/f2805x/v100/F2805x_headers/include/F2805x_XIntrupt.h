//########################################################################### 
// 
// FILE:   F2805x_Xintrupt.h 
// 
// TITLE:  F2805x Device XINTRUPT Register Definitions. 
// 
//########################################################################### 
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//########################################################################### 

#ifndef F2805x_XINTRUPT_H 
#define F2805x_XINTRUPT_H 

#ifdef __cplusplus 
extern "C" {
#endif 


//--------------------------------------------------------------------------- 
// XINTRUPT Individual Register Bit Definitions: 

struct XINTCR_BITS {                    // bits description
    Uint16  ENABLE:1;                   // 0 XINT1 Enable 
    Uint16  rsvd1:1;                    // 1 Reserved 
    Uint16  POLARITY:2;                 // 3:2 XINT1 Polarity 
    Uint16  rsvd2:12;                   // 15:4 Reserved 
};

union XINTCR_REG {
    Uint16  all;  
    struct  XINTCR_BITS  bit;  
};

struct XINTRUPT_REGS {
    union   XINTCR_REG    XINT1CR;      // XINT1 Configuration Register 
    union   XINTCR_REG    XINT2CR;      // XINT2 Configuration Register 
    union   XINTCR_REG    XINT3CR;      // XINT3 Configuration Register 
    Uint16                rsvd1[5];     // Reserved 
    Uint16                XINT1CTR;     // XINT1 Counter Register 
    Uint16                XINT2CTR;     // XINT2 Counter Register 
    Uint16                XINT3CTR;     // XINT3 Counter Register 
};

//---------------------------------------------------------------------------
// Xintrupt External References & Function Declarations:
//
extern volatile struct XINTRUPT_REGS XIntruptRegs;

#ifdef __cplusplus
}
#endif                                  /* extern "C" */


#endif                                  // end of F2805x_XINTRUPT_H definition
//===========================================================================
// End of file.
//===========================================================================
