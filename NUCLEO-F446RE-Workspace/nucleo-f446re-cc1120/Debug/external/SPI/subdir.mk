################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../external/SPI/spi_lib.c 

C_DEPS += \
./external/SPI/spi_lib.d 

OBJS += \
./external/SPI/spi_lib.o 


# Each subdirectory must supply rules for building sources it contributes
external/SPI/spi_lib.o: ../external/SPI/spi_lib.c external/SPI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/seant/OneDrive/Documents/QSAT/CC1120/NUCLEO-F446RE-Workspace/NUCLEO-F446RE-CC1120/external/includes" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"external/SPI/spi_lib.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

