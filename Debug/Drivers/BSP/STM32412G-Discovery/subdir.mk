################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.c \
../Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.c 

OBJS += \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.o \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.o 

C_DEPS += \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.d \
./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32412G-Discovery/%.o Drivers/BSP/STM32412G-Discovery/%.su Drivers/BSP/STM32412G-Discovery/%.cyclo: ../Drivers/BSP/STM32412G-Discovery/%.c Drivers/BSP/STM32412G-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F412Zx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Drivers" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Drivers/BSP/Components" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Drivers/BSP/STM32412G-Discovery" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Core/Src/sensor" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Drivers/BSP" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Drivers/BSP/Components/Common" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Core/Src/snake" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32412G-2d-Discovery

clean-Drivers-2f-BSP-2f-STM32412G-2d-Discovery:
	-$(RM) ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.cyclo ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.d ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.o ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery.su ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.cyclo ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.d ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.o ./Drivers/BSP/STM32412G-Discovery/stm32412g_discovery_lcd.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32412G-2d-Discovery

