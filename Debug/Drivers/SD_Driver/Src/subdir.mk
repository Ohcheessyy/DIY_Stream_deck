################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SD_Driver/Src/sdcard.c 

OBJS += \
./Drivers/SD_Driver/Src/sdcard.o 

C_DEPS += \
./Drivers/SD_Driver/Src/sdcard.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SD_Driver/Src/%.o Drivers/SD_Driver/Src/%.su Drivers/SD_Driver/Src/%.cyclo: ../Drivers/SD_Driver/Src/%.c Drivers/SD_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"C:/Users/Ohcheessyy/Desktop/STM32Project/Stream_deck/Drivers/SD_Driver/Inc" -I"C:/Users/Ohcheessyy/Desktop/STM32Project/Stream_deck/Drivers/OLED_Driver/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-SD_Driver-2f-Src

clean-Drivers-2f-SD_Driver-2f-Src:
	-$(RM) ./Drivers/SD_Driver/Src/sdcard.cyclo ./Drivers/SD_Driver/Src/sdcard.d ./Drivers/SD_Driver/Src/sdcard.o ./Drivers/SD_Driver/Src/sdcard.su

.PHONY: clean-Drivers-2f-SD_Driver-2f-Src

