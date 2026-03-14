/*
 * Main_display_control.h
 *
 *  Created on: Feb 22, 2026
 *      Author: Ohcheessyy
 */

#ifndef INC_DISPLAY_CONTROL_H_
#define INC_DISPLAY_CONTROL_H_

#include "main.h"
#include "App_display_control.h"

typedef enum {
    MODE_NONE = 0,
    MODE_CHOOSE_APP,
    MODE_CHOOSE_FCTN
} Mode;

// Event when changeing screen
typedef enum {
    SCREEN_EVENT_NONE = 0,
    SCREEN_EVENT_LEFT_BUTTON,
    SCREEN_EVENT_RIGHT_BUTTON,
    SCREEN_EVENT_COUNT
} ScreenEvent;

// State for main 3 screens
typedef enum {
    STATE_NO_SCREEN = 0,
    STATE_SCREEN_1,
    STATE_SCREEN_2,
    STATE_SCREEN_3,
    STATE_SCREEN_COUNT
} ScreenState;

//Button for changing application
typedef enum {
    APP_EVENT_NONE = 0,
    APP_EVENT_BUTTON_0,
    APP_EVENT_BUTTON_1,
    APP_EVENT_BUTTON_2,
    APP_EVENT_BUTTON_3,
    APP_EVENT_COUNT
} AppEvent;

// State for main 4 applications
typedef enum {
    STATE_NO_APP = 0,
    STATE_APP_1,
    STATE_APP_2,
    STATE_APP_3,
    STATE_APP_4,
    STATE_APP_COUNT
} AppState;

typedef UI8 (*EventJudgeFunction)(void);
typedef void (*ScreenFunction)(void);
typedef void (*AppFunction)(void);

extern Mode currScrMode;
extern Mode prevScrMode;
extern ScreenState currScrState;
extern ScreenState prevScnState;
extern AppState currAppState;
extern AppState prevAppState;
extern AppScreenState currAScrState;
extern AppScreenState prevAScnState;

void dummy_void_func(void);
UI8 dummy_UI8_func(void);
void State_Trans_Init(void);
void Jdg_State_Transition(void);
UI8 Jdg_Btn_0(void);
UI8 Jdg_Btn_1(void);
UI8 Jdg_Btn_2(void);
UI8 Jdg_Btn_3(void);
UI8 Jdg_Btn_4(void);
UI8 Jdg_Btn_5(void);

#endif /* INC_DISPLAY_CONTROL_H_ */
