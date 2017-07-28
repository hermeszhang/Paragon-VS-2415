//###########################################################################
//
// FILE:   Example_2805xClaAdcFir.c
//
// TITLE:  CLA FIR filter example
//
// ASSUMPTIONS:
//
//   This program requires the F2805x header files.
//
//   Make sure the CPU clock speed is properly defined in
//   F2805x_Examples.h before compiling this example.
//
//   For testing, connect a jumper between to ADCINA2 and GPIO4 (EPWM3A)
//
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
//   This example sets up the PLL in x12/2 mode.
//
//   For 60 MHz devices (default) (assuming a 10Mhz input clock).
//
//   * ePWM1 is setup to generate a periodic ADC SOC. 
//   * One channel is converted: ADCINA7 and the results are placed in 
//     the ADC RESULT1 register
//   * When the ADC sample window ends and it begins conversion, it 
//     will assert ADCINT7 
//   * The CLA responds to ADCINT7 and executes CLA Task 7.
//   * CLA Task7 is an FIR filter.  The output from the filter is
//     placed in  
//   * When Task 7 complets, it fires the CLA1_INT7 __interrupt to the
//     main CPU.  
//   * The main CPU will clear the ADCINT flag, copy the CLA output to 
//     a buffer and also record the raw ADCRESULT1 value for comparison
//
//   * After ADC_BUF_LEN samples are collected, the code will halt on
//     an embedded software breaktpoint.
//
//   Watch Variables:
//
//      It is suggested that you graph the AdcBuf and AdcFiltBuf arrays
//      as shown in the included .jpg screenshot files.
//
//      Uint16 AdcBuf[ADC_BUF_LEN]       Buffer of raw ADC RESULT1 values
//      Uint16 AdcFiltBuf[ADC_BUF_LEN]   Buffer of CLA FIR filter outputs                 
//      Uint16 SampleCount               Current sample number
//
//###########################################################################
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//###########################################################################

#include "DSP28x_Project.h" // includes all of the header files and defines used in the
                            // example projects    
#include "CLAShared.h"      // includes all of the shared variables (shared between
                            // C28x C source and CLA assembly code)

// 
// If you want a low-pass filter, then set LOWPASS to 1
// If you want a high-pass filter, then set HIGHPASS to 1
// This will select the proper filter coefficients
//

#define LOWPASS             0
#define HIGHPASS            1

// 
// 
// ADC_SAMPLE_PERIOD is used to configure ePWM1 in 
// up count mode with TBPRD = 1/2 SYSCLKOUT = 30 MHz
// 
//      An ADC SOC will be started every ePWM1 period. 
//      For a 20 KHz sampling rate:
//      -> Tpwm = (TBPRD + 1) x (1/30 MHz)
//      -> TBPRD = (1/20KHz)x(30MHz)-1 = 1499 
// 
// PWM_PERIOD is the period for ePWM3. This will be sampled
// by the ADC.  
// 
// PWM_DUTY_CYCLE is the duty cycle for ePWM3.  This will 
// be used for the compare A value
//
// ADC_BUF_LEN is the number of samples we will gather before
// stopping.
//
// FILTER_LEN is the FIR filter length


#define ADC_SAMPLE_PERIOD	1499 
#define PWM_PERIOD		    30000   
#define PWM_DUTY_CYCLE		15000	
#define ADC_BUF_LEN         200     

// 
// Prototype statements for functions found within this file.
// These are used to init the peripherals used in this example
//

void init_epwm1(void);
void init_epwm3(void);
void init_cla(void);
void init_adc(void);

// 
// Prototype statements for __interrupt functions found within
// this file.  The main CPU will service this __interrupt every
// every time task 7 completes.
//

__interrupt void cla1_isr7(void);


// 
// Global variables used in this example:
//
// SampleCount The current sample
//
// 
// AdcBuf      holds a log of the raw ADC RESULT register
//             values as read by the main CPU
//
// ADCFiltBuf  holds a log of the CLA filter output
//             as passed from the CLA to the main CPU through
//             the message RAM
//

Uint16 SampleCount;
Uint16 AdcBuf[ADC_BUF_LEN];
Uint16 AdcFiltBuf[ADC_BUF_LEN];

