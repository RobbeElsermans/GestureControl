################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_calibration.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_core.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_debug.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_preset_modes.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_core.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_core_support.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_dmax.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_algos_gen3.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_algos_gen4.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_char.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_core.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_funcs.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_nvm.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_nvm_debug.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_register_funcs.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_sigma_estimate.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_silicon_core.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_wait.c \
../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_xtalk.c 

OBJS += \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_calibration.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_core.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_debug.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_preset_modes.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_core.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_core_support.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_dmax.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_algos_gen3.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_algos_gen4.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_char.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_core.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_funcs.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_nvm.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_nvm_debug.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_register_funcs.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_sigma_estimate.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_silicon_core.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_wait.o \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_xtalk.o 

C_DEPS += \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_calibration.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_core.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_debug.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_preset_modes.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_core.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_core_support.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_dmax.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_algos_gen3.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_algos_gen4.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_char.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_core.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_funcs.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_nvm.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_nvm_debug.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_register_funcs.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_sigma_estimate.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_silicon_core.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_wait.d \
./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_xtalk.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/vl53l3cx/modules/%.o: ../Drivers/BSP/Components/vl53l3cx/modules/%.c Drivers/BSP/Components/vl53l3cx/modules/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../X-CUBE-TOF1/Target -I../Drivers/BSP/53L3A2 -I../Drivers/BSP/Components/vl53l3cx/modules -I../Drivers/BSP/Components/vl53l3cx/porting -I../Drivers/BSP/Components/vl53l3cx -I../Drivers/BSP/Components/Common -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-vl53l3cx-2f-modules

clean-Drivers-2f-BSP-2f-Components-2f-vl53l3cx-2f-modules:
	-$(RM) ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_calibration.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_calibration.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_core.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_core.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_debug.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_debug.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_preset_modes.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_preset_modes.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_core.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_core.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_core_support.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_core_support.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_dmax.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_dmax.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_algos_gen3.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_algos_gen3.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_algos_gen4.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_algos_gen4.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_char.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_char.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_core.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_core.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_funcs.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_funcs.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_nvm.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_nvm.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_nvm_debug.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_nvm_debug.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_register_funcs.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_register_funcs.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_sigma_estimate.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_sigma_estimate.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_silicon_core.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_silicon_core.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_wait.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_wait.o ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_xtalk.d ./Drivers/BSP/Components/vl53l3cx/modules/vl53lx_xtalk.o

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-vl53l3cx-2f-modules

