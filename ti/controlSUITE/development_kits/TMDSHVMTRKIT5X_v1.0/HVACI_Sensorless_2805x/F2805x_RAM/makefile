################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/c2000_6.1.0

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./HVACI_Sensorless.obj" \
"./HVACI_Sensorless-DevInit_F2805x.obj" \
"./F2805x_usDelay.obj" \
"./F2805x_GlobalVariableDefs.obj" \
"./F2805x_CodeStartBranch.obj" \
"./DLOG4CHC.obj" \
-l"rts2800_ml.lib" \
"../2805x_RAM_HVACI_Sensorless.cmd" \
"../F2805x_Headers_nonBIOS.cmd" \
"C:/ti/controlSUITE/libs/math/IQmath/v15c/lib/IQmath.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: HVACI_Sensorless_2805x.out

# Tool invocations
HVACI_Sensorless_2805x.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --diag_warning=225 -z --stack_size=0x380 -m"HVACI_Sensorless_2805x.map" --warn_sections -i"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/lib" -i"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" -i"C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/development_kits/TMDSHVMTRKIT5X_v1.0/HVACI_Sensorless_2805x" --reread_libs --rom_model -o "HVACI_Sensorless_2805x.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C2000_EXECUTABLE_OUTPUTS__QUOTED) "HVACI_Sensorless_2805x.out"
	-$(RM) "F2805x_GlobalVariableDefs.pp" "HVACI_Sensorless-DevInit_F2805x.pp" "HVACI_Sensorless.pp" 
	-$(RM) "DLOG4CHC.obj" "F2805x_CodeStartBranch.obj" "F2805x_GlobalVariableDefs.obj" "F2805x_usDelay.obj" "HVACI_Sensorless-DevInit_F2805x.obj" "HVACI_Sensorless.obj" 
	-$(RM) "DLOG4CHC.pp" "F2805x_CodeStartBranch.pp" "F2805x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
