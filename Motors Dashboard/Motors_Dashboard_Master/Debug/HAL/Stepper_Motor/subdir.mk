################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Stepper_Motor/Stepper.c 

OBJS += \
./HAL/Stepper_Motor/Stepper.o 

C_DEPS += \
./HAL/Stepper_Motor/Stepper.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Stepper_Motor/%.o: ../HAL/Stepper_Motor/%.c HAL/Stepper_Motor/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


