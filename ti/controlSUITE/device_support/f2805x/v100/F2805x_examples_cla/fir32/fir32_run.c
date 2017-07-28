//###########################################################################
// Description:
//
// Call Task 1
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
	for(i=0;i<OUTPUT_LEN;i++){
        if(i< INPUT_LEN){
    	  xAdcInput = adc_input[i];
       	  Cla1ForceTask1andWait();
       	  fir_output[i] = xResult;
        }else{
         fir_output[i] = 0;   
        }
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
