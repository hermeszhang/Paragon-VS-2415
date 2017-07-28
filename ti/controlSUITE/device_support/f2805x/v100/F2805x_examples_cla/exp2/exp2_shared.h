//###########################################################################
// Description:
//
// Declare shared variables
//
//###########################################################################
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//###########################################################################

#ifndef EXP2_SHARED_H_
#define EXP2_SHARED_H_
#ifdef __cplusplus
extern "C" {
#endif

//Task 1 (C) Variables
extern float Num,Den; //A/B user input at the C28x side
extern float ExpRes;  //Final Result used in C28x code

//Task 2 (C) Variables

//Task 3 (C) Variables

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables
//Coefficients in the Taylor series expansion of exp(A/B)
extern float CLAINV1,CLAINV2,CLAINV3,CLAINV4;
extern float CLAINV5,CLAINV6,CLAINV7;
extern float CLAexpTable[];//exponent table defined in Tables_C.c

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
#endif /*EXP2_SHARED_H_*/
