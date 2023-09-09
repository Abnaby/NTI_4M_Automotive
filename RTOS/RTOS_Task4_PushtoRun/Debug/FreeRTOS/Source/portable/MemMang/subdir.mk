################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Source/portable/MemMang/heap_4.c 

OBJS += \
./FreeRTOS/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./FreeRTOS/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/portable/MemMang/heap_4.o: ../FreeRTOS/Source/portable/MemMang/heap_4.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I../Inc -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/EXTI" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/NVIC" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/GPIO" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/LIB" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/include" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/Source/portable/MemMang/heap_4.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

