

/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

LED.h
STM32L476RG LED Driver Header File

Purpose:
Defines function prototypes for controlling LED output
on PA6 (digital output control).
========================================================
*/

#ifndef LED_H_
#define LED_H_

#include "stm32l476xx.h"

/*======================================================
  LED INITIALIZATION
======================================================*/

void LED_Init();

/*
Configures PA6 as digital output pin for LED control.

Reference [1]
*/

/*======================================================
  LED CONTROL FUNCTIONS
======================================================*/

void toggle_LED();

/*
Toggles LED state using XOR operation.

Used for blinking or status indication.
*/

void turn_off_LED();

/*
Sets PA6 LOW to turn OFF LED.
*/

void turn_on_LED();

/*
Sets PA6 HIGH to turn ON LED.
*/

#endif
