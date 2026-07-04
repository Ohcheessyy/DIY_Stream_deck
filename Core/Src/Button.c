/*
 * Button.c
 *
 *  Created on: Feb 15, 2026
 *      Author: Ohcheessyy
 */

#include "Button.h"
#include "main.h"
#include "Main_display_control.h"

UI16 debounce_pin;                                                         // Variable to store the pin number of the button being debounced
UI8 debounce_state_flag;                                                   // Flag to indicate if debounce is in progress (1) or not (0)
UI8 prevBtnState[BUTTONMAX];
UI8 currBtnState[BUTTONMAX];

GPIO_TypeDef* BtnPort[BUTTONMAX] = {GPIOA, GPIOA, GPIOA, GPIOA, GPIOB, GPIOB}; // Pointers to the GPIO ports for each button
UI16 BtnPin[BUTTONMAX] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5}; // Pin numbers for each button
// Button initialization function to clear previous states before use

void Button_Init(void)
{
    for (UI8 i = 0; i < BUTTONMAX; ++i)
    {
        prevBtnState[i] = OFF;
    }
}

// Function to reset button states after processing

void Button_State_Reset(void)
{
    for (UI8 i = 0; i < BUTTONMAX; ++i)
    {
        prevBtnState[i] = currBtnState[i];
        GPIO_PinState pin_state = HAL_GPIO_ReadPin(BtnPort[i], BtnPin[i]);
        if (pin_state != GPIO_PIN_RESET)
        {
            currBtnState[i] = OFF;
        }
    }
}

// EXTI callback function called when a button is pressed

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (debounce_state_flag == ON)                                            // Check if debounce is already in progress
    {
        return;
    }
    
    debounce_state_flag = ON;                                                // Set debounce flag to indicate debounce is in progress
    debounce_pin = GPIO_Pin;                                                // Store the pin number of the button being debounced
    
    __HAL_TIM_SET_COUNTER(&htim3, 0);                                       // Reset the timer counter to 0 and start the timer in interrupt mode to handle debounce timing
    HAL_TIM_Base_Start_IT(&htim3);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    HAL_TIM_Base_Stop_IT(htim);                                              // Stop the timer

    UI16 pressed_pin = debounce_pin;
    debounce_pin = 0;
    debounce_state_flag = 0;

    GPIO_PinState pin_state;
    if (pressed_pin == GPIO_PIN_4 || pressed_pin == GPIO_PIN_5)             // Check if the pressed pin is on GPIOB (buttons 4 and 5)
    {
        pin_state = HAL_GPIO_ReadPin(GPIOB, pressed_pin);
    }
    else
    {
        pin_state = HAL_GPIO_ReadPin(GPIOA, pressed_pin);                   // Read the state of the pressed pin from GPIOA (buttons 0-3)
    }

    if (pin_state == GPIO_PIN_RESET)                                        // active low: pressed
    {
        Button_TypeDef Btn_Input = BUTTONMAX;
        if (pressed_pin == GPIO_PIN_0) Btn_Input = BUTTON0;
        else if (pressed_pin == GPIO_PIN_1) Btn_Input = BUTTON1;
        else if (pressed_pin == GPIO_PIN_2) Btn_Input = BUTTON2;
        else if (pressed_pin == GPIO_PIN_3) Btn_Input = BUTTON3;
        else if (pressed_pin == GPIO_PIN_4) Btn_Input = BUTTON4;
        else if (pressed_pin == GPIO_PIN_5) Btn_Input = BUTTON5;

        if (Btn_Input != BUTTONMAX)
        {
            currBtnState[Btn_Input] = ON; // Update current button state to pressed
            Main_Operation();
        }
    }
}
