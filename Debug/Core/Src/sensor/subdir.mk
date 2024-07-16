################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/sensor/communication.c \
../Core/Src/sensor/d6t.c \
../Core/Src/sensor/render.c 

OBJS += \
./Core/Src/sensor/communication.o \
./Core/Src/sensor/d6t.o \
./Core/Src/sensor/render.o 

C_DEPS += \
./Core/Src/sensor/communication.d \
./Core/Src/sensor/d6t.d \
./Core/Src/sensor/render.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/sensor/%.o Core/Src/sensor/%.su Core/Src/sensor/%.cyclo: ../Core/Src/sensor/%.c Core/Src/sensor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F412Zx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Drivers" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Drivers/BSP/Components" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Drivers/BSP/STM32412G-Discovery" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Core/Src/sensor" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Drivers/BSP" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Drivers/BSP/Components/Common" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Core/Src/snake" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-sensor

clean-Core-2f-Src-2f-sensor:
	-$(RM) ./Core/Src/sensor/communication.cyclo ./Core/Src/sensor/communication.d ./Core/Src/sensor/communication.o ./Core/Src/sensor/communication.su ./Core/Src/sensor/d6t.cyclo ./Core/Src/sensor/d6t.d ./Core/Src/sensor/d6t.o ./Core/Src/sensor/d6t.su ./Core/Src/sensor/render.cyclo ./Core/Src/sensor/render.d ./Core/Src/sensor/render.o ./Core/Src/sensor/render.su

.PHONY: clean-Core-2f-Src-2f-sensor

