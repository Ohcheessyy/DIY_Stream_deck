/*
 * Main_display_control.h
 *
 *  Created on: Feb 22, 2026
 *      Author: Ohcheessyy
 */

#ifndef INC_DISPLAY_CONTROL_H_
#define INC_DISPLAY_CONTROL_H_

#include "main.h"

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

void State_Transition_Init(void);
void Judge_State_Transition(void);


#endif /* INC_DISPLAY_CONTROL_H_ */
