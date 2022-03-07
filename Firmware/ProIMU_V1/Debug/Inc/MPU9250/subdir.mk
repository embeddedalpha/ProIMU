################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/MPU9250/MPU9250.c 

OBJS += \
./Inc/MPU9250/MPU9250.o 

C_DEPS += \
./Inc/MPU9250/MPU9250.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/MPU9250/%.o: ../Inc/MPU9250/%.c Inc/MPU9250/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-MPU9250

clean-Inc-2f-MPU9250:
	-$(RM) ./Inc/MPU9250/MPU9250.d ./Inc/MPU9250/MPU9250.o

.PHONY: clean-Inc-2f-MPU9250

