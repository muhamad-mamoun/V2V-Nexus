################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/FPEC_program.c \
../Src/NVIC.c \
../Src/Parse.c \
../Src/RCC.c \
../Src/STK_program.c \
../Src/USART.c \
../Src/gpio.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/FPEC_program.o \
./Src/NVIC.o \
./Src/Parse.o \
./Src/RCC.o \
./Src/STK_program.o \
./Src/USART.o \
./Src/gpio.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/FPEC_program.d \
./Src/NVIC.d \
./Src/Parse.d \
./Src/RCC.d \
./Src/STK_program.d \
./Src/USART.d \
./Src/gpio.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/FPEC_program.cyclo ./Src/FPEC_program.d ./Src/FPEC_program.o ./Src/FPEC_program.su ./Src/NVIC.cyclo ./Src/NVIC.d ./Src/NVIC.o ./Src/NVIC.su ./Src/Parse.cyclo ./Src/Parse.d ./Src/Parse.o ./Src/Parse.su ./Src/RCC.cyclo ./Src/RCC.d ./Src/RCC.o ./Src/RCC.su ./Src/STK_program.cyclo ./Src/STK_program.d ./Src/STK_program.o ./Src/STK_program.su ./Src/USART.cyclo ./Src/USART.d ./Src/USART.o ./Src/USART.su ./Src/gpio.cyclo ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

