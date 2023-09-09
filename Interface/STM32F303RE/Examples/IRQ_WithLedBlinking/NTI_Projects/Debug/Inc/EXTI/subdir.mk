################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/EXTI/extint.c 

OBJS += \
./Inc/EXTI/extint.o 

C_DEPS += \
./Inc/EXTI/extint.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/EXTI/extint.o: ../Inc/EXTI/extint.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I../Inc -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/EXTI" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/NVIC" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/GPIO" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/LIB" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/EXTI/extint.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

