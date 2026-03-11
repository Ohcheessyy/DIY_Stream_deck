/*
 * Main_display_control.c
 *
 *  Created on: Feb 22, 2026
 *      Author: Ohcheessyy
 */
#include "main.h"
#include "Display_control.h"
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
UI8 Judge_Left_Button(void);
UI8 Judge_Right_Button(void);
void State_Transition_Init(void);
void Judge_State_Transition(void);

typedef enum {
    EVENT_NONE = 0,
    EVENT_LEFT,
    EVENT_RIGHT,
    EVENT_COUNT
} ScreenEvent;

typedef enum {
    STATE_NO_SCREEN = 0,
    STATE_SCREEN_1,
    STATE_SCREEN_2,
    STATE_SCREEN_3,
    STATE_SCREEN_COUNT
} ScreenState;


ScreenState Current_State_Table[STATE_SCREEN_COUNT][EVENT_COUNT] = {
    {STATE_NO_SCREEN, STATE_NO_SCREEN, STATE_NO_SCREEN}, // From Init
    {STATE_SCREEN_1, STATE_SCREEN_3, STATE_SCREEN_2}, // From STATE_SCREEN_1
    {STATE_SCREEN_2, STATE_SCREEN_1, STATE_SCREEN_3}, // From STATE_SCREEN_2
    {STATE_SCREEN_3, STATE_SCREEN_2, STATE_SCREEN_1}  // From STATE_SCREEN_3
};

typedef UI8 (*EventJudgeFunction)(void);

EventJudgeFunction Event_Judge_Functions[STATE_SCREEN_COUNT][EVENT_COUNT] = {
    {&dummy_UI8_function, &dummy_UI8_function, &dummy_UI8_function}, // From Init
    {&dummy_UI8_function, &Judge_Left_Button, &Judge_Right_Button}, // From STATE_SCREEN_1
    {&dummy_UI8_function, &Judge_Left_Button, &Judge_Right_Button}, // From STATE_SCREEN_2
    {&dummy_UI8_function, &Judge_Left_Button, &Judge_Right_Button}  // From STATE_SCREEN_3
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

typedef struct {
    ScreenFunction EntryFunction;
    ScreenFunction ExitFunction;
} ScreenFunctionTable;

ScreenFunctionTable screen_Table[STATE_SCREEN_COUNT] = {
    {&dummy_void_function, &dummy_void_function}, // STATE_NO_SCREEN
    {&Screen1_Entry, &Screen1_Exit}, // STATE_SCREEN_1
    {&Screen2_Entry, &Screen2_Exit}, // STATE_SCREEN_2
    {&Screen3_Entry, &Screen3_Exit}  // STATE_SCREEN_3
};

ScreenState currentState;
ScreenState previousState;

 // Initialize the state transition system if needed
void State_Transition_Init(void) {
    currentState = STATE_SCREEN_1;
    previousState = STATE_SCREEN_1;
    screen_Table[currentState].EntryFunction();
}

// Implement logic to determine which event occurred
void Judge_State_Transition(void) {

    UI8 event_no = EVENT_NONE;
    UI8 result = 0;

    for (int i = 0; i < EVENT_COUNT; i++) {
        if (event_no == EVENT_NONE) {
            result = Event_Judge_Functions[currentState][i]();
            if (result == 1) {
                event_no = i;
            }
        }
    }
    
    currentState = Current_State_Table[currentState][event_no];

    if(currentState != previousState) {
        Main_Screen_ExitFunctions[previousState]();
    }

    Main_Screen_EntryFunctions[currentState]();
    
    previousState = currentState;

}

// Implement logic to check if the left button was pressed
UI8 Judge_Left_Button(void) {
    
    if(prevBtnState[BUTTON3] == OFF && currBtnState[BUTTON3] == ON)
    {
        return ON; // Left button event detected
    }
    return OFF;
}

// Implement logic to check if the right button was pressed
UI8 Judge_Right_Button(void) {
    
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
    DrawBitMap();
}

void Screen1_Exit(void) {
    // Implement the exit action for Screen 1
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen(CS_PIN_0);
}

void Screen2_Entry(void) {
    // Implement the entry action for Screen 2
    ssd1306_Fill(White);
    ssd1306_UpdateScreen(CS_PIN_1);
}

void Screen2_Exit(void) {
    // Implement the exit action for Screen 2
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen(CS_PIN_1);
}

void Screen3_Entry(void) {
    // Implement the entry action for Screen 3
    ssd1306_Fill(White);
    ssd1306_UpdateScreen(CS_PIN_2);
}

void Screen3_Exit(void) {
    // Implement the exit action for Screen 3
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen(CS_PIN_2);
}