/*
 * Button.c
 *
 *  Created on: Feb 15, 2026
 *      Author: Ohcheessyy
 */

#include "main.h"
#include "Button.h"

#define DEBOUNCE_THRESHOLD 5  // Not used anymore, but kept for reference

UI8 debounce_counter[BUTTONMAX];  // Not used, but kept
UI8 button_state[BUTTONMAX];      // State for each button: IDLE or DEBOUNCING
UI8 prevBtnState[BUTTONMAX];
UI8 currBtnState[BUTTONMAX];

UI16 button_pins[BUTTONMAX] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5};
GPIO_TypeDef* button_ports[BUTTONMAX] = {GPIOA, GPIOA, GPIOA, GPIOA, GPIOB, GPIOB};

// Button initialization function to clear previous states before use

void Button_Init(void)
{
    for (UI8 i = 0; i < BUTTONMAX; ++i)
    {
        prevBtnState[i] = OFF;
        currBtnState[i] = OFF;
        debounce_counter[i] = 0;  // Not used
        button_state[i] = BUTTON_IDLE;
    }
}

// Function to reset button states after processing

void Button_State_Reset(void)
{
    for (UI8 i = 0; i < BUTTONMAX; ++i)
    {
        prevBtnState[i] = currBtnState[i];
        currBtnState[i] = OFF;
    }
}

// Function called to scan button states with TIM3 polling for debouncing

void Button_Scan(void)
{
    for (UI8 i = 0; i < BUTTONMAX; ++i)
    {
        if (button_state[i] == BUTTON_IDLE)
        {
            GPIO_PinState pin_state = HAL_GPIO_ReadPin(button_ports[i], button_pins[i]);
            if (pin_state == GPIO_PIN_RESET)  // Button pressed
            {
                // Start debouncing timer
                __HAL_TIM_SET_COUNTER(&htim3, 0);
                HAL_TIM_Base_Start(&htim3);
                button_state[i] = BUTTON_DEBOUNCING;
            }
        }
        else if (button_state[i] == BUTTON_DEBOUNCING)
        {
            // Poll the timer
            if (__HAL_TIM_GET_COUNTER(&htim3) >= htim3.Init.Period)
            {
                // Timer expired, check button again
                HAL_TIM_Base_Stop(&htim3);
                GPIO_PinState pin_state = HAL_GPIO_ReadPin(button_ports[i], button_pins[i]);
                if (pin_state == GPIO_PIN_RESET)  // Still pressed
                {
                    currBtnState[i] = ON;
                    UI8 btn_signal = 48 + i;
                    HAL_UART_Transmit(&huart1, &btn_signal, 1, 100);
                }
                button_state[i] = BUTTON_IDLE;
            }
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{}
