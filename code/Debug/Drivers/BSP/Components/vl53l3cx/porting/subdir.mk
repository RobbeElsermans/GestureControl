################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform.c \
../Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform_ipp.c \
../Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform_log.c 

OBJS += \
./Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform.o \
./Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform_ipp.o \
./Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform_log.o 

C_DEPS += \
./Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform.d \
./Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform_ipp.d \
./Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform_log.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/vl53l3cx/porting/%.o: ../Drivers/BSP/Components/vl53l3cx/porting/%.c Drivers/BSP/Components/vl53l3cx/porting/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../X-CUBE-TOF1/Target -I../Drivers/BSP/53L3A2 -I../Drivers/BSP/Components/vl53l3cx/modules -I../Drivers/BSP/Components/vl53l3cx/porting -I../Drivers/BSP/Components/vl53l3cx -I../Drivers/BSP/Components/Common -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-vl53l3cx-2f-porting

clean-Drivers-2f-BSP-2f-Components-2f-vl53l3cx-2f-porting:
	-$(RM) ./Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform.d ./Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform.o ./Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform_ipp.d ./Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform_ipp.o ./Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform_log.d ./Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform_log.o

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-vl53l3cx-2f-porting

