################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/NVIC/nvic.c 

OBJS += \
./Inc/NVIC/nvic.o 

C_DEPS += \
./Inc/NVIC/nvic.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/NVIC/nvic.o: ../Inc/NVIC/nvic.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I../Inc -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/EXTI" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/NVIC" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/GPIO" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/LIB" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/include" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/NVIC/nvic.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

