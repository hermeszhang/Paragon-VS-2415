//###########################################################################
//
// FILE:	Example_2805xEqep_freqcal.c
//
// TITLE:	Frequency measurement using EQEP peripheral
//
// ASSUMPTIONS:
//
//    This program requires the F2805x header files.
//    As supplied, this project is configured for "boot to SARAM" operation.
//
//    Test requires the following hardware connections
//
//    GPIO20/EQEP1A <- External input - connect to GPIO0/EPWM1A
//
//    As supplied, this project is configured for "boot to SARAM"
//    operation.  The 2805x Boot Mode table is shown below.
//    For information on configuring the boot mode of an eZdsp,
//    please refer to the documentation included with the eZdsp.
//    $Boot_Table:
//
//    While an emulator is connected to your device, the TRSTn pin = 1,
//    which sets the device into EMU_BOOT boot mode. In this mode, the
//    peripheral boot modes are as follows:
//
//      Boot Mode:       EMU_KEY        EMU_BMODE
//                       (0xD00)	     (0xD01)
//      ---------------------------------------
//      Wait             !=0x55AA        X
//      I/O              0x55AA	         0x0000
//      SCI              0x55AA	         0x0001
//      Wait             0x55AA	         0x0002
//      Get_Mode         0x55AA	         0x0003
//      SPI              0x55AA	         0x0004
//      I2C              0x55AA	         0x0005
//      OTP              0x55AA	         0x0006
//      eCANA            0x55AA	         0x0007 
//      SARAM            0x55AA	         0x000A	  <-- "Boot to SARAM"
//      Flash            0x55AA	         0x000B
//      Wait             0x55AA          Other
//
//   Write EMU_KEY to 0xD00 and EMU_BMODE to 0xD01 via the debugger
//   according to the Boot Mode Table above. Build/Load project,
//   Reset the device, and Run example
//
//   $End_Boot_Table
//
//
// Description:
//
//    This test will provide frequency measurement using capture unit (freqhz_pr)
//    and unit time out (freqhz_fr).
//
//    By default, EPWM1A is configured to generate a frequency of 5 kHz.
//
//    See DESCRIPTION in Example_freqcal.c for more details on the frequency calculation
//    performed in this example.
//
//    In addition to this file, the following files must be included in this project:
//    Example_freqcal.c - includes all eQEP functions
//    Example_EPwmSetup.c - sets up EPWM1A for use with this example
//    Example_freqcalh - includes initialization values for frequency structure.
//
//    * Maximum frequency is configured to 10Khz (BaseFreq)
//    * Minimum frequency is assumed at 50Hz for capture pre-scalar selection
//
//    SPEED_FR: High Frequency Measurement is obtained by counting the external input pulses
//              for 10ms (unit timer set to 100Hz).
//
// 	  SPEED_FR = { (Count Delta)/10ms }
//
//
//    SPEED_PR: Low Frequency Measurement is obtained by measuring time period of input edges.
//              Time measurement is averaged over 64edges for better results and
//              capture unit performs the time measurement using pre-scaled SYSCLK
//
//              Note that pre-scaler for capture unit clock is selected such that
//              capture timer does not overflow at the required minimum frequency
//
//              This example runs forever until the user stops it.
//
//    --------------------------------------------------------------
//    CODE MODIFICATIONS ARE REQUIRED FOR 60 MHZ DEVICES (In
//    F2805x_Examples.h in the common/include/ directory, set
//    #define CPU_FRQ_60MHZ to 1, and #define CPU_FRQ_100MHZ to 0).
//    --------------------------------------------------------------
//
//    Watch Variables: freq.freqhz_fr - Frequency measurement using position counter/unit time out
//                     freq.freqhz_pr - Frequency measurement using capture unit
//
//###########################################################################
// Original Author: SD
//
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Example_freqcal.h"    // Example specific include file

void EPwmSetup(void);
__interrupt void prdTick(void);

FREQCAL freq=FREQCAL_DEFAULTS;

void main(void)
{

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2805x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the F2805x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example

// Only init the GPIO for EQep1 and EPwm1 in this case
// This function is found in F2805x_EQep.c
   InitEQep1Gpio();
   InitEPwm1Gpio();

// Step 3. Clear all __interrupts and initialize PIE vector table:
// Disable CPU __interrupts
   DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE __interrupts disabled and flags
// are cleared.
// This function is found in the F2805x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU __interrupts and clear all CPU __interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the __interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2805x_DefaultIsr.c.
// This function is found in F2805x_PieVect.c.
   InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.EPWM1_INT= &prdTick;
   EDIS;    // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize all the Device Peripherals:
// Example specific ePWM setup.  This function is found
// in Example_EPwmSetup.c
   EPwmSetup();

// Step 5. User specific code, enable __interrupts:
// Enable CPU INT1 which is connected to CPU-Timer 0:
   IER |= M_INT3;

// Enable TINT0 in the PIE: Group 3 __interrupt 1
   PieCtrlRegs.PIEIER3.bit.INTx1 = 1;

// Enable global Interrupts and higher priority real-time debug events:
   EINT;   // Enable Global __interrupt INTM
   ERTM;   // Enable Global realtime __interrupt DBGM

   freq.init(&freq);         // Initializes eQEP for frequency calculation in
                             // FREQCAL_Init(void)function in Example_EPwmSetup.c
	for(;;)
	{
	}

}

__interrupt void prdTick(void) // Interrupts once per ePWM period
{
   freq.calc(&freq); // Checks for event and calculates frequency in FREQCAL_Calc(FREQCAL *p)
                     // function in Example_EPwmSetup.c
   // Acknowledge this __interrupt to receive more __interrupts from group 1
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
   EPwm1Regs.ETCLR.bit.INT=1;
}

