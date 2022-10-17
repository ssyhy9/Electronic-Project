################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MyLibrary/adc.c 

OBJS += \
./MyLibrary/adc.o 

C_DEPS += \
./MyLibrary/adc.d 


# Each subdirectory must supply rules for building sources it contributes
MyLibrary/%.o MyLibrary/%.su: ../MyLibrary/%.c MyLibrary/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -IC:/Users/Razer/STM32Cube/Repository/STM32Cube_FW_L4_V1.17.2/Drivers/STM32L4xx_HAL_Driver/Inc -IC:/Users/Razer/STM32Cube/Repository/STM32Cube_FW_L4_V1.17.2/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -IC:/Users/Razer/STM32Cube/Repository/STM32Cube_FW_L4_V1.17.2/Drivers/CMSIS/Device/ST/STM32L4xx/Include -IC:/Users/Razer/STM32Cube/Repository/STM32Cube_FW_L4_V1.17.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MyLibrary

clean-MyLibrary:
	-$(RM) ./MyLibrary/adc.d ./MyLibrary/adc.o ./MyLibrary/adc.su

.PHONY: clean-MyLibrary

