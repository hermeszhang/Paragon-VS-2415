################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
DLOG4CHC.obj: ../DLOG4CHC.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/math/IQmath/v15c/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/app_libs/motor_control/drivers/f2805x_v1.0" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_common/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_headers/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/app_libs/motor_control/math_blocks/v4.0" --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --quiet --diag_warning=225 --preproc_with_compile --preproc_dependency="DLOG4CHC.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2805x_CodeStartBranch.obj: C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_common/source/F2805x_CodeStartBranch.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/math/IQmath/v15c/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/app_libs/motor_control/drivers/f2805x_v1.0" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_common/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_headers/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/app_libs/motor_control/math_blocks/v4.0" --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --quiet --diag_warning=225 --preproc_with_compile --preproc_dependency="F2805x_CodeStartBranch.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2805x_GlobalVariableDefs.obj: C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_headers/source/F2805x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/math/IQmath/v15c/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/app_libs/motor_control/drivers/f2805x_v1.0" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_common/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_headers/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/app_libs/motor_control/math_blocks/v4.0" --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --quiet --diag_warning=225 --preproc_with_compile --preproc_dependency="F2805x_GlobalVariableDefs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2805x_usDelay.obj: ../F2805x_usDelay.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/math/IQmath/v15c/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/app_libs/motor_control/drivers/f2805x_v1.0" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_common/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_headers/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/app_libs/motor_control/math_blocks/v4.0" --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --quiet --diag_warning=225 --preproc_with_compile --preproc_dependency="F2805x_usDelay.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

HVACI_Sensorless-DevInit_F2805x.obj: ../HVACI_Sensorless-DevInit_F2805x.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/math/IQmath/v15c/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/app_libs/motor_control/drivers/f2805x_v1.0" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_common/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_headers/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/app_libs/motor_control/math_blocks/v4.0" --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --quiet --diag_warning=225 --preproc_with_compile --preproc_dependency="HVACI_Sensorless-DevInit_F2805x.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

HVACI_Sensorless.obj: ../HVACI_Sensorless.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/math/IQmath/v15c/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/app_libs/motor_control/drivers/f2805x_v1.0" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_common/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/device_support/f2805x/v100/F2805x_headers/include" --include_path="C:/Users/Rick/Desktop/GitHub/Paragon-VS-2415/ti/controlSUITE/libs/app_libs/motor_control/math_blocks/v4.0" --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --quiet --diag_warning=225 --preproc_with_compile --preproc_dependency="HVACI_Sensorless.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


