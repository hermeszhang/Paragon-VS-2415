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
	unsigned int i;
	Uint16 fail_flag = 0x0000;
	
    if(index1 != 6 || max1 != 13.2) fail_flag = fail_flag | M_INT1;
    if(index2 != 4 || max2 != -2.5) fail_flag = fail_flag | M_INT2;
    if(index3 != 0 || max3 != 12.2) fail_flag = fail_flag | M_INT3; 
    if(max4 != 9.9 || min4 != -8.8) fail_flag = fail_flag | M_INT4;       
    if(fail_flag == 0) puts("Pass\n");
    else
       printf("FAIL  fail_flag = 0x%d\n",fail_flag);

}
