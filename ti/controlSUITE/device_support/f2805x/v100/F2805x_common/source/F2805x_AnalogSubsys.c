//###########################################################################
//
// FILE:    F2805x_AnalogSubsys.c
//
// TITLE:   F2805x Analog Subsystem Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//###########################################################################

#include "F2805x_Device.h"     // F2805x Headerfile Include File
#include "F2805x_Examples.h"   // F2805x Examples Include File

#define ADC_usDELAY  1000L

//---------------------------------------------------------------------------
// InitAdc:
//---------------------------------------------------------------------------
// This function initializes Analog Subsystem to a known state.

void InitAdcSubsys(void)
{
    // TBD...
}

void InitCTRIPGpio(void)
{
    InitCTRIPM1Gpio();
	InitCTRIPM2Gpio();
	InitCTRIPPFCGpio();

}


void InitCTRIPM1Gpio()
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   to reduce power consumption */
// Pull-ups can be enabled or disabled disabled by the user.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;    // Disable pull-up for GPIO1 (CTRIPM1OUT)
//  GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1;   // Disable pull-up for GPIO12 (CTRIPM1OUT)
//  GpioCtrlRegs.GPAPUD.bit.GPIO15 = 1;   // Disable pull-up for GPIO15 (CTRIPM1OUT)
//  GpioCtrlRegs.GPAPUD.bit.GPIO20 = 1;   // Disable pull-up for GPIO20 (CTRIPM1OUT)
//  GpioCtrlRegs.GPBPUD.bit.GPIO42 = 1;   // Disable pull-up for GPIO42 (CTRIPM1OUT)

/* Configure CTRIP pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be CTRIP functional pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 3;   // Configure GPIO1 for CTRIPM1OUT operation
// GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 3;  // Configure GPIO20 for CTRIPM1OUT operation
// GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 3;  // Configure GPIO42 for CTRIPM1OUT operation

// GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 for CTRIPM1OUT/TZ operation
// GpioCtrlRegs.GPADIR.bit.GPIO12 = 1  // Configure GPIO12 (CTRIPM1OUT) for output

// GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 1;  // Configure GPIO15 for CTRIPM1OUT/TZ operation
// GpioCtrlRegs.GPADIR.bit.GPIO15 = 1  // Configure GPIO15 (CTRIPM1OUT) for output

    EDIS;
}


void InitCTRIPM2Gpio()
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   to reduce power consumption */
// Pull-ups can be enabled or disabled disabled by the user.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;    // Disable pull-up for GPIO3 (CTRIPM2OUT)
//  GpioCtrlRegs.GPAPUD.bit.GPIO13 = 1;   // Disable pull-up for GPIO13 (CTRIPM2OUT)
//	GpioCtrlRegs.GPAPUD.bit.GPIO16 = 1;   // Disable pull-up for GPIO16 (CTRIPM2OUT)
//  GpioCtrlRegs.GPAPUD.bit.GPIO21 = 1;   // Disable pull-up for GPIO21 (CTRIPM2OUT)
//	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 1;   // Disable pull-up for GPIO28 (CTRIPM2OUT)
//  GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;   // Disable pull-up for GPIO34 (CTRIPM2OUT)
//  GpioCtrlRegs.GPBPUD.bit.GPIO43 = 1;   // Disable pull-up for GPIO43 (CTRIPM2OUT)

/* Configure Comp pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be Comp functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 3;   // Configure GPIO3 for CTRIPM2OUT operation
//  GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 3;  // Configure GPIO21 for CTRIPM2OUT operation
//  GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 1;  // Configure GPIO34 for CTRIPM2OUT operation
//  GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 3;  // Configure GPIO43 for CTRIPM2OUT operation

//	GpioCtrlRegs.GPAMUX2.bit.GPIO13 = 1;  // Configure GPIO13 for CTRIPM2OUT/TZ operation
//  GpioCtrlRegs.GPADIR.bit.GPIO13 = 1;  // Configure GPIO13 (CTRIPM2OUT) as output

//	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3;  // Configure GPIO16 for CTRIPM2OUT/TZ operation
//  GpioCtrlRegs.GPADIR.bit.GPIO16 = 1;  // Configure GPIO16 (CTRIPM2OUT) as output

//  GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // Configure GPIO28 for CTRIPM2OUT/TZ operation
//  GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;  // Configure GPIO28 (CTRIPM2OUT) as output

    EDIS;
}


void InitCTRIPPFCGpio()
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   to reduce power consumption */
// Pull-ups can be enabled or disabled disabled by the user.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAPUD.bit.GPIO14 = 1;    // Disable pull-up for GPIO14 (CTRIPPFCOUT)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 1;    // Disable pull-up for GPIO17 (CTRIPPFCOUT)
//  GpioCtrlRegs.GPAPUD.bit.GPIO29 = 1;    // Disable pull-up for GPIO29 (CTRIPPFCOUT)
//  GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;    // Disable pull-up for GPIO34 (CTRIPPFCOUT)
//  GpioCtrlRegs.GPBPUD.bit.GPIO39 = 1;    // Disable pull-up for GPIO39 (CTRIPPFCOUT)

/* Configure Comp pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be Comp functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 3;  // Configure GPIO34 for CTRIPPFCOUT operation
//  GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 3;  // Configure GPIO39 for CTRIPPFCOUT operation

//  GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 3;  // Configure GPIO14 for CTRIPPFCOUT/TZ operation
//  GpioCtrlRegs.GPADIR.bit.GPIO14 = 1;  // Configure GPIO14 (CTRIPPFOUT) as output

    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 3;  // Configure GPIO17 for CTRIPPFCOUT/TZ operation
    GpioCtrlRegs.GPADIR.bit.GPIO17 = 1;  // Configure GPIO17 (CTRIPPFOUT) as output

//  GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // Configure GPIO29 for CTRIPPFCOUT/TZ operation
//  GpioCtrlRegs.GPADIR.bit.GPIO29 = 1;  // Configure GPIO29 (CTRIPPFOUT) as output

    EDIS;
}

//===========================================================================
// End of file.
//===========================================================================
