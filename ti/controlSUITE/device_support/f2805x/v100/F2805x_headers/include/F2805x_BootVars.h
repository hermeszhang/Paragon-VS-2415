//###########################################################################
//
// FILE:    F2805x_BootVars.h
//
// TITLE:   F2805x Boot Variable Definitions.
//
// NOTES:
//
//###########################################################################
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//###########################################################################

#ifndef F2805x_BOOT_VARS_H
#define F2805x_BOOT_VARS_H

#ifdef __cplusplus
extern "C" {
#endif



//---------------------------------------------------------------------------
// External Boot ROM variable definitions:
//
extern Uint16 EmuKey;
extern Uint16 EmuBMode;
extern Uint32 Flash_CPUScaleFactor;
extern void (*Flash_CallbackPtr) (void);

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif                                  // end of F2805x_BOOT_VARS_H definition

//===========================================================================
// End of file.
//===========================================================================
