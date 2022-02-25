################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/robel/Desktop/testing\ Nucleo/en.en.bare_driver_VL53L3CX_v1.2.8/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f401xe.s 

OBJS += \
./Application/SW4STM32/startup_stm32f401xe.o 

S_DEPS += \
./Application/SW4STM32/startup_stm32f401xe.d 


# Each subdirectory must supply rules for building sources it contributes
Application/SW4STM32/startup_stm32f401xe.o: C:/Users/robel/Desktop/testing\ Nucleo/en.en.bare_driver_VL53L3CX_v1.2.8/BareDriver/VL53L3CX_API_1.2.8/example/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f401xe.s Application/SW4STM32/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"Application/SW4STM32/startup_stm32f401xe.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Application-2f-SW4STM32

clean-Application-2f-SW4STM32:
	-$(RM) ./Application/SW4STM32/startup_stm32f401xe.d ./Application/SW4STM32/startup_stm32f401xe.o

.PHONY: clean-Application-2f-SW4STM32

