################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ADC.c \
../Src/Audio.c \
../Src/Button.c \
../Src/Buzzer.c \
../Src/LED.c \
../Src/Systick_timer.c \
../Src/USART.c \
../Src/main.c \
../Src/syscalls.c 

OBJS += \
./Src/ADC.o \
./Src/Audio.o \
./Src/Button.o \
./Src/Buzzer.o \
./Src/LED.o \
./Src/Systick_timer.o \
./Src/USART.o \
./Src/main.o \
./Src/syscalls.o 

C_DEPS += \
./Src/ADC.d \
./Src/Audio.d \
./Src/Button.d \
./Src/Buzzer.d \
./Src/LED.d \
./Src/Systick_timer.d \
./Src/USART.d \
./Src/main.d \
./Src/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L4 -DSTM32 -DSTM32L476RGTx -c -I../Inc -I"D:/SFSU/Engr478/aaLAB/FP83/CtrlBrain-Stm32-Darkness-project/Final_Project/CMSIS/Include" -I"D:/SFSU/Engr478/aaLAB/FP83/CtrlBrain-Stm32-Darkness-project/Final_Project/CMSIS/Device/ST/STM32L4xx/Include" -O0 -ffunction-sections -fdata-sections -mslow-flash-data -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/ADC.cyclo ./Src/ADC.d ./Src/ADC.o ./Src/ADC.su ./Src/Audio.cyclo ./Src/Audio.d ./Src/Audio.o ./Src/Audio.su ./Src/Button.cyclo ./Src/Button.d ./Src/Button.o ./Src/Button.su ./Src/Buzzer.cyclo ./Src/Buzzer.d ./Src/Buzzer.o ./Src/Buzzer.su ./Src/LED.cyclo ./Src/LED.d ./Src/LED.o ./Src/LED.su ./Src/Systick_timer.cyclo ./Src/Systick_timer.d ./Src/Systick_timer.o ./Src/Systick_timer.su ./Src/USART.cyclo ./Src/USART.d ./Src/USART.o ./Src/USART.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su

.PHONY: clean-Src

