################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MyLibrary/LCD.c \
../MyLibrary/RS485.c \
../MyLibrary/adc.c \
../MyLibrary/fft.c 

OBJS += \
./MyLibrary/LCD.o \
./MyLibrary/RS485.o \
./MyLibrary/adc.o \
./MyLibrary/fft.o 

C_DEPS += \
./MyLibrary/LCD.d \
./MyLibrary/RS485.d \
./MyLibrary/adc.d \
./MyLibrary/fft.d 


# Each subdirectory must supply rules for building sources it contributes
MyLibrary/%.o MyLibrary/%.su: ../MyLibrary/%.c MyLibrary/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I"D:/ST/WorkSpace/Project_ADC/Drivers/CMSIS/DSP/Include" -IC:/Users/Razer/STM32Cube/Repository/STM32Cube_FW_L4_V1.17.2/Drivers/STM32L4xx_HAL_Driver/Inc -IC:/Users/Razer/STM32Cube/Repository/STM32Cube_FW_L4_V1.17.2/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -IC:/Users/Razer/STM32Cube/Repository/STM32Cube_FW_L4_V1.17.2/Drivers/CMSIS/Device/ST/STM32L4xx/Include -IC:/Users/Razer/STM32Cube/Repository/STM32Cube_FW_L4_V1.17.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MyLibrary

clean-MyLibrary:
	-$(RM) ./MyLibrary/LCD.d ./MyLibrary/LCD.o ./MyLibrary/LCD.su ./MyLibrary/RS485.d ./MyLibrary/RS485.o ./MyLibrary/RS485.su ./MyLibrary/adc.d ./MyLibrary/adc.o ./MyLibrary/adc.su ./MyLibrary/fft.d ./MyLibrary/fft.o ./MyLibrary/fft.su

.PHONY: clean-MyLibrary

