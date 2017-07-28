//###########################################################################
// Description:
//
// Compare observed output against expected output vector and print a 
// PASS/FAIL report to the console
//
//###########################################################################
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//###########################################################################

#include <stdio.h>
#include <math.h>
#include "DSP28x_Project.h"
#include "F2805x_Cla_defines.h"  
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
#include XSTRINGIZE(XCONCAT(TEST_NAME,_shared.h))

void test_report(void)
{
	      	
   int32 i, j, index;
   int fail_flag;
   int32 gold_out[LENGTH];   
   fail_flag = 0;
   index = 2;
   gold_out[0] = 1;
   gold_out[1] = 2;
   
//
// For the rest of the numbers, skip evens
//       
   for ( i = 3; index < LENGTH; i+=2 )
   {
      for ( j = 2; j <= i/2; j++ )
      {
         if ( ! (i % j) ) break;
      }
      if ( j > i / 2 ) 
      {
      	gold_out[index] = i;
      	index++;
      }
   }
 
     // 
    // Map the data memory back to the CPU so we can check the
    // results
    //    
    EALLOW;
    Cla1Regs.MMEMCFG.bit.RAM0E	= 0;
    Cla1Regs.MMEMCFG.bit.RAM1E	= 0;
    EDIS;
  asm("   NOP");
  asm("   NOP");
  asm("   NOP");
  asm("   NOP");    
 
    for(i = 0; i<LENGTH;i++)
    {
        if(out[i] != gold_out[i]) 
        {
        	fail_flag = 1;
        }
    }
	
    if(fail_flag == 0) puts("PASS\n");
    else
       printf("FAIL  fail_flag = 0x%d\n",fail_flag);
}


