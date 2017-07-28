//###########################################################################
// Description:
//
// Call Task 1 in a loop and feed it test inputs
//
//###########################################################################
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//###########################################################################

#include "DSP28x_Project.h"
#include "F2805x_Cla_defines.h"  
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
#include XSTRINGIZE(XCONCAT(TEST_NAME,_shared.h))


void test_run(void)
{
	int i;
	
	for(i=0;i<BUFFER_SIZE;i++)
	{
	 Num = (float)(BUFFER_SIZE - i);
	 Den = (float)(BUFFER_SIZE + i);
	 Cla1ForceTask1andWait();
	 y[i] = Res; 
	}   

#if 0
    Cla1ForceTask2andWait();

    Cla1ForceTask3andWait();

    Cla1ForceTask4andWait();

    Cla1ForceTask5andWait();

    Cla1ForceTask6andWait();

    Cla1ForceTask7andWait();

    Cla1ForceTask8andWait();
#endif
}