//
// The DATA_SECTION pragma statements are used to place the
// variables in specific assembly sections.  These sections
// are linked to the message RAMs for the CLA in the
// linker command (.cmd) file.
//
// The following will be placed in the CLA to CPU
// message RAM.  The CLA can write to and read from
// this RAM.  The main CPU can only read from it
//
// X is the filter sample delay line.  These will 
// be populated by the CLA from the ADC RESULT1 register
//
// VoltFilt is the output from the CLA after the FIR filter
// Basically it is the filtered value
//
  
#pragma DATA_SECTION(X,          "Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(VoltFilt,   "Cla1ToCpuMsgRAM");

float32 X[FILTER_LEN];
Uint16 VoltFilt;


// The following will be placed in the CPU to CLA
// message RAM.  The main CPU can write to and read from
// this RAM.  The CLA can only read from it
//
// A is the filter coefficients passed by the main 
// CPU to the CLA. 
//

#pragma DATA_SECTION(A,          "CpuToCla1MsgRAM");

#if LOWPASS
float32 A [FILTER_LEN] = {0.0625L, 0.25L, 0.375L, 0.25L, 0.0625L};	    
#elif HIGHPASS
float32 A [FILTER_LEN] = {0.0625L, -0.25L, 0.375L, -0.25L, 0.0625L};	
#endif

//
// These are defined by the linker file and used to copy
// the CLA code from its load address to its run address
// in CLA program memory in the CLA initalization function
//

main()
{

   Uint16 i;

//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2805x_SysCtrl.c file.
//

   InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2805x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
//

    InitGpio();

//    
// Specific setup for this example:
//
    
    EALLOW;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;	  // GPIO34 is an output (connected to LED on F28027 ControlStick)
	GpioDataRegs.GPBSET.bit.GPIO34 = 1;	  // GPIO34 pin is set to 1 (turn LED on)
	GpioCtrlRegs.GPADIR.bit.GPIO18 = 1;	  // GPIO19 is an output (used for test - pin toggle)
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // 0=GPIO         1=EPWM2A     2=rsvd       3=COMP1OUT
    EDIS;  
     

//
// Step 3. Clear all __interrupts and initialize PIE vector table:
// Disable CPU __interrupts
//

   DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE __interrupts disabled and flags
// are cleared.
// This function is found in the F2805x_PieCtrl.c file.
//

   InitPieCtrl();

//
// Disable CPU __interrupts and clear all CPU __interrupt flags:
//
   IER = 0x0000;
   IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the __interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2805x_DefaultIsr.c.
// This function is found in F2805x_PieVect.c.
//

   InitPieVectTable();

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
// EALLOW: is needed to write to EALLOW protected registers
// EDIS: is needed to disable write to EALLOW protected registers
//

   EALLOW;  
   PieVectTable.CLA1_INT7 = &cla1_isr7;   
   EDIS;    

//
// Step 4. Initialize all the Device Peripherals:
// This function is found in F2805x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
//
//
// Step 5. User specific code, enable __interrupts:
//

//
// Enable INT 11.8 in the PIE (CLA Task8)
// Enable INT 11 at the CPU level
// Enable Global __interrupts with INTM
// Enable Global realtime __interrupts with DBGM
//
 
   PieCtrlRegs.PIEIER11.bit.INTx7 = 1;      
   IER |= M_INT11;                         
   EINT;          						   
   ERTM;          						   

   //
   // Clear the output buffers
   //
      
   for (i = 0; i< ADC_BUF_LEN; i++)
   {
       AdcBuf[i] = 0x0000;
       AdcFiltBuf[i] = 0x0000;
   } 

   init_cla();  
   init_adc();
            
              
   //                                         
   // Assumes ePWM1 clock is already enabled in InitSysCtrl();
   // 
   // Before configuring the ePWMs, halt the counters
   // After configuration they can all be started again
   // in syncronization by setting this bit.
   //

   EALLOW;					   
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
   EDIS;

   init_epwm1();
   init_epwm3();

   //
   // Start the ePWM counters                   
   // Note: this should be done after all ePWM modules are configured
   // to ensure synchronization between the ePWM modules.
   //

   EALLOW;
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
   EDIS;

   //
   // The main CPU will recieve an __interrupt from the 
   // CLA each time task 7 (CLA FIR filter) completes 
   //
   // In the meantime the main CPU can do other work
   //
   // After the CLA has fired ADC_BUF_LEN __interrupts, 
   // the main CPU  will halt here 
   //
   // You can view the results by graphing AdcBuf and
   // AdcFiltBuf.  Both are unsigned int arrays. 
   //

   SampleCount = 0; 
   for(;;)
   {
      if(SampleCount == ADC_BUF_LEN-1)
	  {
         asm(" ESTOP0");
	  }
   }

}

