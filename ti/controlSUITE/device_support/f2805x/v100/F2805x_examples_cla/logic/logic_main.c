//###########################################################################
// Description:
//! \addtogroup f2806x_example_cla_list
//! <h1> Logic Test </h1>
//!
//! In this example, Task 1 of the CLA impements a set of
//! logic tests. More information about these logic statements can be
//! found at:
//! http://graphics.stanford.edu/~seander/bithacks.html#OperationCounting
//!
//! \b Watch \b Variables \n
//! - cla_pass_count - Logic test pass count
//! - cla_fail_count - Logic test fail count
//
//###########################################################################
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//###########################################################################

#include "DSP28x_Project.h"     // DSP28x Headerfile
#include "F2805x_Cla_defines.h"  
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
#include XSTRINGIZE(XCONCAT(TEST_NAME,_shared.h))

#define CLARAM0_ENABLE	1
#define CLARAM1_ENABLE	1
#define CLARAM2_ENABLE	1

#define HARDWARE 1


// Constants
#define OSCCLK	     (10000000UL) 	         // < Internal OSC frequency
#define SYSCLK	     (80000000UL) 			 // < System Clock frequency
#define PER_CLK_DIV  (4)					 // < Low speed peripheral clock dividers
#define PER_CLK	     (SYSCLK/PER_CLK_DIV)	 // < Low speed peripheral clock
#define DIV_SEL	     (2)		             // < Clock divider selection
#define CLK_DIV	     ((SYSCLK * DIV_SEL)/OSCCLK) // < Clock divider


//CLA ISRs
__interrupt void cla1_task1_isr( void );
__interrupt void cla1_task2_isr( void );
__interrupt void cla1_task3_isr( void );
__interrupt void cla1_task4_isr( void );
__interrupt void cla1_task5_isr( void );
__interrupt void cla1_task6_isr( void );
__interrupt void cla1_task7_isr( void );
__interrupt void cla1_task8_isr( void );

//Linker defined vars
extern Uint16 Cla1Prog_Start;
extern Uint16 Cla1funcsLoadStart;
extern Uint16 Cla1funcsLoadEnd;
extern Uint16 Cla1funcsRunStart;
extern Uint16 Cla1funcsLoadSize;
extern Uint16 Cla1mathTablesLoadStart;
extern Uint16 Cla1mathTablesRunStart;
extern Uint16 Cla1mathTablesLoadSize;

//  Main Function
void main(void)
{
   //  Step 1: Setup the system clock
   /*  Disable the watchdog timer, initialize the system clock,
    *  PLL and configure the peripheral clock. 
    */
   InitSysCtrl();
	
   //  Step 2: Initialize PIE control
   /*  Intialize PIE control, disable all __interrupts and
    * then copy over the PIE Vector table from BootROM to RAM
    */
   DINT;
   InitPieCtrl();
   IER = 0x00000000;
   IFR = 0x00000000;
   InitPieVectTable();
	
   /*  Assign user defined ISR to the PIE vector table */
	EALLOW;
   PieVectTable.CLA1_INT1  = &cla1_task1_isr;
   PieVectTable.CLA1_INT2  = &cla1_task2_isr;
   PieVectTable.CLA1_INT3  = &cla1_task3_isr;
   PieVectTable.CLA1_INT4  = &cla1_task4_isr;
   PieVectTable.CLA1_INT5  = &cla1_task5_isr;
   PieVectTable.CLA1_INT6  = &cla1_task6_isr;
   PieVectTable.CLA1_INT7  = &cla1_task7_isr;
   PieVectTable.CLA1_INT8  = &cla1_task8_isr;
	EDIS;

   //Copy over the CLA code and Tables
   memcpy(&Cla1funcsRunStart, &Cla1funcsLoadStart, (Uint32)&Cla1funcsLoadSize);
   memcpy(&Cla1mathTablesRunStart, &Cla1mathTablesLoadStart, (Uint32)&Cla1mathTablesLoadSize);   
	
   /*  Compute all CLA task vectors */ 
    EALLOW;
    Cla1Regs.MVECT1 = ((Uint16)Cla1Task1 - (Uint16)&Cla1Prog_Start);
    Cla1Regs.MVECT2 = ((Uint16)Cla1Task2 - (Uint16)&Cla1Prog_Start);
    Cla1Regs.MVECT3 = ((Uint16)Cla1Task3 - (Uint16)&Cla1Prog_Start);
    Cla1Regs.MVECT4 = ((Uint16)Cla1Task4 - (Uint16)&Cla1Prog_Start);
    Cla1Regs.MVECT5 = ((Uint16)Cla1Task5 - (Uint16)&Cla1Prog_Start);
    Cla1Regs.MVECT6 = ((Uint16)Cla1Task6 - (Uint16)&Cla1Prog_Start);
    Cla1Regs.MVECT7 = ((Uint16)Cla1Task7 - (Uint16)&Cla1Prog_Start);
    Cla1Regs.MVECT8 = ((Uint16)Cla1Task8 - (Uint16)&Cla1Prog_Start);
    EDIS;
   
    //  Step 3 : Mapping CLA tasks
    /*  All tasks are enabled and will be started by an ePWM trigger
     *  Map CLA program memory to the CLA and enable software breakpoints
     */
    EALLOW;
	Cla1Regs.MPISRCSEL1.bit.PERINT1SEL 	= CLA_INT1_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT2SEL 	= CLA_INT2_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT3SEL 	= CLA_INT3_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT4SEL 	= CLA_INT4_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT5SEL 	= CLA_INT5_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT6SEL 	= CLA_INT6_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT7SEL 	= CLA_INT7_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT8SEL 	= CLA_INT8_NONE;
	Cla1Regs.MIER.all 		 		    = 0x00FF;
	EDIS;	
    
 
    /*  Enable CLA __interrupts at the group and subgroup levels */
    PieCtrlRegs.PIEIER11.all       = 0xFFFF;
    IER = (M_INT11 );
    EINT;   // Enable Global __interrupt INTM
    ERTM;   // Enable Global realtime __interrupt DBGM

    /* Switch the CLA program space to the CLA and enable software forcing
     * Also switch over CLA data ram 0 and 1
     */
    EALLOW;
    Cla1Regs.MMEMCFG.bit.PROGE 	= 1;
    Cla1Regs.MMEMCFG.bit.RAM1CPUE = 1;
    Cla1Regs.MCTL.bit.IACKE	= 1;
    Cla1Regs.MMEMCFG.bit.RAM0E	= CLARAM0_ENABLE;
    Cla1Regs.MMEMCFG.bit.RAM1E	= CLARAM1_ENABLE;
    Cla1Regs.MMEMCFG.bit.RAM2E	= CLARAM2_ENABLE;
    EDIS;	

    // Invoke Task(s)
    test_run();

    // Report Results
    test_report();

#if HARDWARE
{__asm(" ESTOP0");}
#endif
}

//###########################################################################
// CLA ISRs
//###########################################################################
__interrupt void cla1_task1_isr( void)
{
        PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task2_isr( void)
{
        PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task3_isr( void)
{
        PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task4_isr( void)
{
        PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task5_isr( void)
{
        PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task6_isr( void)
{
        PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task7_isr( void)
{
        PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task8_isr( void)
{
        PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

