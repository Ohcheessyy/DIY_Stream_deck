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
void DrawScreenState(ScreenState state);
void ClearScreen(void);

// Reset and initialize all OLED displays
void OLED_Init(void) {
    for (int i = 0; i < 6; i++) {
        ssd1306_Reset(CS_PIN_ARRAY[i]);
    }

    for (int i = 0; i < 6; i++) {
        ssd1306_Init(CS_PIN_ARRAY[i]);
    }
}

void DrawScreenState(ScreenState state)
{
    switch(state) {
        case STATE_SCREEN_1:
        ssd1306_Fill(Black);
        ssd1306_DrawBitmap(0,0,bitmap_discord,128,64,White);
        ssd1306_UpdateScreen(CS_PIN_0);
        
        ssd1306_Fill(Black);
        ssd1306_DrawBitmap(0,0,bitmap_youtube,128,64,White);
        ssd1306_UpdateScreen(CS_PIN_1); 

        ssd1306_Fill(Black);
        ssd1306_DrawBitmap(0,0,bitmap_obs,128,64,White);
        ssd1306_UpdateScreen(CS_PIN_2);

        ssd1306_Fill(Black);
        ssd1306_DrawBitmap(0,0,bitmap_left_arrow,128,64,White);
        ssd1306_UpdateScreen(CS_PIN_3);

        ssd1306_Fill(Black);
        ssd1306_DrawBitmap(0,0,bitmap_right_arrow,128,64,White);
        ssd1306_UpdateScreen(CS_PIN_5);
        
        break;

        case STATE_SCREEN_2:
        ssd1306_Fill(Black);
        ssd1306_DrawBitmap(0,0,bitmap_valorant,128,64,White);
        ssd1306_UpdateScreen(CS_PIN_0);  
        
        ssd1306_Fill(Black);
        ssd1306_DrawBitmap(0,0,bitmap_steam,128,64,White);
        ssd1306_UpdateScreen(CS_PIN_1);

        ssd1306_Fill(Black);
        ssd1306_DrawBitmap(0,0,bitmap_left_arrow,128,64,White);
        ssd1306_UpdateScreen(CS_PIN_3);

        ssd1306_Fill(Black);
        ssd1306_DrawBitmap(0,0,bitmap_right_arrow,128,64,White);
        ssd1306_UpdateScreen(CS_PIN_5);
        break;

        case STATE_SCREEN_3:
        ssd1306_Fill(Black);
        ssd1306_DrawBitmap(0,0,bitmap_vs_code,128,64,White);
        ssd1306_UpdateScreen(CS_PIN_0);    
        
        ssd1306_Fill(Black);
        ssd1306_DrawBitmap(0,0,bitmap_left_arrow,128,64,White);
        ssd1306_UpdateScreen(CS_PIN_3);

        ssd1306_Fill(Black);
        ssd1306_DrawBitmap(0,0,bitmap_right_arrow,128,64,White);
        ssd1306_UpdateScreen(CS_PIN_5);

        break;
		
		default:
    }

    
}

void ClearScreen(void)
{
    for(int i = 0; i < 6; i++){
        ssd1306_Fill(Black);
        ssd1306_UpdateScreen(CS_PIN_ARRAY[i]);
    }
}