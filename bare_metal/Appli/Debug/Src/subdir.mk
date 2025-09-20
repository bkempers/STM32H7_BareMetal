################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/exti.c \
../Src/led_driver.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/systick.c \
../Src/timer.c \
../Src/uart_driver.c 

OBJS += \
./Src/adc.o \
./Src/exti.o \
./Src/led_driver.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/systick.o \
./Src/timer.o \
./Src/uart_driver.o 

C_DEPS += \
./Src/adc.d \
./Src/exti.d \
./Src/led_driver.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/systick.d \
./Src/timer.d \
./Src/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32H7SINGLE -DSTM32H7S3L8Hx -DNUCLEO_H7S3L8 -DSTM32H7 -c -I../Inc -I/Users/benkempers/Developer/Misc/STM32CubeH7RS/Drivers/CMSIS/Core/Include -I/Users/benkempers/Developer/Misc/STM32CubeH7RS/Drivers/CMSIS/Device/ST/STM32H7RSxx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc.cyclo ./Src/adc.d ./Src/adc.o ./Src/adc.su ./Src/exti.cyclo ./Src/exti.d ./Src/exti.o ./Src/exti.su ./Src/led_driver.cyclo ./Src/led_driver.d ./Src/led_driver.o ./Src/led_driver.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/systick.cyclo ./Src/systick.d ./Src/systick.o ./Src/systick.su ./Src/timer.cyclo ./Src/timer.d ./Src/timer.o ./Src/timer.su ./Src/uart_driver.cyclo ./Src/uart_driver.d ./Src/uart_driver.o ./Src/uart_driver.su

.PHONY: clean-Src

