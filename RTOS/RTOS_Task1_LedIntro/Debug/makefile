################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Inc/RCC/subdir.mk
-include Inc/NVIC/subdir.mk
-include Inc/GPIO/subdir.mk
-include Inc/EXTI/subdir.mk
-include FreeRTOS/Source/portable/MemMang/subdir.mk
-include FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include FreeRTOS/Source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
NTI_Projects.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
NTI_Projects.list \

OBJCOPY_BIN += \
NTI_Projects.bin \


# All Target
all: NTI_Projects.elf secondary-outputs

# Tool invocations
NTI_Projects.elf: $(OBJS) $(USER_OBJS) C:\Users\Abnaby\STM32CubeIDE\workspace_1.4.0\NTI_Projects\STM32F303RETX_FLASH.ld
	arm-none-eabi-gcc -o "NTI_Projects.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Abnaby\STM32CubeIDE\workspace_1.4.0\NTI_Projects\STM32F303RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="NTI_Projects.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

NTI_Projects.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "NTI_Projects.list"
	@echo 'Finished building: $@'
	@echo ' '

NTI_Projects.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "NTI_Projects.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
