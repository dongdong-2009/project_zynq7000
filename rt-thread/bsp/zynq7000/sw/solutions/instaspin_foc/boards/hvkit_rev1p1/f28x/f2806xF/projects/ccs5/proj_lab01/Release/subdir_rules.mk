################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
adc.obj: D:/ti/motorware/motorware_1_01_00_16/sw/drivers/adc/src/32b/f28x/f2806x/adc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="adc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

clk.obj: D:/ti/motorware/motorware_1_01_00_16/sw/drivers/clk/src/32b/f28x/f2806x/clk.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="clk.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cpu.obj: D:/ti/motorware/motorware_1_01_00_16/sw/drivers/cpu/src/32b/f28x/f2806x/cpu.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="cpu.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

flash.obj: D:/ti/motorware/motorware_1_01_00_16/sw/drivers/flash/src/32b/f28x/f2806x/flash.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="flash.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

gpio.obj: D:/ti/motorware/motorware_1_01_00_16/sw/drivers/gpio/src/32b/f28x/f2806x/gpio.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="gpio.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

hal.obj: D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/hal.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="hal.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

osc.obj: D:/ti/motorware/motorware_1_01_00_16/sw/drivers/osc/src/32b/f28x/f2806x/osc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="osc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pie.obj: D:/ti/motorware/motorware_1_01_00_16/sw/drivers/pie/src/32b/f28x/f2806x/pie.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="pie.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pll.obj: D:/ti/motorware/motorware_1_01_00_16/sw/drivers/pll/src/32b/f28x/f2806x/pll.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="pll.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

proj_lab01.obj: D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/src/proj_lab01.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="proj_lab01.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pwm.obj: D:/ti/motorware/motorware_1_01_00_16/sw/drivers/pwm/src/32b/f28x/f2806x/pwm.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="pwm.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pwr.obj: D:/ti/motorware/motorware_1_01_00_16/sw/drivers/pwr/src/32b/f28x/f2806x/pwr.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="pwr.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

timer.obj: D:/ti/motorware/motorware_1_01_00_16/sw/drivers/timer/src/32b/f28x/f2806x/timer.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="timer.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usDelay.obj: D:/ti/motorware/motorware_1_01_00_16/sw/modules/usDelay/src/32b/f28x/usDelay.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="usDelay.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

user.obj: D:/ti/motorware/motorware_1_01_00_16/sw/modules/user/src/32b/user.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="user.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

wdog.obj: D:/ti/motorware/motorware_1_01_00_16/sw/drivers/wdog/src/32b/f28x/f2806x/wdog.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2806x/src/" --include_path="D:/ti/motorware/motorware_1_01_00_16/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2806xF/src" --include_path="D:/ti/motorware/motorware_1_01_00_16" -g --define=FAST_ROM_V1p6 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="wdog.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


