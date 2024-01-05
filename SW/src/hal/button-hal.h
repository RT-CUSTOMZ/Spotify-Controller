#pragma once
#include "pinconfig.h"
#include "periphery/button.h"

/*
Called on Interrupt on Pin button_left and sets a changed flag for the button.
*/
void OnButtonLeftPress();

/*
Called on Interrupt on Pin button_middle and sets a changed flag for the button.
*/
void OnButtonMiddlePress();

/*
Called on Interrupt on Pin button_right and sets a changed flag for the button.
*/
void OnButtonRightPress();

/*
Called on Interrupt on Pin encoder_clk and sets a changed flag for the button.
*/
void OnButtonEncoderPress();

/*
Initializes the counter of each button and attaches Interrupts to the correspondent Pin. 
*/
void InitButtons();

/*
Of a Button Changed, the Function handles what shall be done in each case and resets 
the flag that shows that an interrupt happended. Moreover the Time is reset on the pressed
button (which will be checked repeatedly to help debouncing the Buttons).
*/
void ButtonLoop();

