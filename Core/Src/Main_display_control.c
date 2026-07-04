/*
 * Main_display_control.c
 *
 *  Created on: Feb 22, 2026
 *      Author: Ohcheessyy
 */

#include "Main_display_control.h"
#include "main.h"
#include "Button.h"
#include "OLED.h"
#include "ssd1306.h"
#include "App_display_control.h"
#include "Image_bit_map.h"
#include <string.h>

void dummy_void_func(void);
UI8 dummy_UI8_func(void);
void Screen1_Entry(void);
void Screen1_Exit(void);
void Screen2_Entry(void);
void Screen2_Exit(void);
void Screen3_Entry(void);
void Screen3_Exit(void);
UI8 Jdg_Btn_0(void);
UI8 Jdg_Btn_1(void);
UI8 Jdg_Btn_2(void);
UI8 Jdg_Btn_3(void);
UI8 Jdg_Btn_4(void);
UI8 Jdg_Btn_5(void);
void State_Trans_Init(void);
void Jdg_Transition(void);
void Scrn_Operation(void);
void Main_Operation(void);
void Update_Scrn_State(void);
void Btn0_AFctn(void);
void Btn1_AFctn(void);
void Btn2_AFctn(void);
void Btn4_AFctn(void);

//State change table for main 3 screens
ScreenState MScrn_State_Table[STATE_SCREEN_COUNT][SCREEN_EVENT_COUNT] = {
    {STATE_NO_SCREEN, STATE_NO_SCREEN, STATE_NO_SCREEN}, // From Init
    {STATE_SCREEN_1, STATE_SCREEN_3, STATE_SCREEN_2}, // From STATE_SCREEN_1
    {STATE_SCREEN_2, STATE_SCREEN_1, STATE_SCREEN_3}, // From STATE_SCREEN_2
    {STATE_SCREEN_3, STATE_SCREEN_2, STATE_SCREEN_1} // From STATE_SCREEN_3
};

//Array for which application have been choosen
AppState App_Array[APP_EVENT_COUNT] = {
    STATE_NO_APP, // From APP_EVENT_NONE
    STATE_APP_1, // From APP_EVENT_BUTTON_0
    STATE_APP_2, // From APP_EVENT_BUTTON_1
    STATE_APP_3, // From APP_EVENT_BUTTON_2
    STATE_APP_4  // From APP_EVENT_BUTTON_3
};

// Event judge for 3 main screens
EventJudgeFunction MScrn_Event_Jdg_Func[STATE_SCREEN_COUNT][SCREEN_EVENT_COUNT] = {
    {&dummy_UI8_func, &dummy_UI8_func, &dummy_UI8_func}, // From Init
    {&dummy_UI8_func, &Jdg_Btn_3, &Jdg_Btn_5}, // From STATE_SCREEN_1
    {&dummy_UI8_func, &Jdg_Btn_3, &Jdg_Btn_5}, // From STATE_SCREEN_2
    {&dummy_UI8_func, &Jdg_Btn_3, &Jdg_Btn_5}  // From STATE_SCREEN_3
};

// Event judge for 4 apps
EventJudgeFunction App_Event_Jdg_Func[APP_EVENT_COUNT] = {
    &dummy_UI8_func, // From APP_EVENT_NONE
    &Jdg_Btn_0, // From APP_EVENT_BUTTON_0
    &Jdg_Btn_1, // From APP_EVENT_BUTTON_1
    &Jdg_Btn_2, // From APP_EVENT_BUTTON_2
    &Jdg_Btn_4  // From APP_EVENT_BUTTON_3
};

ScreenFunction Main_Scrn_EntryFunc[STATE_SCREEN_COUNT] = {
    &dummy_void_func, // STATE_NO_SCREEN
    &Screen1_Entry, // STATE_SCREEN_1
    &Screen2_Entry, // STATE_SCREEN_2
    &Screen3_Entry  // STATE_SCREEN_3
};

ScreenFunction Main_Scrn_ExitFunc[STATE_SCREEN_COUNT] = {
    &dummy_void_func, // STATE_NO_SCREEN
    &Screen1_Exit, // STATE_SCREEN_1
    &Screen2_Exit, // STATE_SCREEN_2
    &Screen3_Exit  // STATE_SCREEN_3
};

