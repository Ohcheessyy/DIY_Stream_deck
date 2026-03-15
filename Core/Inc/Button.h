#ifndef __BUTTON_H
#define __BUTTON_H

#include "main.h"

typedef enum
{
    BUTTON0 = 0,
    BUTTON1,
    BUTTON2,
    BUTTON3,
    BUTTON4,
    BUTTON5,
    BUTTONMAX
} Button_TypeDef;

extern UI8 prevBtnState[BUTTONMAX];
extern UI8 currBtnState[BUTTONMAX];

void Button_Init(void);
void Button_State_Reset(void);
void ClearScreen(void);

#endif /* __BUTTON_H */
