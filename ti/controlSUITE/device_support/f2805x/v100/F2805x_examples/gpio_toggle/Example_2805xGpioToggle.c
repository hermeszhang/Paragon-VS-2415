//###########################################################################
//
// FILE:    Example_281xGpioToggle.c
//
// TITLE:   F2805x Device GPIO toggle test program. 
//
// ASSUMPTIONS:
//
//    This program requires the F2805x header files.  
//
//    ALL OF THE I/O'S TOGGLE IN THIS PROGRAM.  MAKE SURE
//    THIS WILL NOT DAMAGE YOUR HARDWARE BEFORE RUNNING THIS
//    EXAMPLE.
//
//    Monitor desired pins on an oscilloscope.
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
//     Three different examples are included. Select the example 
//     (data, set/clear or toggle) to execute before compiling using
//     the #define statements found at the top of the code.   
//
//
//     Toggle all of the GPIO PORT pins 
//        
//    The pins can be observed using Oscilloscope.  
// 
//
//###########################################################################
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

// Select the example to compile in.  Only one example should be set as 1
// the rest should be set as 0.
#define EXAMPLE1 1  // Use DATA registers to toggle I/O's
#define EXAMPLE2 0  // Use SET/CLEAR registers to toggle I/O's
#define EXAMPLE3 0  // Use TOGGLE registers to toggle I/O's

// Prototype statements for functions found within this file.
void delay_loop(void);
void Gpio_select(void);
void Gpio_example1(void);
void Gpio_example2(void);
void Gpio_example3(void);

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
 
// For this example use the following configuration:
   Gpio_select();	  

// Step 3. Clear all __interrupts and initialize PIE vector table:
// Disable CPU __interrupts 
   DINT;

// Initialize PIE control registers to their default state.
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

	
// Step 4. Initialize all the Device Peripherals:
// This function is found in F2805x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
	
// Step 5. User specific code:
	
#if EXAMPLE1

    // This example uses DATA registers to toggle I/O's
    Gpio_example1();

#endif  // - EXAMPLE1

#if EXAMPLE2

    // This example uses SET/CLEAR registers to toggle I/O's
    Gpio_example2();
    
#endif

#if EXAMPLE3

    // This example uses TOGGLE registers to toggle I/O's
    Gpio_example3();
    
#endif

} 	

void delay_loop()
{
    short      i;
    for (i = 0; i < 1000; i++) {}
}

void Gpio_example1(void)
{ 
   // Example 1:
   // Toggle I/Os using DATA registers

   for(;;)
   {   
      GpioDataRegs.GPADAT.all    =0xAAAAAAAA;                 
      GpioDataRegs.GPBDAT.all    =0x00000AAA;
      delay_loop();

      GpioDataRegs.GPADAT.all    =0x55555555;  
      GpioDataRegs.GPBDAT.all    =0x00001555; 

       delay_loop();    
    }
}

void Gpio_example2(void)
{ 
   // Example 2:
   // Toggle I/Os using SET/CLEAR registers
   for(;;)
   {    

       GpioDataRegs.GPASET.all    =0xAAAAAAAA;
       GpioDataRegs.GPACLEAR.all  =0x55555555;

       GpioDataRegs.GPBSET.all    =0x00000AAA;                 
       GpioDataRegs.GPBCLEAR.all  =0x00001555; 

       delay_loop();

       GpioDataRegs.GPACLEAR.all    =0xAAAAAAAA;
       GpioDataRegs.GPASET.all      =0x55555555;

       GpioDataRegs.GPBCLEAR.all    =0x00000AAA;                 
       GpioDataRegs.GPBSET.all      =0x00001555;  

       delay_loop();    

    }
}

void Gpio_example3(void)
{ 
   // Example 3:
   // Toggle I/Os using TOGGLE registers

   // Set pins to a known state

      GpioDataRegs.GPASET.all    =0xAAAAAAAA;
      GpioDataRegs.GPACLEAR.all  =0x55555555;

      GpioDataRegs.GPBSET.all    =0x00000AAA;                 
      GpioDataRegs.GPBCLEAR.all  =0x00001555;                  

   // Use TOGGLE registers to flip the state of
   // the pins. 
   // Any bit set to a 1 will flip state (toggle)
   // Any bit set to a 0 will not toggle.   

   for(;;)
   {    
      GpioDataRegs.GPATOGGLE.all =0xFFFFFFFF;
      GpioDataRegs.GPBTOGGLE.all =0x00001FFF; 

      delay_loop();
    }
}
void Gpio_select(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.all = 0x00000000;  // All GPIO
    GpioCtrlRegs.GPAMUX2.all = 0x00000000;  // All GPIO
    GpioCtrlRegs.GPBMUX1.all = 0x00000000;  // All GPIO

    GpioCtrlRegs.GPADIR.all = 0xFFFFFFFF;   // All outputs
    GpioCtrlRegs.GPBDIR.all = 0x00001FFF;   // All outputs 
    EDIS;

}
//===========================================================================
// No more.
//===========================================================================

