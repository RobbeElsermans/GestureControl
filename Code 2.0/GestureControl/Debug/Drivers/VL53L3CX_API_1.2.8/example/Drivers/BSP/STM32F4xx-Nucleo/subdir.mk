################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/STM32F4xx-Nucleo/stm32f4xx_nucleo.c 

OBJS += \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/STM32F4xx-Nucleo/stm32f4xx_nucleo.o 

C_DEPS += \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/STM32F4xx-Nucleo/stm32f4xx_nucleo.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/STM32F4xx-Nucleo/%.o: ../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/STM32F4xx-Nucleo/%.c Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/STM32F4xx-Nucleo/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/robel/GitHub/GestureControl/Code 2.0/GestureControl/Drivers/VL53L3CX_API_1.2.8" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-example-2f-Drivers-2f-BSP-2f-STM32F4xx-2d-Nucleo

clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-example-2f-Drivers-2f-BSP-2f-STM32F4xx-2d-Nucleo:
	-$(RM) ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/STM32F4xx-Nucleo/stm32f4xx_nucleo.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/STM32F4xx-Nucleo/stm32f4xx_nucleo.o

.PHONY: clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-example-2f-Drivers-2f-BSP-2f-STM32F4xx-2d-Nucleo

