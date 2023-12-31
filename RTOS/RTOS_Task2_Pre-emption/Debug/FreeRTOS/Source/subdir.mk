################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Source/croutine.c \
../FreeRTOS/Source/event_groups.c \
../FreeRTOS/Source/list.c \
../FreeRTOS/Source/queue.c \
../FreeRTOS/Source/stream_buffer.c \
../FreeRTOS/Source/tasks.c \
../FreeRTOS/Source/timers.c 

OBJS += \
./FreeRTOS/Source/croutine.o \
./FreeRTOS/Source/event_groups.o \
./FreeRTOS/Source/list.o \
./FreeRTOS/Source/queue.o \
./FreeRTOS/Source/stream_buffer.o \
./FreeRTOS/Source/tasks.o \
./FreeRTOS/Source/timers.o 

C_DEPS += \
./FreeRTOS/Source/croutine.d \
./FreeRTOS/Source/event_groups.d \
./FreeRTOS/Source/list.d \
./FreeRTOS/Source/queue.d \
./FreeRTOS/Source/stream_buffer.d \
./FreeRTOS/Source/tasks.d \
./FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/croutine.o: ../FreeRTOS/Source/croutine.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I../Inc -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/EXTI" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/NVIC" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/GPIO" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/LIB" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/include" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/Source/croutine.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
FreeRTOS/Source/event_groups.o: ../FreeRTOS/Source/event_groups.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I../Inc -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/EXTI" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/NVIC" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/GPIO" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/LIB" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/include" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/Source/event_groups.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
FreeRTOS/Source/list.o: ../FreeRTOS/Source/list.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I../Inc -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/EXTI" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/NVIC" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/GPIO" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/LIB" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/include" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/Source/list.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
FreeRTOS/Source/queue.o: ../FreeRTOS/Source/queue.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I../Inc -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/EXTI" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/NVIC" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/GPIO" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/LIB" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/include" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/Source/queue.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
FreeRTOS/Source/stream_buffer.o: ../FreeRTOS/Source/stream_buffer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I../Inc -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/EXTI" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/NVIC" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/GPIO" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/LIB" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/include" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/Source/stream_buffer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
FreeRTOS/Source/tasks.o: ../FreeRTOS/Source/tasks.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I../Inc -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/EXTI" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/NVIC" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/GPIO" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/LIB" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/include" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/Source/tasks.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
FreeRTOS/Source/timers.o: ../FreeRTOS/Source/timers.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I../Inc -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/EXTI" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/NVIC" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/GPIO" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/Inc/LIB" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/include" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/NTI_Projects/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/Source/timers.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

