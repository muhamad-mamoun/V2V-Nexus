################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/USART/SOURCE/USART.c 

OBJS += \
./MCAL/USART/SOURCE/USART.o 

C_DEPS += \
./MCAL/USART/SOURCE/USART.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/USART/SOURCE/%.o MCAL/USART/SOURCE/%.su MCAL/USART/SOURCE/%.cyclo: ../MCAL/USART/SOURCE/%.c MCAL/USART/SOURCE/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -c -I../Inc -I"D:/Content/NTI/Projects/Final Project/Software [Git Repo]/FOTA/Bootloader/OTHERS" -I"D:/Content/NTI/Projects/Final Project/Software [Git Repo]/FOTA/Bootloader/MCAL/FPEC/INCLUDES" -I"D:/Content/NTI/Projects/Final Project/Software [Git Repo]/FOTA/Bootloader/MCAL/GPIO/INCLUDES" -I"D:/Content/NTI/Projects/Final Project/Software [Git Repo]/FOTA/Bootloader/MCAL/NVIC/INCLUDES" -I"D:/Content/NTI/Projects/Final Project/Software [Git Repo]/FOTA/Bootloader/MCAL/RCC/INCLUDES" -I"D:/Content/NTI/Projects/Final Project/Software [Git Repo]/FOTA/Bootloader/MCAL/SYSTICK/INCLUDES" -I"D:/Content/NTI/Projects/Final Project/Software [Git Repo]/FOTA/Bootloader/MCAL/USART/INCLUDES" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCAL-2f-USART-2f-SOURCE

clean-MCAL-2f-USART-2f-SOURCE:
	-$(RM) ./MCAL/USART/SOURCE/USART.cyclo ./MCAL/USART/SOURCE/USART.d ./MCAL/USART/SOURCE/USART.o ./MCAL/USART/SOURCE/USART.su

.PHONY: clean-MCAL-2f-USART-2f-SOURCE

