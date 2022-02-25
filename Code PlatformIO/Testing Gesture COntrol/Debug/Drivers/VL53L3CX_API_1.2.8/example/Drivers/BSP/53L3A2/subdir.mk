################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2/53l3a2.c 

OBJS += \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2/53l3a2.o 

C_DEPS += \
./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2/53l3a2.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2/%.o: ../Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2/%.c Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/robel/GitHub/GestureControl/Code 2.0/GestureControl/Drivers/VL53L3CX_API_1.2.8" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-example-2f-Drivers-2f-BSP-2f-53L3A2

clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-example-2f-Drivers-2f-BSP-2f-53L3A2:
	-$(RM) ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2/53l3a2.d ./Drivers/VL53L3CX_API_1.2.8/example/Drivers/BSP/53L3A2/53l3a2.o

.PHONY: clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-example-2f-Drivers-2f-BSP-2f-53L3A2

