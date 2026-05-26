################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/Buzzer.c 

OBJS += \
./Inc/Buzzer.o 

C_DEPS += \
./Inc/Buzzer.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/%.o Inc/%.su Inc/%.cyclo: ../Inc/%.c Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32L4 -DSTM32 -DSTM32L476RGTx -c -I"D:/SFSU/Engr478/aaLAB/Final_Project/CMSIS/Include" -I"D:/SFSU/Engr478/aaLAB/Final_Project/Inc" -I"D:/SFSU/Engr478/aaLAB/Final_Project/Src" -I"D:/SFSU/Engr478/aaLAB/Final_Project/CMSIS/Device/ST/STM32L4xx/Include" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc

clean-Inc:
	-$(RM) ./Inc/Buzzer.cyclo ./Inc/Buzzer.d ./Inc/Buzzer.o ./Inc/Buzzer.su

.PHONY: clean-Inc

