/*
 * App1_display_control.c
 *
 *  Created on: Mar 11, 2026
 *      Author: Ohcheessyy
 */

#include "App_display_control.h"
#include "main.h"
#include "Main_display_control.h"
#include "Image_bit_map.h"
#include "ssd1306.h"
#include "OLED.h"

void Jdg_App_State_Transition(AppScreenState *currState, AppScreenState *prevState);
void Btn0_Fctn();
void AppScrn1_Entry(void);
void AppScrn2_Entry(void);
void AppScrn1_Exit(void);
void AppScrn2_Exit(void);
void AppScrn_Operation(AppScreenState currState, AppScreenState prevState);

//State change table for main 3 screens
AppScreenState AppScrn_State_Table[APP_STATE_SCREEN_COUNT][APP_SCREEN_EVENT_COUNT] = {
    {APP_STATE_NO_SCREEN, APP_STATE_NO_SCREEN, APP_STATE_NO_SCREEN}, // From Init
    {APP_STATE_SCREEN_1, APP_STATE_SCREEN_2, APP_STATE_SCREEN_2}, // From APP_STATE_SCREEN_1
    {APP_STATE_SCREEN_2, APP_STATE_SCREEN_1, APP_STATE_SCREEN_1} // From APP_STATE_SCREEN_2
};

EventJudgeFunction AppScrn_Event_Jdg_Table[APP_STATE_SCREEN_COUNT][APP_SCREEN_EVENT_COUNT] = {
    {&dummy_UI8_func, &dummy_UI8_func, dummy_UI8_func},
    {&dummy_UI8_func, &Jdg_Btn_3, Jdg_Btn_5},
    {&dummy_UI8_func, &Jdg_Btn_3, Jdg_Btn_5}
};

EventJudgeFunction Fctn_Jdg_Arr[FUNC_EVENT_COUNT] = {
    &dummy_UI8_func,
    &Jdg_Btn_0, // From FUNC_EVENT_BUTTON_0
    &Jdg_Btn_1, // From FUNC_EVENT_BUTTON_1
    &Jdg_Btn_2, // From FUNC_EVENT_BUTTON_2
    &Jdg_Btn_4  // From FUNC_EVENT_BUTTON_3
};

AppFunction AppScrn_EntryFunc[APP_STATE_SCREEN_COUNT] = {
    &dummy_void_func,
    &AppScrn1_Entry,
    &AppScrn2_Entry
};

AppFunction AppScrn_ExitFunc[APP_STATE_SCREEN_COUNT] = {
    &dummy_void_func,
    &AppScrn1_Exit,
    &AppScrn2_Exit
};

FuncFunction Fctn_DoFucntion[FUNC_EVENT_COUNT] = {
    &dummy_void_func,
    &Btn0_Fctn,
    &dummy_void_func,
    &dummy_void_func,
    &dummy_void_func
};

void Jdg_App_State_Transition(AppScreenState *currState, AppScreenState *prevState)
{
    UI8 event_AppScrn = APP_SCREEN_EVENT_NONE;
    UI8 result_AppScrn = 0;

    // Check each event for the main application state
    for (int i = 0; i < APP_SCREEN_EVENT_COUNT; i++) {
        if (event_AppScrn == APP_SCREEN_EVENT_NONE) {
            result_AppScrn = AppScrn_Event_Jdg_Table[*currState][i]();
            if (result_AppScrn == 1) {
                event_AppScrn = i;
            }
        }
    }

    *currState = AppScrn_State_Table[*currState][event_AppScrn];
    AppScrn_Operation(*currState, *prevState);
    *prevState = *currState;

}

void Jdg_Fctn_Event(void)
{
    UI8 event_Fctn = 0;
    UI8 result_Fctn = 0;

    for (int i = 0; i < FUNC_EVENT_COUNT; i++) {
        if (event_Fctn == 0) {
            result_Fctn = Fctn_Jdg_Arr[i]();
            if (result_Fctn == 1) {
                event_Fctn = i;
            }
        }
    }

    Fctn_DoFucntion[event_Fctn]();

}

void AppScrn_Operation(AppScreenState currState, AppScreenState prevState){
    
    if(currState != prevState) {
        AppScrn_ExitFunc[prevState]();
    }
    
    AppScrn_EntryFunc[currState]();
}

void Btn0_Fctn(void)
{
    currScrMode = MODE_CHOOSE_APP;
}

void AppScrn1_Entry(void)
{
    ssd1306_Fill(Black);
    ssd1306_DrawBitmap(0,0,bitmap_go_back_arrow,128,64,White);
    ssd1306_UpdateScreen(CS_PIN_0);
}

void AppScrn2_Entry(void)
{
    ssd1306_Fill(Black);
    ssd1306_DrawBitmap(0,0,bitmap_microphone_black_shape,128,64,White);
    ssd1306_UpdateScreen(CS_PIN_1);
}

void AppScrn1_Exit(void)
{
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen(CS_PIN_0);
}

void AppScrn2_Exit(void)
{
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen(CS_PIN_1);
}

void AppScrn_EntryFctn_IF()
{
    AppScrn_EntryFunc[currAScrState]();
}

void AppScrn_ExitFctn_IF(AppScreenState currState)
{
    AppScrn_ExitFunc[currState]();
}