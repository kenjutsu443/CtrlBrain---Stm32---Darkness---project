/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

Systick_timer.h
STM32L476RG SysTick Timer Driver Header File

Purpose:
Defines system tick timing functions for millisecond
delays and global time tracking using SysTick.
========================================================
*/

#ifndef SYSTICK_TIMER_H_
#define SYSTICK_TIMER_H_

#include "stm32l476xx.h"
#include <stdint.h>

/*======================================================
  GLOBAL SYSTEM TICK VARIABLE
======================================================*/

extern volatile uint32_t msTicks;

/*
msTicks:
- Global millisecond counter
- Incremented inside SysTick interrupt handler
- Used for delay timing and system scheduling [1]
*/

/*======================================================
  FUNCTION PROTOTYPES
======================================================*/

void SysTick_Init(void);

/*
Initializes SysTick timer to generate periodic interrupts.

Used for:
- system time base
- delay generation
- real-time control loops

Reference [2]
*/

void delay_ms(uint32_t ms);

/*
Blocking delay function using msTicks counter.

Implements busy-wait timing mechanism [3]:

Wait until:
(msTicks - start_time) >= delay
*/

#endif
