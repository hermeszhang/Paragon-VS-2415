//###########################################################################
//
// FILE:   F2805x_EQep.c
//
// TITLE:  F2805x eQEP Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//###########################################################################

#include "F2805x_Device.h"     // F2805x Headerfile Include File
#include "F2805x_Examples.h"   // F2805x Examples Include File

//---------------------------------------------------------------------------
// InitEQep:
//---------------------------------------------------------------------------
// This function initializes the eQEP(s) to a known state.
//
void InitEQep(void)
{
   // Initialize eQEP1

   //tbd...

}

//---------------------------------------------------------------------------
// Example: InitEQepGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as eQEP pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// For each eQEP peripheral
// Only one GPIO pin should be enabled for EQEPxA operation.
// Only one GPIO pin should be enabled for EQEPxB operation.
// Only one GPIO pin should be enabled for EQEPxS operation.
// Only one GPIO pin should be enabled for EQEPxI operation.
// Comment out other unwanted lines.

void InitEQepGpio()
{
#if DSP28_EQEP1
   InitEQep1Gpio();
#endif  // endif DSP28_EQEP1
}

#if DSP28_EQEP1
void InitEQep1Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   // Enable pull-up on GPIO20 (EQEP1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;   // Enable pull-up on GPIO21 (EQEP1B)
    GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;   // Enable pull-up on GPIO22 (EQEP1S)
    GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;   // Enable pull-up on GPIO23 (EQEP1I)
	
	// GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pull-up on GPIO32 (EQEP1S)
    // GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pull-up on GPIO33 (EQEP1I)
	
	// GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pull-up on GPIO16 (EQEP1S)
    // GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pull-up on GPIO17 (EQEP1I)
	

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = 0;   // Sync to SYSCLKOUT GPIO20 (EQEP1A)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 0;   // Sync to SYSCLKOUT GPIO21 (EQEP1B)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 0;   // Sync to SYSCLKOUT GPIO22 (EQEP1S)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 0;   // Sync to SYSCLKOUT GPIO23 (EQEP1I)

    // GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0;   // Sync to SYSCLKOUT GPIO32 (EQEP1S)
    // GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 0;   // Sync to SYSCLKOUT GPIO33 (EQEP1I)
	
    // GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 0;   // Sync to SYSCLKOUT GPIO16 (EQEP1S)
    // GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 0;   // Sync to SYSCLKOUT GPIO17 (EQEP1I)

/* Configure eQEP-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eQEP1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;   // Configure GPIO20 as EQEP1A
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;   // Configure GPIO21 as EQEP1B
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 1;   // Configure GPIO22 as EQEP1S
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;   // Configure GPIO23 as EQEP1I
	
	// GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 3;   // Configure GPIO32 as EQEP1S
	// GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 3;   // Configure GPIO32 as EQEP1I
	
	// GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 2;   // Configure GPIO16 as EQEP1S
	// GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 2;   // Configure GPIO17 as EQEP1I
    EDIS;
}
#endif // if DSP28_EQEP1

//===========================================================================
// End of file.
//===========================================================================