AFuncFunction AFctn_DoFunction[APP_EVENT_COUNT] = {
    &dummy_void_func,
    &Btn0_AFctn,
    &Btn1_AFctn,
    &Btn2_AFctn,
    &Btn4_AFctn
};

//Deploy this later
// typedef struct {
//     ScreenFunction EntryFunction;
//     ScreenFunction ExitFunction;
// } ScreenFunctionTable;

// ScreenFunctionTable screen_Table[STATE_SCREEN_COUNT] = {
//     {&dummy_void_func, &dummy_void_func}, // STATE_NO_SCREEN
//     {&Screen1_Entry, &Screen1_Exit}, // STATE_SCREEN_1
//     {&Screen2_Entry, &Screen2_Exit}, // STATE_SCREEN_2
//     {&Screen3_Entry, &Screen3_Exit}  // STATE_SCREEN_3
// };
Mode currScrMode;
Mode prevScrMode;
ScreenState currScrState;
ScreenState prevScrState;
AppState currAppState;
AppState prevAppState;
AppScreenState currAScrState;
AppScreenState prevAScrState;

 // Initialize the state transition system
void State_Trans_Init(void) {
    currScrMode = MODE_CHOOSE_APP;
    prevScrMode = MODE_CHOOSE_APP;
    currScrState = STATE_SCREEN_1;
    prevScrState = STATE_SCREEN_1;
    currAppState = STATE_NO_APP;
    prevAppState = STATE_NO_APP;
    currAScrState = APP_STATE_SCREEN_1;
    prevAScrState = APP_STATE_SCREEN_1;
    Main_Scrn_EntryFunc[currScrState]();
}

void Main_Operation(){
    if(currScrMode == MODE_CHOOSE_APP){
        Jdg_Scrn_State_Trans();
    }
    else{
        Jdg_App_State_Transition(&currAScrState, &prevAScrState);
        Jdg_Fctn_Event();
    }

    if(currScrMode == MODE_CHOOSE_APP){
        Scrn_Operation();
        Update_Scrn_State();
    }
    else{
        AppScrn_Operation(&currAScrState, &prevAScrState);
        Update_AppScrn_State(&currAScrState, &prevAScrState);
    }
}

// Implement logic to determine which event occurred
void Jdg_Scrn_State_Trans(void) {

    UI8 event_Screen = SCREEN_EVENT_NONE;
    UI8 event_App = APP_EVENT_NONE;
    UI8 result_Screen = OFF;
    UI8 result_App = OFF;

    if(currScrMode == MODE_CHOOSE_APP) {                                    // Judge condition if no Application is selected         
        
        for (int i = 0; i < APP_EVENT_COUNT; i++) {                         // Check each event for the main application state
            if (event_App == APP_EVENT_NONE) {
                result_App = App_Event_Jdg_Func[i]();
                if (result_App == ON) {
                    event_App = i;
                }
            }
        }
        if(event_App != APP_EVENT_NONE){
            currAppState = App_Array[event_App];                            //Update current Applcation State
            currScrMode = MODE_CHOOSE_FCTN;
            AFctn_DoFunction[event_App]();
        }                                       

        for (int i = 0; i < SCREEN_EVENT_COUNT; i++) {                      // Check each event for the main screen state
            if (event_Screen == SCREEN_EVENT_NONE) {
                result_Screen = MScrn_Event_Jdg_Func[currScrState][i]();
                if (result_Screen == ON) {
                    event_Screen = i;
                }
            }
        }
        
        currScrState = MScrn_State_Table[currScrState][event_Screen];       //Update current Screen State
    }
}

void Scrn_Operation(void){

    Main_Scrn_ExitFunc[prevScrState]();
    Main_Scrn_EntryFunc[currScrState]();

}

void Update_Scrn_State(void){
    if(currAppState != prevAppState){
        prevAppState = currAppState;
    }
}

// Implement logic to check if the button 0 was pressed
UI8 Jdg_Btn_0(void) {
    
    if(prevBtnState[BUTTON0] == OFF && currBtnState[BUTTON0] == ON)
    {
        return ON; // Left button event detected
    }
    return OFF;
}

// Implement logic to check if the left button was pressed
UI8 Jdg_Btn_1(void) {
    
    if(prevBtnState[BUTTON1] == OFF && currBtnState[BUTTON1] == ON)
    {
        return ON; // Left button event detected
    }
    return OFF;
}

// Implement logic to check if the left button was pressed
UI8 Jdg_Btn_2(void) {
    
    if(prevBtnState[BUTTON2] == OFF && currBtnState[BUTTON2] == ON)
    {
        return ON; // Left button event detected
    }
    return OFF;
}

// Implement logic to check if the left button was pressed
UI8 Jdg_Btn_3(void) {
    
    if(prevBtnState[BUTTON3] == OFF && currBtnState[BUTTON3] == ON)
    {
        return ON; // Left button event detected
    }
    return OFF;
}

// Implement logic to check if the left button was pressed
UI8 Jdg_Btn_4(void) {
    
    if(prevBtnState[BUTTON4] == OFF && currBtnState[BUTTON4] == ON)
    {
        return ON; // Left button event detected
    }
    return OFF;
}

// Implement logic to check if the right button was pressed
UI8 Jdg_Btn_5(void) {
    
    if(prevBtnState[BUTTON5] == OFF && currBtnState[BUTTON5] == ON)
    {
        return ON; // Right button event detected
    }
    return OFF;
}

void dummy_void_func(void) {
    // This function is intentionally left empty to prevent linker errors
}

UI8 dummy_UI8_func(void)
{
    // This function is intentionally left empty to prevent linker errors
    return OFF;
}

void Screen1_Entry(void) {
    // Implement the entry action for Screen 1
    DrawScreenState(currScrState);
}

void Screen1_Exit(void) {
    // Implement the exit action for Screen 1
    ClearScreen();
}

void Screen2_Entry(void) {
    // Implement the entry action for Screen 2
    DrawScreenState(currScrState);
}

void Screen2_Exit(void) {
    // Implement the exit action for Screen 2
    ClearScreen();
}

void Screen3_Entry(void) {
    // Implement the entry action for Screen 3
    DrawScreenState(currScrState);
}

void Screen3_Exit(void) {
    // Implement the exit action for Screen 3
    ClearScreen();
}

void Btn0_AFctn(void)
{
    char msg[10];
    switch (currScrState) {
        case STATE_SCREEN_1:
            strcpy(msg, "D");
            HAL_UART_Transmit(&huart1, (UI8*)msg , strlen(msg), 100);
            break;
        case STATE_SCREEN_2:
            strcpy(msg, "V");
            HAL_UART_Transmit(&huart1, (UI8*)msg , strlen(msg), 100);
            break;               
        case STATE_SCREEN_3:
            strcpy(msg, "VS");
            HAL_UART_Transmit(&huart1, (UI8*)msg , strlen(msg), 100);
            break;        
        default:
            break;
    }
}

void Btn1_AFctn(void)
{
    char msg[10];
    switch (currScrState) {
        case STATE_SCREEN_1:
            strcpy(msg, "YT");
            HAL_UART_Transmit(&huart1, (UI8*)msg , strlen(msg), 100);
            break;
        case STATE_SCREEN_2:
            strcpy(msg, "S");
            HAL_UART_Transmit(&huart1, (UI8*)msg , strlen(msg), 100);
            break;               
        case STATE_SCREEN_3:
        default:
            break;
    }
}

void Btn2_AFctn(void)
{
    char msg[10];
    switch (currScrState) {
        case STATE_SCREEN_1:
            strcpy(msg, "O");
            HAL_UART_Transmit(&huart1, (UI8*)msg , strlen(msg), 100);
            break;
        case STATE_SCREEN_2:            
        case STATE_SCREEN_3:
        default:
            break;
    }
}

void Btn4_AFctn(void)
{
    switch (currScrState) {
        case STATE_SCREEN_1:
        case STATE_SCREEN_2:            
        case STATE_SCREEN_3:
        default:
            break;
    }
}