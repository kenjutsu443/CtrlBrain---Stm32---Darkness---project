
/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

Button.h
STM32L476RG Push Button Driver Header File

Purpose:
Defines function prototypes for reading and initializing
push button input on PC13.
========================================================
*/

#ifndef BUTTON_H_
#define BUTTON_H_

#include "stm32l476xx.h"

/*======================================================
  BUTTON INITIALIZATION FUNCTION
======================================================*/

void Button_Init(void);

/*
Configures PC13 as digital input with internal pull-up
resistor enabled.

Reference [1]
*/

/*======================================================
  BUTTON STATE FUNCTION
======================================================*/

uint8_t Button_Pressed(void);

/*
Reads push button state from PC13.

Returns:
- 1 = button pressed (LOW state due to pull-up)
- 0 = button not pressed (HIGH state)

Logic behavior based on GPIO input register [1]
*/

#endif
