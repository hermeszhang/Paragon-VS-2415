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
	Uint16 fail_flag = 0x0000;
    Uint16 const gold1 = 0x0043;   
    Uint16 const gold2 = 0x009f;
    Uint16 const gold3 = 0x00CE;
    Uint16 const gold4 = 0x00c0;
                
    if(gold1 != crc8_msg1) fail_flag = 1;
    if(gold2 != crc8_msg2) fail_flag = 2;          
    if(gold3 != crc8_msg3) fail_flag = 3; 
    if(gold4 != crc8_msg4) fail_flag = 4;           
     
    if(fail_flag == 0) puts("PASS\n");
    else
       printf("FAIL  fail_flag = 0x%d\n",fail_flag);

}
