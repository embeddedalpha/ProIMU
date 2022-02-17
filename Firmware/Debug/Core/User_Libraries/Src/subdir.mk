################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/User_Libraries/Src/BMP280.c \
../Core/User_Libraries/Src/Console.c \
../Core/User_Libraries/Src/GPIO.c \
../Core/User_Libraries/Src/I2C.c \
../Core/User_Libraries/Src/MPU9250.c 

OBJS += \
./Core/User_Libraries/Src/BMP280.o \
./Core/User_Libraries/Src/Console.o \
./Core/User_Libraries/Src/GPIO.o \
./Core/User_Libraries/Src/I2C.o \
./Core/User_Libraries/Src/MPU9250.o 

C_DEPS += \
./Core/User_Libraries/Src/BMP280.d \
./Core/User_Libraries/Src/Console.d \
./Core/User_Libraries/Src/GPIO.d \
./Core/User_Libraries/Src/I2C.d \
./Core/User_Libraries/Src/MPU9250.d 


# Each subdirectory must supply rules for building sources it contributes
Core/User_Libraries/Src/%.o: ../Core/User_Libraries/Src/%.c Core/User_Libraries/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F412Cx -c -I../Core/Inc -I"C:/Users/Kunal/STM32CubeIDE/Kunal/Blackshield_Eng/ProIMU/Core/User_Libraries/Inc" -I"C:/Users/Kunal/STM32CubeIDE/Kunal/Blackshield_Eng/ProIMU/Core/User_Libraries/Src" -IC:/Users/Kunal/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.2/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Kunal/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Kunal/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Kunal/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.2/Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -IC:/Users/Kunal/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -IC:/Users/Kunal/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.2/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-User_Libraries-2f-Src

clean-Core-2f-User_Libraries-2f-Src:
	-$(RM) ./Core/User_Libraries/Src/BMP280.d ./Core/User_Libraries/Src/BMP280.o ./Core/User_Libraries/Src/Console.d ./Core/User_Libraries/Src/Console.o ./Core/User_Libraries/Src/GPIO.d ./Core/User_Libraries/Src/GPIO.o ./Core/User_Libraries/Src/I2C.d ./Core/User_Libraries/Src/I2C.o ./Core/User_Libraries/Src/MPU9250.d ./Core/User_Libraries/Src/MPU9250.o

.PHONY: clean-Core-2f-User_Libraries-2f-Src

