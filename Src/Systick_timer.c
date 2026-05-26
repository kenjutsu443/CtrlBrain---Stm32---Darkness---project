/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

Systick_timer.c
STM32L476RG SysTick Timer Driver

Purpose:
Provides millisecond timing, delays, and system tick
interrupt management for real-time embedded control.
========================================================
*/

#include "Systick_timer.h"
#include "LED.h"
#include "Buzzer.h"

/*======================================================
  GLOBAL SYSTEM TICK VARIABLE
======================================================*/

extern volatile uint32_t msTicks;

// External declaration used across multiple files [1]

volatile uint32_t msTicks = 0;

/*
msTicks:
- Global millisecond counter
- Incremented by SysTick interrupt
- Used for delay timing functions
*/

/*======================================================
  SYSTICK INITIALIZATION
======================================================*/

void SysTick_Init(void)
{
    /*==================================================
      DISABLE SYSTICK
    ==================================================*/

    SysTick->CTRL = 0;

    /*
    Disable SysTick counter before configuration [2]

    Prevents unintended interrupts during setup.
    */

    /*==================================================
      SET RELOAD VALUE
    ==================================================*/

    SysTick->LOAD = 4000 - 1;

    /*
    Reload value determines interrupt period [2]

    Formula:
    Time Interval =
    (LOAD + 1) / System Clock Frequency

    This generates ~1ms tick (depends on clock).
    */

    /*==================================================
      CLEAR CURRENT VALUE
    ==================================================*/

    SysTick->VAL = 0;

    /*
    Reset current counter value [2]

    Ensures clean starting point for timer.
    */

    /*==================================================
      ENABLE INTERRUPT
    ==================================================*/

    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

    /*
    Enable SysTick interrupt request [2]

    Allows SysTick_Handler() to execute.
    */

    /*==================================================
      SELECT CLOCK SOURCE
    ==================================================*/

    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;

    /*
    Select processor clock (AHB) [2]

    Provides stable timing source.
    */

    /*==================================================
      ENABLE SYSTICK
    ==================================================*/

    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    /*
    Start SysTick counter [2]
    */
}

/*======================================================
  SYSTICK INTERRUPT HANDLER
======================================================*/

void SysTick_Handler(void)
{
    msTicks++;

    /*
    Interrupt occurs every 1 ms [2]

    msTicks acts as:
    - system time base
    - delay reference counter
    */

    // turn_off_Buzzer();
    // Optional safety shutdown during interrupt
}

/*======================================================
  DELAY FUNCTION (ms)
======================================================*/

void delay_ms(uint32_t ms)
{
    uint32_t start = msTicks;

    /*
    Capture starting time
    */

    while((msTicks - start) < ms)
    {
        /*
        Busy-wait loop [3]

        Keeps CPU in loop until time expires
        */
    }
}
