################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.c 

OBJS += \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.o 

C_DEPS += \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/VL53L3CX_API_1.2.8/example/Drivers/STM32F4xx_HAL_Driver/Src/Legacy/%.o: ../Drivers/VL53L3CX_API_1.2.8/example/Drivers/STM32F4xx_HAL_Driver/Src/Legacy/%.c Drivers/VL53L3CX_API_1.2.8/example/Drivers/STM32F4xx_HAL_Driver/Src/Legacy/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/robel/GitHub/GestureControl/Code 2.0/GestureControl/Drivers/VL53L3CX_API_1.2.8" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-example-2f-Drivers-2f-STM32F4xx_HAL_Driver-2f-Src-2f-Legacy

clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-example-2f-Drivers-2f-STM32F4xx_HAL_Driver-2f-Src-2f-Legacy:
	-$(RM) ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.o

.PHONY: clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-example-2f-Drivers-2f-STM32F4xx_HAL_Driver-2f-Src-2f-Legacy

