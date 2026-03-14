/*
 * OLED.c
 *
 *  Created on: Mar 7, 2026
 *      Author: Ohcheessyy
 */

#include "OLED.h"
#include "ssd1306.h"
#include "Main_display_control.h"
#include "Image_bit_map.h"

CS_PIN_TypeDef CS_PIN_ARRAY[6] = {CS_PIN_0, CS_PIN_1, CS_PIN_2, CS_PIN_3, CS_PIN_4, CS_PIN_5};

UI8 flag = 0;

void OLED_Init(void);
void OLED_Main(void);

// Reset and initialize all OLED displays
void OLED_Init(void) {
    for (int i = 0; i < 6; i++) {
        ssd1306_Reset(CS_PIN_ARRAY[i]);
    }

    for (int i = 0; i < 6; i++) {
        ssd1306_Init(CS_PIN_ARRAY[i]);
    }
}

void OLED_Main(void) {
    if(flag == 0){
        ssd1306_Fill(White);
        for (int i = 0; i < 6; i++) {
            ssd1306_UpdateScreen(CS_PIN_ARRAY[i]);
        }
        flag = 1;
    }
    else{
        ssd1306_Fill(Black);
        for (int i = 0; i < 6; i++) {
            ssd1306_UpdateScreen(CS_PIN_ARRAY[i]);
        }
        flag = 0;
    }
    HAL_Delay(1000);
}

void DrawBitMap(ScreenState state)
{
    switch(state) {
        case STATE_SCREEN_1:
        ssd1306_Fill(White);
        ssd1306_DrawBitmap(0,0,bitmap_discord,128,64,Black);
        ssd1306_UpdateScreen(CS_PIN_0);
        break;

        case STATE_SCREEN_2:
        ssd1306_Fill(White);
        ssd1306_DrawBitmap(0,0,bitmap_youtube,128,64,Black);
        ssd1306_UpdateScreen(CS_PIN_1);    
        break;

        case STATE_SCREEN_3:
        ssd1306_Fill(White);
        ssd1306_DrawBitmap(0,0,bitmap_obs,128,64,Black);
        ssd1306_UpdateScreen(CS_PIN_2);    
        break;
		
		default:
    }

    
}

