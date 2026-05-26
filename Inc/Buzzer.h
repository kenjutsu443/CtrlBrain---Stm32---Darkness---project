
/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

Buzzer.h
STM32L476RG Passive Buzzer Driver Header File

Purpose:
Defines function prototypes for controlling a passive
buzzer and generating audio tones using PA7.
========================================================
*/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "stm32l476xx.h"
#include <stdint.h>

/*======================================================
  BUZZER INITIALIZATION
======================================================*/

void Buzzer_Init(void);

/*
Configures PA7 as digital output for buzzer control.

Reference [1]
*/

/*======================================================
  BUZZER CONTROL FUNCTIONS
======================================================*/

void Buzzer_On(void);

/*
Sets PA7 HIGH to activate buzzer output.
*/

void Buzzer_Off(void);

/*
Sets PA7 LOW to deactivate buzzer output.
*/

/*======================================================
  BUZZER TONE GENERATION
======================================================*/

void Buzzer_Play_Tone(uint32_t frequency,
                      uint32_t duration_ms);

/*
Generates square wave signal to drive passive buzzer.

Parameters:
- frequency: tone frequency in Hz
- duration_ms: duration in milliseconds

Internal principle [8]:

T = 1 / f

Where:
T = waveform period
f = frequency
*/

#endif
