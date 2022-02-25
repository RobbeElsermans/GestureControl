################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/VL53L3CX_API_1.2.8/platform/src/vl53l3cx.c \
../Drivers/VL53L3CX_API_1.2.8/platform/src/vl53lx_platform.c \
../Drivers/VL53L3CX_API_1.2.8/platform/src/vl53lx_platform_ipp.c \
../Drivers/VL53L3CX_API_1.2.8/platform/src/vl53lx_platform_log.c 

OBJS += \
./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53l3cx.o \
./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53lx_platform.o \
./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53lx_platform_ipp.o \
./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53lx_platform_log.o 

C_DEPS += \
./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53l3cx.d \
./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53lx_platform.d \
./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53lx_platform_ipp.d \
./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53lx_platform_log.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/VL53L3CX_API_1.2.8/platform/src/%.o: ../Drivers/VL53L3CX_API_1.2.8/platform/src/%.c Drivers/VL53L3CX_API_1.2.8/platform/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/robel/GitHub/GestureControl/Code 2.0/GestureControl/Drivers/VL53L3CX_API_1.2.8" -I"C:/Users/robel/GitHub/GestureControl/Code 2.0/GestureControl/Drivers/VL53L3CX_API_1.2.8/platform/src" -I"C:/Users/robel/GitHub/GestureControl/Code 2.0/GestureControl/Drivers/VL53L3CX_API_1.2.8/platform/inc" -I"C:/Users/robel/GitHub/GestureControl/Code 2.0/GestureControl/Drivers/VL53L3CX_API_1.2.8/core/inc" -I"C:/Users/robel/GitHub/GestureControl/Code 2.0/GestureControl/Drivers/VL53L3CX_API_1.2.8/core/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-platform-2f-src

clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-platform-2f-src:
	-$(RM) ./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53l3cx.d ./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53l3cx.o ./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53lx_platform.d ./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53lx_platform.o ./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53lx_platform_ipp.d ./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53lx_platform_ipp.o ./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53lx_platform_log.d ./Drivers/VL53L3CX_API_1.2.8/platform/src/vl53lx_platform_log.o

.PHONY: clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-platform-2f-src

