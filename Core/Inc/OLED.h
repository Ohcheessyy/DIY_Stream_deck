/*
 * OLED.h
 *
 *  Created on: Mar 7, 2026
 *      Author: Ohcheessyy
 */

#ifndef INC_OLED_H_
#define INC_OLED_H_

#include "main.h"

typedef enum{
    CS_PIN_0 = GPIO_PIN_0,
    CS_PIN_1 = GPIO_PIN_1,
    CS_PIN_2 = GPIO_PIN_2,
    CS_PIN_3 = GPIO_PIN_6,
    CS_PIN_4 = GPIO_PIN_7,
    CS_PIN_5 = GPIO_PIN_8
}CS_PIN_TypeDef;

void OLED_Init(void);
void OLED_Main(void);

#endif /* INC_OLED_H_ */
