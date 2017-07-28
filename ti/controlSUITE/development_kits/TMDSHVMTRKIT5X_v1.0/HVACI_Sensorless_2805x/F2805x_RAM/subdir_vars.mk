################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../2805x_RAM_HVACI_Sensorless.cmd \
../F2805x_Headers_nonBIOS.cmd 

LIB_SRCS += \
C:/ti/controlSUITE/libs/math/IQmath/v15c/lib/IQmath.lib 

ASM_SRCS += \
../DLOG4CHC.asm \
C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_common/source/F2805x_CodeStartBranch.asm \
../F2805x_usDelay.asm 

C_SRCS += \
C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_headers/source/F2805x_GlobalVariableDefs.c \
../HVACI_Sensorless-DevInit_F2805x.c \
../HVACI_Sensorless.c 

OBJS += \
./DLOG4CHC.obj \
./F2805x_CodeStartBranch.obj \
./F2805x_GlobalVariableDefs.obj \
./F2805x_usDelay.obj \
./HVACI_Sensorless-DevInit_F2805x.obj \
./HVACI_Sensorless.obj 

ASM_DEPS += \
./DLOG4CHC.pp \
./F2805x_CodeStartBranch.pp \
./F2805x_usDelay.pp 

C_DEPS += \
./F2805x_GlobalVariableDefs.pp \
./HVACI_Sensorless-DevInit_F2805x.pp \
./HVACI_Sensorless.pp 

C_DEPS__QUOTED += \
"F2805x_GlobalVariableDefs.pp" \
"HVACI_Sensorless-DevInit_F2805x.pp" \
"HVACI_Sensorless.pp" 

OBJS__QUOTED += \
"DLOG4CHC.obj" \
"F2805x_CodeStartBranch.obj" \
"F2805x_GlobalVariableDefs.obj" \
"F2805x_usDelay.obj" \
"HVACI_Sensorless-DevInit_F2805x.obj" \
"HVACI_Sensorless.obj" 

ASM_DEPS__QUOTED += \
"DLOG4CHC.pp" \
"F2805x_CodeStartBranch.pp" \
"F2805x_usDelay.pp" 

ASM_SRCS__QUOTED += \
"../DLOG4CHC.asm" \
"C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_common/source/F2805x_CodeStartBranch.asm" \
"../F2805x_usDelay.asm" 

C_SRCS__QUOTED += \
"C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_headers/source/F2805x_GlobalVariableDefs.c" \
"../HVACI_Sensorless-DevInit_F2805x.c" \
"../HVACI_Sensorless.c" 


