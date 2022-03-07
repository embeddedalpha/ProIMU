################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/SPI/SPI.c 

OBJS += \
./Inc/SPI/SPI.o 

C_DEPS += \
./Inc/SPI/SPI.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/SPI/%.o: ../Inc/SPI/%.c Inc/SPI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-SPI

clean-Inc-2f-SPI:
	-$(RM) ./Inc/SPI/SPI.d ./Inc/SPI/SPI.o

.PHONY: clean-Inc-2f-SPI

