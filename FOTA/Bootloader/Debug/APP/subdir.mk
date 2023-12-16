################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/Parse.c \
../APP/main.c 

OBJS += \
./APP/Parse.o \
./APP/main.o 

C_DEPS += \
./APP/Parse.d \
./APP/main.d 


# Each subdirectory must supply rules for building sources it contributes
APP/%.o APP/%.su APP/%.cyclo: ../APP/%.c APP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -c -I../Inc -I"D:/Content/NTI/Projects/Final Project/Software [Git Repo]/FOTA/Bootloader/OTHERS" -I"D:/Content/NTI/Projects/Final Project/Software [Git Repo]/FOTA/Bootloader/MCAL/FPEC/INCLUDES" -I"D:/Content/NTI/Projects/Final Project/Software [Git Repo]/FOTA/Bootloader/MCAL/GPIO/INCLUDES" -I"D:/Content/NTI/Projects/Final Project/Software [Git Repo]/FOTA/Bootloader/MCAL/NVIC/INCLUDES" -I"D:/Content/NTI/Projects/Final Project/Software [Git Repo]/FOTA/Bootloader/MCAL/RCC/INCLUDES" -I"D:/Content/NTI/Projects/Final Project/Software [Git Repo]/FOTA/Bootloader/MCAL/SYSTICK/INCLUDES" -I"D:/Content/NTI/Projects/Final Project/Software [Git Repo]/FOTA/Bootloader/MCAL/USART/INCLUDES" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-APP

clean-APP:
	-$(RM) ./APP/Parse.cyclo ./APP/Parse.d ./APP/Parse.o ./APP/Parse.su ./APP/main.cyclo ./APP/main.d ./APP/main.o ./APP/main.su

.PHONY: clean-APP

