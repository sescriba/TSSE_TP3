################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/app/app_sm.c 

OBJS += \
./Core/Src/app/app_sm.o 

C_DEPS += \
./Core/Src/app/app_sm.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/app/%.o Core/Src/app/%.su: ../Core/Src/app/%.c Core/Src/app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/CESE/Programacion_Microcontroladores/PdM_sescriba/MPU9250/Drivers/dev/src" -I"D:/Documents/CESE/Programacion_Microcontroladores/PdM_sescriba/MPU9250/Drivers/dev/inc" -I"D:/Documents/CESE/Programacion_Microcontroladores/PdM_sescriba/MPU9250/Core/Src" -I"D:/Documents/CESE/Programacion_Microcontroladores/PdM_sescriba/MPU9250/Core/Inc/app" -I"D:/Documents/CESE/Programacion_Microcontroladores/PdM_sescriba/MPU9250/Core/Src/app" -I"D:/Documents/CESE/Programacion_Microcontroladores/PdM_sescriba/MPU9250/Drivers/BSP" -I"D:/Documents/CESE/Programacion_Microcontroladores/PdM_sescriba/MPU9250/Drivers/BSP/STM32F4xx_Nucleo_144" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-app

clean-Core-2f-Src-2f-app:
	-$(RM) ./Core/Src/app/app_sm.d ./Core/Src/app/app_sm.o ./Core/Src/app/app_sm.su

.PHONY: clean-Core-2f-Src-2f-app

