################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/GPIO/GPIO.c 

OBJS += \
./Inc/GPIO/GPIO.o 

C_DEPS += \
./Inc/GPIO/GPIO.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/GPIO/%.o: ../Inc/GPIO/%.c Inc/GPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-GPIO

clean-Inc-2f-GPIO:
	-$(RM) ./Inc/GPIO/GPIO.d ./Inc/GPIO/GPIO.o

.PHONY: clean-Inc-2f-GPIO