//=============================================================
//
// ISR for Task 2
//
// This __interrupt will be taken by the main CPU when CLA task 7 
// completes.
//
//=============================================================

__interrupt void cla1_isr7()
{
    // 
    // Clear the ADC __interrupt flag so the next SOC can occur
	// Clear the IACK bits so another __interrupt
	// can be taken
	// Toggle GPIO for status
	//

    AdcRegs.ADCINTFLGCLR.bit.ADCINT7 = 1;       
    PieCtrlRegs.PIEACK.all = 0xFFFF;
	GpioDataRegs.GPATOGGLE.bit.GPIO18 = 1;		
    
    //
    // Read the raw ADC RESULT1 register value and
    // put it into the AdcBuf buffer
    // This can be compared to the CLA filtered value
    //   

       AdcBuf[SampleCount] = AdcResult.ADCRESULT1;
   
    //
    // Read the CLA filtered value and put it in the
    // AdcFiltBuf buffer
    //
    
	  AdcFiltBuf[SampleCount] = VoltFilt;    

    //
    // Make sure that the buffer does not overflow
    // the buffer size.  If it is larger than ADC_BUF_LEN
    // then rewind back to the sample 0
    //
	
    SampleCount++;
	if( SampleCount == ADC_BUF_LEN )
	{	
		SampleCount = 0;
	}
}

//=============================================================
//
// Function init_adc()
//
//
// EPWM1 will be used to generate the ADC
// Start of conversion
//
//=============================================================

void init_adc(void)
{

   // Assumes ADC clock is already enabled in InitSysCtrl();

   // 
   // Call the InitAdc function in the F2805x_Adc.c file
   //
   // This function calibrates and powers up the ADC to 
   // into a known state.
   //
   InitAdc();  
   
   //
   // Specific ADC configuration for this example
   //
   // ADC __interrupt will trigger early - before the ADC conversion starts
   // Enable ADCINT2
   // Disable ADC 2 continuous mode
   // Set the SOC1 channel select to ADCINTA7.  
   // After the This __interrupt triggers task 7
   // which is where the CLA FIR filter is located
   // Set the S


   EALLOW;

   //
   // ADC __interrupt comes early (end of sample window)
   // SOC1 will trigger ADCINT7
   // Enable ADCINT7
   // Disable ADCINT7 Continuous mode	    
   //
   
   AdcRegs.ADCCTL1.bit.INTPULSEPOS = 0;
   AdcRegs.INTSEL7N8.bit.INT7SEL   = 1;
   AdcRegs.INTSEL7N8.bit.INT7E     = 1;	    
   AdcRegs.INTSEL7N8.bit.INT7CONT  = 0;
   
   //
   // set SOC1 channel select to ADCINA7
   // set SOC1 start trigger on EPWM1A __interrupt  	    
   // set SOC1 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
   //

   AdcRegs.ADCSOC1CTL.bit.CHSEL    = 7;     
   AdcRegs.ADCSOC1CTL.bit.TRIGSEL  = 5;     
   AdcRegs.ADCSOC1CTL.bit.ACQPS    = 6;	    
   EDIS;
}          


//=============================================================
//
// Function init_epwm1()
//
//
// EPWM1 will be used to generate the ADC
// Start of conversion
//
//=============================================================

void init_epwm1(void)
{

   //
   // EALLOW: is needed to write to EALLOW protected registers
   // EDIS: is needed to disable write to EALLOW protected registers   
   //
   // Enable start of conversion (SOC) on A
   // An SOC event will occur when the ePWM counter is zero
   // The ePWM will generate an SOC on the first event
   // 

   EALLOW;

   //
   // Set the period for ePWM1  
   // By default TBPRD = 1/2 SYSCLKOUT 
   // Set the counter for up count mode
   //

   EPwm1Regs.TBPRD 				= ADC_SAMPLE_PERIOD;  
   EPwm1Regs.TBCTL.bit.CTRMODE 	= TB_COUNT_UP;	   
   EPwm1Regs.ETSEL.bit.SOCAEN	= 1;	   
   EPwm1Regs.ETSEL.bit.SOCASEL	= ET_CTR_ZERO;	   
   EPwm1Regs.ETPS.bit.SOCAPRD 	= ET_1ST;	   

   //
   // For testing - monitor the EPWM1A output
   // which toggles once every ePWM period (i.e
   // at the start of conversion)
   //
   
   GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
   EPwm1Regs.AQCTLA.bit.ZRO = AQ_TOGGLE;
   EPwm1Regs.TBCTL.bit.FREE_SOFT = 3;     

   EDIS;
}


