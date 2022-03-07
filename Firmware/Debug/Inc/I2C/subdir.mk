################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/I2C/I2C.c 

OBJS += \
./Inc/I2C/I2C.o 

C_DEPS += \
./Inc/I2C/I2C.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/I2C/%.o: ../Inc/I2C/%.c Inc/I2C/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-I2C

clean-Inc-2f-I2C:
	-$(RM) ./Inc/I2C/I2C.d ./Inc/I2C/I2C.o

.PHONY: clean-Inc-2f-I2C

