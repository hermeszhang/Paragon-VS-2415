//###########################################################################
//
// FILE:    Example_2805xECap_Capture_Pwm.c
//
// TITLE:   Capture EPWM3.
//
// ASSUMPTIONS:
//
//    This program requires the F2805x header files.  
//
//    Make the following external connection:
//    EPWM3 on GPIO4 should be connected to ECAP1 on GPIO24.
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
//    This example configures ePWM3A for:
//    - Up count
//    - Period starts at 2 and goes up to 1000
//    - Toggle output on PRD
//
//    eCAP1 is configured to capture the time between rising
//    and falling edge of the PWM3A output.
//
//###########################################################################
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

// Configure the start/end period for the timer
#define PWM3_TIMER_MIN     10                    
#define PWM3_TIMER_MAX     8000

// Prototype statements for functions found within this file.
__interrupt void ecap1_isr(void);
void InitECapture(void);
void InitEPwmTimer(void);
void Fail(void);

// Global variables used in this example
Uint32  ECap1IntCount;
Uint32  ECap1PassCount;
Uint32  EPwm3TimerDirection;

// To keep track of which way the timer value is moving
#define EPWM_TIMER_UP   1
#define EPWM_TIMER_DOWN 0

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
   
   InitEPwm3Gpio();
   InitECap1Gpio();

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
   PieVectTable.ECAP1_INT = &ecap1_isr;
   EDIS;    // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize all the Device Peripherals:
// This function is found in F2805x_InitPeripherals.c
// InitPeripherals();  // Not required for this example
   InitEPwmTimer();    // For this example, only initialize the ePWM Timers
   InitECapture();

// Step 5. User specific code, enable __interrupts:

// Initalize counters:   
   ECap1IntCount = 0;
   ECap1PassCount = 0;
   
// Enable CPU INT4 which is connected to ECAP1-4 INT:
   IER |= M_INT4;

// Enable eCAP INTn in the PIE: Group 3 __interrupt 1-6
   PieCtrlRegs.PIEIER4.bit.INTx1 = 1;

// Enable global Interrupts and higher priority real-time debug events:
   EINT;   // Enable Global __interrupt INTM
   ERTM;   // Enable Global realtime __interrupt DBGM

// Step 6. IDLE loop. Just sit and loop forever (optional):
   for(;;)
   {
      asm("          NOP");
   }

} 

void InitEPwmTimer()
{

   EALLOW;
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
   EDIS;

   EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
   EPwm3Regs.TBPRD = PWM3_TIMER_MIN;
   EPwm3Regs.TBPHS.all = 0x00000000;
   EPwm3Regs.AQCTLA.bit.PRD = AQ_TOGGLE;      // Toggle on PRD
   
   // TBCLK = SYSCLKOUT
   EPwm3Regs.TBCTL.bit.HSPCLKDIV = 1;
   EPwm3Regs.TBCTL.bit.CLKDIV = 0;

   EPwm3TimerDirection = EPWM_TIMER_UP; 
   
   EALLOW;
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
   EDIS;

}

void InitECapture()
{
   ECap1Regs.ECEINT.all = 0x0000;             // Disable all capture __interrupts
   ECap1Regs.ECCLR.all = 0xFFFF;              // Clear all CAP __interrupt flags
   ECap1Regs.ECCTL1.bit.CAPLDEN = 0;          // Disable CAP1-CAP4 register loads
   ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;        // Make sure the counter is stopped
   
   // Configure peripheral registers
   ECap1Regs.ECCTL2.bit.CONT_ONESHT = 1;      // One-shot
   ECap1Regs.ECCTL2.bit.STOP_WRAP = 3;        // Stop at 4 events
   ECap1Regs.ECCTL1.bit.CAP1POL = 1;          // Falling edge
   ECap1Regs.ECCTL1.bit.CAP2POL = 0;          // Rising edge
   ECap1Regs.ECCTL1.bit.CAP3POL = 1;          // Falling edge
   ECap1Regs.ECCTL1.bit.CAP4POL = 0;          // Rising edge
   ECap1Regs.ECCTL1.bit.CTRRST1 = 1;          // Difference operation         
   ECap1Regs.ECCTL1.bit.CTRRST2 = 1;          // Difference operation         
   ECap1Regs.ECCTL1.bit.CTRRST3 = 1;          // Difference operation         
   ECap1Regs.ECCTL1.bit.CTRRST4 = 1;          // Difference operation         
   ECap1Regs.ECCTL2.bit.SYNCI_EN = 1;         // Enable sync in
   ECap1Regs.ECCTL2.bit.SYNCO_SEL = 0;        // Pass through
   ECap1Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable capture units

   ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;        // Start Counter
   ECap1Regs.ECCTL2.bit.REARM = 1;            // arm one-shot
   ECap1Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
   ECap1Regs.ECEINT.bit.CEVT4 = 1;            // 4 events = __interrupt

}

__interrupt void ecap1_isr(void)
{

   // Cap input is syc'ed to SYSCLKOUT so there may be
   // a +/- 1 cycle variation
    
   if(ECap1Regs.CAP2 > EPwm3Regs.TBPRD*2+1 || ECap1Regs.CAP2 < EPwm3Regs.TBPRD*2-1) 
   {
       Fail();
   }

   if(ECap1Regs.CAP3 > EPwm3Regs.TBPRD*2+1 || ECap1Regs.CAP3 < EPwm3Regs.TBPRD*2-1) 
   {
       Fail();
   }
   
   if(ECap1Regs.CAP4 > EPwm3Regs.TBPRD*2+1 || ECap1Regs.CAP4 < EPwm3Regs.TBPRD*2-1) 
   {
       Fail();
   }   

   ECap1IntCount++;

   if(EPwm3TimerDirection == EPWM_TIMER_UP)
   {
        if(EPwm3Regs.TBPRD < PWM3_TIMER_MAX) 
        {
           EPwm3Regs.TBPRD++;
        }
        else
        {
           EPwm3TimerDirection = EPWM_TIMER_DOWN;
           EPwm3Regs.TBPRD--;
        }
   }
   else
   {
        if(EPwm3Regs.TBPRD > PWM3_TIMER_MIN) 
        {
           EPwm3Regs.TBPRD--;
        }
        else
        {
           EPwm3TimerDirection = EPWM_TIMER_UP;
           EPwm3Regs.TBPRD++;
        }
   }   

   ECap1PassCount++;

   ECap1Regs.ECCLR.bit.CEVT4 = 1;
   ECap1Regs.ECCLR.bit.INT = 1;
   ECap1Regs.ECCTL2.bit.REARM = 1;

   // Acknowledge this __interrupt to receive more __interrupts from group 4
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
}

void Fail()
{
   asm("   ESTOP0");
}

//===========================================================================
// No more.
//===========================================================================