//=============================================================
//
// Function init_epwm3()
//
//=============================================================
void init_epwm3(void)
{

    // EALLOW: is needed to write to EALLOW protected registers
    // EDIS: is needed to disable write to EALLOW protected registers
    // Configure the GPIO4 pin to be EPWM4A output

    EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;
    EDIS;

    //
    // Disable the timer (counter mode is halt)
	// Set the free/soft emulation bits to ignore the
	// emulation halt (PWM will continue to count when
	// the CPU is halted)
    //

	EPwm3Regs.TBCTL.bit.CTRMODE = 0x3;		
    EPwm3Regs.TBCTL.bit.FREE_SOFT = 3; 

	//
	// Clear the counter
	// Set the period and timer phase
	// Specify when the compare A event will occur
    //

	EPwm3Regs.TBCTR = 0x0000;			   
	EPwm3Regs.TBPRD = PWM_PERIOD;	   
	EPwm3Regs.TBPHS.half.TBPHS = 0x0000;   
    EPwm3Regs.CMPA.half.CMPA = PWM_DUTY_CYCLE;

	//
    // On compare A, when counting up, pull the EPWM A output high
	// On compare A, when counting down, pull the EPWM A outpout low
	// Set the counter to up/down count mode
    //

    EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;
	EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;		

} 


//=============================================================
//
// Function init_cla()
//
// CLA module initialization
// 1) Enable the CLA clock
// 2) Init the CLA __interrupt vectors
// 3) Allow the IACK instruction to flag a CLA __interrupt/start a task
//    This is used to force Task 8 in this example
// 4) Copy CLA code from its load address to CLA program RAM
//
//    Note: during debug the load and run addresses could be 
//    the same as Code Composer Studio can load the CLA program
//    RAM directly. 
// 
//    The ClafuncsLoadStart, ClafuncsLoadEnd, and ClafuncsRunStart
//    symbols are created by the linker. 
// 4) Assign CLA program memory to the CLA
// 5) Enable CLA __interrupts (MIER)
//
//=============================================================

void init_cla()
{

   //
   // This code assumes the CLA clock is already enabled in 
   // the call to InitSysCtrl();
   //
   // EALLOW: is needed to write to EALLOW protected registers
   // EDIS: is needed to disable write to EALLOW protected registers
   //
   // Initalize the __interrupt vectors for Task 7 (CLA FIR Filter)
   // and for Task 8 (FIR filter initalization)
   //
   // The symbols used in this calculation are defined in the CLA 
   // assembly code and in the CLAShared.h header file
   //

   EALLOW;
   Cla1Regs.MVECT7 = (Uint16) (&Cla1Task7 - &Cla1Prog_Start)*sizeof(Uint32);
   Cla1Regs.MVECT8 = (Uint16) (&Cla1Task8 - &Cla1Prog_Start)*sizeof(Uint32);

   //
   // Task 7 has the option to be started by either EPWM7_INT or ADCINT7 
   // In this case we will allow ADCINT7 to start CLA Task 7
   //
   
   Cla1Regs.MPISRCSEL1.bit.PERINT7SEL = CLA_INT7_ADCINT7; 
   
   // 
   // Copy the CLA program code from its load address to the CLA program memory
   // Once done, assign the program memory to the CLA
   //
   // Make sure there are at least two SYSCLKOUT cycles between assigning
   // the memory to the CLA and when an __interrupt comes in
   //
   
   memcpy(&Cla1funcsRunStart,&Cla1funcsLoadStart, (Uint32)&Cla1funcsLoadSize); 
   Cla1Regs.MMEMCFG.bit.PROGE = 1;
      
   //
   // Enable the IACK instruction to start a task
   // Enable the CLA __interrupt 8 and __interrupt 2
   //     
   
   Cla1Regs.MCTL.bit.IACKE = 1;            
   Cla1Regs.MIER.all = (M_INT8 | M_INT7);

   //
   // Force CLA task 8 using the IACK instruction
   // Task 8 will initalize the filter input delay
   // line to zero (X[0] - X[4]). 
   //
   // No need to wait, the task will finish by the time
   // we configure the ePWM and ADC modules
   //

   Cla1ForceTask8(); 

}
