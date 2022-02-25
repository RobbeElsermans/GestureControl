################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_calibration.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_core.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_debug.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_preset_modes.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_core.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_core_support.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_dmax.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_algos_gen3.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_algos_gen4.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_char.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_core.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_funcs.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_nvm.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_nvm_debug.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_register_funcs.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_sigma_estimate.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_silicon_core.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_wait.c \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_xtalk.c 

OBJS += \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_calibration.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_core.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_debug.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_preset_modes.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_core.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_core_support.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_dmax.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_algos_gen3.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_algos_gen4.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_char.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_core.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_funcs.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_nvm.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_nvm_debug.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_register_funcs.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_sigma_estimate.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_silicon_core.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_wait.o \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_xtalk.o 

C_DEPS += \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_calibration.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_core.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_debug.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_preset_modes.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_core.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_core_support.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_dmax.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_algos_gen3.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_algos_gen4.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_char.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_core.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_funcs.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_nvm.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_nvm_debug.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_register_funcs.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_sigma_estimate.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_silicon_core.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_wait.d \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_xtalk.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/%.o: ../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/%.c Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/robel/GitHub/GestureControl/Code 2.0/GestureControl/Drivers/VL53L3CX_API_1.2.8" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-example-2f-Drivers-2f-BSP-2f-Components-2f-vl53l3cx

clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-example-2f-Drivers-2f-BSP-2f-Components-2f-vl53l3cx:
	-$(RM) ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_calibration.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_calibration.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_core.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_core.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_debug.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_debug.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_preset_modes.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_api_preset_modes.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_core.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_core.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_core_support.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_core_support.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_dmax.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_dmax.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_algos_gen3.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_algos_gen3.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_algos_gen4.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_algos_gen4.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_char.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_char.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_core.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_core.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_funcs.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_hist_funcs.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_nvm.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_nvm.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_nvm_debug.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_nvm_debug.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_register_funcs.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_register_funcs.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_sigma_estimate.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_sigma_estimate.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_silicon_core.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_silicon_core.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_wait.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_wait.o ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_xtalk.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/Components/vl53l3cx/vl53lx_xtalk.o

.PHONY: clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-example-2f-Drivers-2f-BSP-2f-Components-2f-vl53l3cx

