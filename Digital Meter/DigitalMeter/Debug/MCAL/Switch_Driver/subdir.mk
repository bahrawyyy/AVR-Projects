################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/Switch_Driver/Switch_Config.c \
../MCAL/Switch_Driver/Switch_Program.c 

OBJS += \
./MCAL/Switch_Driver/Switch_Config.o \
./MCAL/Switch_Driver/Switch_Program.o 

C_DEPS += \
./MCAL/Switch_Driver/Switch_Config.d \
./MCAL/Switch_Driver/Switch_Program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/Switch_Driver/%.o: ../MCAL/Switch_Driver/%.c MCAL/Switch_Driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


