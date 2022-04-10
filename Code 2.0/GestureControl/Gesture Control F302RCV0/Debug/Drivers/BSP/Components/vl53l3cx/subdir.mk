################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/vl53l3cx/vl53l3cx.c 

OBJS += \
./Drivers/BSP/Components/vl53l3cx/vl53l3cx.o 

C_DEPS += \
./Drivers/BSP/Components/vl53l3cx/vl53l3cx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/vl53l3cx/%.o: ../Drivers/BSP/Components/vl53l3cx/%.c Drivers/BSP/Components/vl53l3cx/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F302xC -c -I"/home/robbe/Desktop/Github/GestureControl/Code 2.0/GestureControl/Gesture Control F302RCV0/Drivers/BSP/Components" -I"/home/robbe/Desktop/Github/GestureControl/Code 2.0/GestureControl/Gesture Control F302RCV0/Drivers/BSP/Components/vl53l3cx/modules" -I"/home/robbe/Desktop/Github/GestureControl/Code 2.0/GestureControl/Gesture Control F302RCV0/Drivers/BSP/Components/vl53l3cx" -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../X-CUBE-TOF1/Target -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-vl53l3cx

clean-Drivers-2f-BSP-2f-Components-2f-vl53l3cx:
	-$(RM) ./Drivers/BSP/Components/vl53l3cx/vl53l3cx.d ./Drivers/BSP/Components/vl53l3cx/vl53l3cx.o

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-vl53l3cx

