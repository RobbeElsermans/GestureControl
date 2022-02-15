################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/53L3A2/53l3a2.c \
../Drivers/BSP/53L3A2/53l3a2_ranging_sensor.c 

OBJS += \
./Drivers/BSP/53L3A2/53l3a2.o \
./Drivers/BSP/53L3A2/53l3a2_ranging_sensor.o 

C_DEPS += \
./Drivers/BSP/53L3A2/53l3a2.d \
./Drivers/BSP/53L3A2/53l3a2_ranging_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/53L3A2/%.o: ../Drivers/BSP/53L3A2/%.c Drivers/BSP/53L3A2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../X-CUBE-TOF1/Target -I../Drivers/BSP/53L3A2 -I../Drivers/BSP/Components/vl53l3cx/modules -I../Drivers/BSP/Components/vl53l3cx/porting -I../Drivers/BSP/Components/vl53l3cx -I../Drivers/BSP/Components/Common -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-53L3A2

clean-Drivers-2f-BSP-2f-53L3A2:
	-$(RM) ./Drivers/BSP/53L3A2/53l3a2.d ./Drivers/BSP/53L3A2/53l3a2.o ./Drivers/BSP/53L3A2/53l3a2_ranging_sensor.d ./Drivers/BSP/53L3A2/53l3a2_ranging_sensor.o

.PHONY: clean-Drivers-2f-BSP-2f-53L3A2

