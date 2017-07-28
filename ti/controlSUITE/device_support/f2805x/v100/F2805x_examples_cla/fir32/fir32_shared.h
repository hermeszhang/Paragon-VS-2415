//###########################################################################
// Description:
//
// Declare shared variables
//
//###########################################################################
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//###########################################################################

#ifndef FIR32_SHARED_H_
#define FIR32_SHARED_H_
#ifdef __cplusplus
extern "C" {
#endif

//Task 1 (C) Variables
#define FILTER_LEN    5
#define INPUT_LEN     128
#define OUTPUT_LEN    INPUT_LEN+FILTER_LEN

extern float fCoeffs[];
extern long xAdcInput;
extern long xResult;
extern float fDelayLine[];
extern unsigned long fir_output[];
extern unsigned long adc_input[];

//Task 2 (C) Variables

//Task 3 (C) Variables

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables

//CLA C Tasks
__interrupt void Cla1Task1();
__interrupt void Cla1Task2();
__interrupt void Cla1Task3();
__interrupt void Cla1Task4();
__interrupt void Cla1Task5();
__interrupt void Cla1Task6();
__interrupt void Cla1Task7();
__interrupt void Cla1Task8();

//C Function Prototypes
void test_run();
void test_report();

#ifdef __cplusplus
}
#endif /* extern "C" */
#endif /*FIR32_SHARED_H_*/
