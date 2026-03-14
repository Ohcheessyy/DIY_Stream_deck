/*
 * App1_display_control.h
 *
 *  Created on: Mar 11, 2026
 *      Author: Ohcheessyy
 */

#ifndef INC_APP1_DISPLAY_CONTROL_H_
#define INC_APP1_DISPLAY_CONTROL_H_

typedef enum {
    APP_SCREEN_EVENT_NONE = 0,
    APP_SCREEN_EVENT_LEFT_BUTTON,
    APP_SCREEN_EVENT_RIGHT_BUTTON,
    APP_SCREEN_EVENT_COUNT
} ScreenAppEvent;

typedef enum {
    APP_STATE_NO_SCREEN = 0,
    APP_STATE_SCREEN_1,
    APP_STATE_SCREEN_2,
    APP_STATE_SCREEN_COUNT
} AppScreenState;

typedef enum {
    FUNC_EVENT_NONE = 0,
    FUNC_EVENT_BUTTON_0,
    FUNC_EVENT_BUTTON_1,
    FUNC_EVENT_BUTTON_2,
    FUNC_EVENT_BUTTON_3,
    FUNC_EVENT_COUNT
} FuncEvent;

typedef void (*FuncFunction)(void);
void Jdg_App_State_Transition(AppScreenState *currState, AppScreenState *prevState);
void AppScrn1_Entry(void);
void AppScrn_EntryFctn_IF();
void Jdg_Fctn_Event(void);

#endif /* INC_APP1_DISPLAY_CONTROL_H_ */
