//###########################################################################
//
// FILE:   F2805x_TempSensorConv.c
//
// TITLE:  F2805x ADC Temperature Sensor Conversion Functions
//
// This file contains funcions necessary to convert the temperature sensor
// reading into degrees C or K.
//
// This program makes use of variables stored in OTP during factory
// test on 2805x TMS devices only.
// These OTP locations on pre-TMS devices may not be populated.
// Ensure that the following memory locations in TI OTP are populated
// (not 0xFFFF) before use:
//
// 0x3D7E90 to 0x3D7EA4
//
// Note that these functions pull data from the OTP by calling functions which
// reside in OTP.  Therefore the OTP wait-states (controlled by
// FlashRegs.FOTPWAIT.bit.OTPWAIT) will significantly affect the time required
// to execute these functions.
//
//###########################################################################
// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
// $Release Date: November 30, 2011 $
//###########################################################################

#include "F2805x_Device.h"     // F2805x Headerfile Include File
#include "F2805x_Examples.h"   // F2805x Examples Include File

// Useful definitions
  #define FP_SCALE 32768       //Scale factor for Q15 fixed point numbers (2^15)
  #define FP_ROUND FP_SCALE/2  //Added to Q15 numbers before converting to integer to round the number

// Amount to add to Q15 fixed point numbers to shift from Celsius to Kelvin
// (Converting guarantees number is positive, which makes rounding more efficient)
  #define KELVIN 273
  #define KELVIN_OFF FP_SCALE*KELVIN


// The folloing pointers to function calls are:
//Slope of temperature sensor (deg. C / ADC code).  Stored in fixed point Q15 format.
  #define getTempSlope() (*(int (*)(void))0x3D7E3A)()
//ADC code corresponding to temperature sensor output at 0 deg. C
  #define getTempOffset() (*(int (*)(void))0x3D7E3D)()

//This function uses the reference data stored in OTP to convert the raw temperature
//sensor reading into degrees C
int16 GetTemperatureC(int16 sensorSample)
{
    return ((sensorSample - getTempOffset())*(int32)getTempSlope() + FP_ROUND + KELVIN_OFF)/FP_SCALE - KELVIN;
}

//This function uses the reference data stored in OTP to convert the raw temperature
//sensor reading into degrees K
int16 GetTemperatureK(int16 sensorSample)
{
    return ((sensorSample - getTempOffset())*(int32)getTempSlope() + FP_ROUND + KELVIN_OFF)/FP_SCALE;
}





