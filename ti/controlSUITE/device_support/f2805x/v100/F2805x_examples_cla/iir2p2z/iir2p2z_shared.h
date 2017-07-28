//###########################################################################
// Description:
//
// Declare shared variables
//
//###########################################################################
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//###########################################################################

#ifndef IIR2P2Z_SHARED_H_
#define IIR2P2Z_SHARED_H_

#ifdef __cplusplus
extern "C" {
#endif

//Task 1 (C) Variables
#define NUM_SAMPLES	128
extern float S1_B[];
extern float S1_A[];
extern float xn; //Sample input
extern float yn; //Sample output
extern float fAdcInput[];
extern float fBiquadOutput[];
extern float fAdcInput[];

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
#endif /*IIR2P2Z_SHARED_H_*/
