################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f412zgtx.s 

OBJS += \
./Core/Startup/startup_stm32f412zgtx.o 

S_DEPS += \
./Core/Startup/startup_stm32f412zgtx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Drivers" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Drivers/BSP/Components" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Drivers/BSP/STM32412G-Discovery" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Core/Src/sensor" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Drivers/BSP" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Drivers/BSP/Components/Common" -I"Z:/bsc/repos/microcontroller/STM_Praktikum_D6T/Core/Src/snake" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f412zgtx.d ./Core/Startup/startup_stm32f412zgtx.o

.PHONY: clean-Core-2f-Startup

