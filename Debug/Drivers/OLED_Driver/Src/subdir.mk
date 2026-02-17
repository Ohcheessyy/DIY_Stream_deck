################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/OLED_Driver/Src/ssd1306.c \
../Drivers/OLED_Driver/Src/ssd1306_fonts.c 

OBJS += \
./Drivers/OLED_Driver/Src/ssd1306.o \
./Drivers/OLED_Driver/Src/ssd1306_fonts.o 

C_DEPS += \
./Drivers/OLED_Driver/Src/ssd1306.d \
./Drivers/OLED_Driver/Src/ssd1306_fonts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/OLED_Driver/Src/%.o Drivers/OLED_Driver/Src/%.su Drivers/OLED_Driver/Src/%.cyclo: ../Drivers/OLED_Driver/Src/%.c Drivers/OLED_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"C:/Users/Ohcheessyy/Desktop/STM32Project/Stream_deck/Drivers/OLED_Driver/Inc" -I"C:/Users/Ohcheessyy/Desktop/STM32Project/Stream_deck/Drivers/OLED_Driver" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-OLED_Driver-2f-Src

clean-Drivers-2f-OLED_Driver-2f-Src:
	-$(RM) ./Drivers/OLED_Driver/Src/ssd1306.cyclo ./Drivers/OLED_Driver/Src/ssd1306.d ./Drivers/OLED_Driver/Src/ssd1306.o ./Drivers/OLED_Driver/Src/ssd1306.su ./Drivers/OLED_Driver/Src/ssd1306_fonts.cyclo ./Drivers/OLED_Driver/Src/ssd1306_fonts.d ./Drivers/OLED_Driver/Src/ssd1306_fonts.o ./Drivers/OLED_Driver/Src/ssd1306_fonts.su

.PHONY: clean-Drivers-2f-OLED_Driver-2f-Src

