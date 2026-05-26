

/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

Audio.h
STM32L476RG PAM8302 Audio Driver Header File

Purpose:
Defines function prototypes for tone generation and
audio control using PA8 (PAM8302 amplifier output).
========================================================
*/

#ifndef AUDIO_H_
#define AUDIO_H_

#include "stm32l476xx.h"
#include <stdint.h>

/*======================================================
  AUDIO INITIALIZATION
======================================================*/

void Audio_Init(void);

/*
Initializes PA8 as digital output used to generate
audio signals for the PAM8302 amplifier.

Reference [1]
*/

/*======================================================
  AUDIO TONE GENERATION
======================================================*/

void Audio_Play_Tone(uint32_t frequency,
                     uint32_t duration_ms);

/*
Generates a square-wave tone.

Parameters:
- frequency: tone frequency in Hz
- duration_ms: playback duration in milliseconds

Core relation used internally [8]:

T = 1 / f

Where:
T = period of waveform
f = frequency
*/

/*======================================================
  MELODY PLAYBACK
======================================================*/

void Audio_Play_Melody(void);

/*
Plays a predefined sequence of musical notes.

Used for:
- system startup sound
- notification melody

Musical frequency mapping based on standard tuning [9]
*/

/*======================================================
  MUSIC CONTROL FUNCTIONS
======================================================*/

void Start_Music(void);

/*
Starts playback of predefined melody sequence.
*/

void Stop_Music(void);

/*
Stops audio output immediately by disabling PA8 signal.
*/

/*======================================================
  LEGACY / COMMENTED FUNCTIONS
======================================================*/

/*
static void delay_us(uint32_t us);

Previously used microsecond delay function for:
- manual PWM generation
- timing control

Now replaced by SysTick-based delay system.
*/

#endif
