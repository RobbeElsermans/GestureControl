################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/VL53L3CX_API_1.2.8/example/Src/main.c \
../Drivers/VL53L3CX_API_1.2.8/example/Src/stm32f4xx_hal_msp.c \
../Drivers/VL53L3CX_API_1.2.8/example/Src/stm32f4xx_it.c \
../Drivers/VL53L3CX_API_1.2.8/example/Src/stm32l4xx_hal_msp.c \
../Drivers/VL53L3CX_API_1.2.8/example/Src/stm32l4xx_it.c \
../Drivers/VL53L3CX_API_1.2.8/example/Src/syscalls.c \
../Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform.c \
../Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_init.c \
../Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_ipp.c \
../Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_log.c 

OBJS += \
./Drivers/VL53L3CX_API_1.2.8/example/Src/main.o \
./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32f4xx_hal_msp.o \
./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32f4xx_it.o \
./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32l4xx_hal_msp.o \
./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32l4xx_it.o \
./Drivers/VL53L3CX_API_1.2.8/example/Src/syscalls.o \
./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform.o \
./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_init.o \
./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_ipp.o \
./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_log.o 

C_DEPS += \
./Drivers/VL53L3CX_API_1.2.8/example/Src/main.d \
./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32f4xx_hal_msp.d \
./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32f4xx_it.d \
./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32l4xx_hal_msp.d \
./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32l4xx_it.d \
./Drivers/VL53L3CX_API_1.2.8/example/Src/syscalls.d \
./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform.d \
./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_init.d \
./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_ipp.d \
./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_log.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/VL53L3CX_API_1.2.8/example/Src/%.o: ../Drivers/VL53L3CX_API_1.2.8/example/Src/%.c Drivers/VL53L3CX_API_1.2.8/example/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/robel/GitHub/GestureControl/Code 2.0/GestureControl/Drivers/VL53L3CX_API_1.2.8" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-example-2f-Src

clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-example-2f-Src:
	-$(RM) ./Drivers/VL53L3CX_API_1.2.8/example/Src/main.d ./Drivers/VL53L3CX_API_1.2.8/example/Src/main.o ./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32f4xx_hal_msp.d ./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32f4xx_hal_msp.o ./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32f4xx_it.d ./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32f4xx_it.o ./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32l4xx_hal_msp.d ./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32l4xx_hal_msp.o ./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32l4xx_it.d ./Drivers/VL53L3CX_API_1.2.8/example/Src/stm32l4xx_it.o ./Drivers/VL53L3CX_API_1.2.8/example/Src/syscalls.d ./Drivers/VL53L3CX_API_1.2.8/example/Src/syscalls.o ./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform.d ./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform.o ./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_init.d ./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_init.o ./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_ipp.d ./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_ipp.o ./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_log.d ./Drivers/VL53L3CX_API_1.2.8/example/Src/vl53lx_platform_log.o

.PHONY: clean-Drivers-2f-VL53L3CX_API_1-2e-2-2e-8-2f-example-2f-Src

