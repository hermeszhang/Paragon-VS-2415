//###########################################################################
// Description:
//
// Declare shared memory variables and assign them to specific CLA-accessible
// memory locations
//
//! \addtogroup f2806x_example_cla_list
//! \b Memory \b Allocation \n
//!  - CLA1 Data RAM 1 (RAML2)
//!    - vector2 - Input/Output vector for task 2
//!  - CLA1 to CPU Message RAM
//!    - vector1_inverse - Inverse of input vector1
//!  - CPU to CLA1 Message RAM
//!    - vector1 - Input vector to task 1
//
//###########################################################################
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//###########################################################################

#include "DSP28x_Project.h"
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
#include XSTRINGIZE(XCONCAT(TEST_NAME,_shared.h))

//GLobal Data
 //Ensure that all data is placed in the data rams

//Task 1 (C) Variables
// CLA Input Data
// Note - Vector2 is both input and output
#pragma DATA_SECTION(vector1,"CpuToCla1MsgRAM");
#pragma DATA_SECTION(vector2,"Cla1DataRam1");
float  vector1[5] = {1.0,4.0,8.0,.5,.25};              
float  vector2[10] = {-.25,-.5,-.125,-2.0,-4.0,-8.0,8.0,4.0,.25,.125}; 
// CLA Output Data
#pragma DATA_SECTION(vector1_inverse,"Cla1ToCpuMsgRAM");
float   vector1_inverse[LENGTH1];

//Task 2 (C) Variables

//Task 3 (C) Variables

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables
