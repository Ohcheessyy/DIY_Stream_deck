/*
 * Main_display_control.c
 *
 *  Created on: Feb 22, 2026
 *      Author: Ohcheessyy
 */
#include "main.h"
#include "Main_display_control.h"
#include "Button.h"
#include "OLED.h"
#include "ssd1306.h"

void dummy_void_function(void);
UI8 dummy_UI8_function(void);
void Screen1_Entry(void);
void Screen1_Exit(void);
void Screen2_Entry(void);
void Screen2_Exit(void);
void Screen3_Entry(void);
void Screen3_Exit(void);
UI8 Judge_Button_0(void);
UI8 Judge_Button_1(void);
UI8 Judge_Button_2(void);
UI8 Judge_Button_3(void);
UI8 Judge_Button_4(void);
UI8 Judge_Button_5(void);
void State_Transition_Init(void);
void Judge_State_Transition(void);

//State change table for main 3 screens
ScreenState Current_State_Table[STATE_SCREEN_COUNT][SCREEN_EVENT_COUNT] = {
    {STATE_NO_SCREEN, STATE_NO_SCREEN, STATE_NO_SCREEN}, // From Init
    {STATE_SCREEN_1, STATE_SCREEN_3, STATE_SCREEN_2}, // From STATE_SCREEN_1
    {STATE_SCREEN_2, STATE_SCREEN_1, STATE_SCREEN_3}, // From STATE_SCREEN_2
    {STATE_SCREEN_3, STATE_SCREEN_2, STATE_SCREEN_1} // From STATE_SCREEN_3
};

AppState Current_App_Array[APP_EVENT_COUNT] = {
    STATE_NO_APP, // From APP_EVENT_NONE
    STATE_APP_1, // From APP_EVENT_BUTTON_0
    STATE_APP_2, // From APP_EVENT_BUTTON_1
    STATE_APP_3, // From APP_EVENT_BUTTON_2
    STATE_APP_4  // From APP_EVENT_BUTTON_3
};

typedef UI8 (*EventJudgeFunction)(void);

// Event judge for 3 main screens
EventJudgeFunction Event_Judge_Functions[STATE_SCREEN_COUNT][SCREEN_EVENT_COUNT] = {
    {&dummy_UI8_function, &dummy_UI8_function, &dummy_UI8_function}, // From Init
    {&dummy_UI8_function, &Judge_Button_3, &Judge_Button_5}, // From STATE_SCREEN_1
    {&dummy_UI8_function, &Judge_Button_3, &Judge_Button_5}, // From STATE_SCREEN_2
    {&dummy_UI8_function, &Judge_Button_3, &Judge_Button_5}  // From STATE_SCREEN_3
};

// Event judge for 4 apps
EventJudgeFunction App_Event_Judge_Functions[APP_EVENT_COUNT] = {
    &dummy_UI8_function, // From APP_EVENT_NONE
    &Judge_Button_0, // From APP_EVENT_BUTTON_0
    &Judge_Button_1, // From APP_EVENT_BUTTON_1
    &Judge_Button_2, // From APP_EVENT_BUTTON_2
    &Judge_Button_4  // From APP_EVENT_BUTTON_3
};

typedef void (*ScreenFunction)(void);

ScreenFunction Main_Screen_EntryFunctions[STATE_SCREEN_COUNT] = {
    &dummy_void_function, // STATE_NO_SCREEN
    &Screen1_Entry, // STATE_SCREEN_1
    &Screen2_Entry, // STATE_SCREEN_2
    &Screen3_Entry  // STATE_SCREEN_3
};

ScreenFunction Main_Screen_ExitFunctions[STATE_SCREEN_COUNT] = {
    &dummy_void_function, // STATE_NO_SCREEN
    &Screen1_Exit, // STATE_SCREEN_1
    &Screen2_Exit, // STATE_SCREEN_2
    &Screen3_Exit  // STATE_SCREEN_3
};

typedef void (*AppFunction)(void);

AppFunction Main_App_EntryFunctions[STATE_APP_COUNT] = {
    &dummy_void_function, // STATE_NO_APP
    &dummy_void_function, // STATE_APP_1
    &dummy_void_function, // STATE_APP_2
    &dummy_void_function, // STATE_APP_3
    &dummy_void_function  // STATE_APP_4
};

AppFunction Main_App_ExitFunctions[STATE_APP_COUNT] = {
    &dummy_void_function, // STATE_NO_APP
    &dummy_void_function, // STATE_APP_1
    &dummy_void_function, // STATE_APP_2
    &dummy_void_function, // STATE_APP_3
    &dummy_void_function  // STATE_APP_4
};


//Deploy this later
// typedef struct {
//     ScreenFunction EntryFunction;
//     ScreenFunction ExitFunction;
// } ScreenFunctionTable;

// ScreenFunctionTable screen_Table[STATE_SCREEN_COUNT] = {
//     {&dummy_void_function, &dummy_void_function}, // STATE_NO_SCREEN
//     {&Screen1_Entry, &Screen1_Exit}, // STATE_SCREEN_1
//     {&Screen2_Entry, &Screen2_Exit}, // STATE_SCREEN_2
//     {&Screen3_Entry, &Screen3_Exit}  // STATE_SCREEN_3
// };

ScreenState currentScreenState;
ScreenState previousScreenState;
AppState currentAppState;
AppState previousAppState;

 // Initialize the state transition system if needed
void State_Transition_Init(void) {
    currentScreenState = STATE_SCREEN_1;
    previousScreenState = STATE_SCREEN_1;
    currentAppState = STATE_NO_APP;
    previousAppState = STATE_NO_APP;
    Main_Screen_EntryFunctions[currentScreenState]();
}

// Implement logic to determine which event occurred
void Judge_State_Transition(void) {

    UI8 event_Screen = SCREEN_EVENT_NONE;
    UI8 event_App = APP_EVENT_NONE;
    UI8 result = 0;
    
    // Check each event for the main application state
    for (int i = 0; i < APP_EVENT_COUNT; i++) {
        if (event_App == APP_EVENT_NONE) {
            result = App_Event_Judge_Functions[i]();
            if (result == 1) {
                event_App = i;
            }
        }
    }

    currentAppState = Current_App_Array[event_App];

    // Implement application state transition logic here if needed
    if(currentAppState != previousAppState) {
        Main_App_EntryFunctions[previousAppState]();
    }
    
    Main_App_EntryFunctions[currentAppState]();
    
    previousAppState = currentAppState;

    // Judge condition if no Application is selected

    if(currentAppState == STATE_NO_APP) {
       
        // Check each event for the main screen state
        for (int i = 0; i < SCREEN_EVENT_COUNT; i++) {
            if (event_Screen == SCREEN_EVENT_NONE) {
                result = Event_Judge_Functions[currentScreenState][i]();
                if (result == 1) {
                    event_Screen = i;
                }
            }
        }
        
        currentScreenState = Current_State_Table[currentScreenState][event_Screen];

        if(currentScreenState != previousScreenState) {
            Main_Screen_ExitFunctions[previousScreenState]();
        }

        Main_Screen_EntryFunctions[currentScreenState]();
    
        previousScreenState = currentScreenState;
    }
}

// Implement logic to check if the button 0 was pressed
UI8 Judge_Button_0(void) {
    
    if(prevBtnState[BUTTON0] == OFF && currBtnState[BUTTON0] == ON)
    {
        return ON; // Left button event detected
    }
    return OFF;
}

// Implement logic to check if the left button was pressed
UI8 Judge_Button_1(void) {
    
    if(prevBtnState[BUTTON1] == OFF && currBtnState[BUTTON1] == ON)
    {
        return ON; // Left button event detected
    }
    return OFF;
}

// Implement logic to check if the left button was pressed
UI8 Judge_Button_2(void) {
    
    if(prevBtnState[BUTTON2] == OFF && currBtnState[BUTTON2] == ON)
    {
        return ON; // Left button event detected
    }
    return OFF;
}

// Implement logic to check if the left button was pressed
UI8 Judge_Button_3(void) {
    
    if(prevBtnState[BUTTON3] == OFF && currBtnState[BUTTON3] == ON)
    {
        return ON; // Left button event detected
    }
    return OFF;
}

// Implement logic to check if the left button was pressed
UI8 Judge_Button_4(void) {
    
    if(prevBtnState[BUTTON4] == OFF && currBtnState[BUTTON4] == ON)
    {
        return ON; // Left button event detected
    }
    return OFF;
}

// Implement logic to check if the right button was pressed
UI8 Judge_Button_5(void) {
    
    if(prevBtnState[BUTTON5] == OFF && currBtnState[BUTTON5] == ON)
    {
        return ON; // Right button event detected
    }
    return OFF;
}

void dummy_void_function(void) {
    // This function is intentionally left empty to prevent linker errors
}

UI8 dummy_UI8_function(void)
{
    // This function is intentionally left empty to prevent linker errors
    return OFF;
}

void Screen1_Entry(void) {
    // Implement the entry action for Screen 1
    DrawBitMap(currentScreenState);
}

void Screen1_Exit(void) {
    // Implement the exit action for Screen 1
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen(CS_PIN_0);
}

void Screen2_Entry(void) {
    // Implement the entry action for Screen 2
    DrawBitMap(currentScreenState);
}

void Screen2_Exit(void) {
    // Implement the exit action for Screen 2
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen(CS_PIN_1);
}

void Screen3_Entry(void) {
    // Implement the entry action for Screen 3
    DrawBitMap(currentScreenState);
}

void Screen3_Exit(void) {
    // Implement the exit action for Screen 3
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen(CS_PIN_2);
}