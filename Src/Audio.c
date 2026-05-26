
/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

Audio.c
STM32L476RG PAM8302 Audio Driver

PA8 -> PAM8302 Audio Output

Created on: May 20, 2026
Author: kenjutsu
========================================================
*/

/*======================================================
  HEADER FILES
======================================================*/

#include "Audio.h"

/*
Audio.h contains:
- audio function prototypes
- STM32 register definitions
*/

#include "Systick_timer.h"

/*
Systick_timer.h contains:
- delay functions
- millisecond timing functions
*/

/*======================================================
  AUDIO OUTPUT INITIALIZATION
======================================================*/

void Audio_Init(void)
{
    /*==================================================
      ENABLE GPIOA CLOCK
    ==================================================*/

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    /*
    Enable clock access to GPIO Port A [1]

    Peripheral clock must be enabled before
    configuring GPIO registers.
    */

    /*==================================================
      CONFIGURE PA8 AS OUTPUT
    ==================================================*/

    GPIOA->MODER &= ~(3UL << (2*8));

    // Clear PA8 mode bits

    GPIOA->MODER |= (1UL << (2*8));

    /*
    Configure PA8 as OUTPUT mode [1]

    MODER:
    00 = Input
    01 = Output
    10 = Alternate Function
    11 = Analog
    */

    GPIOA->OTYPER &= ~(1UL << 8);

    /*
    Configure output as PUSH-PULL [1]

    Push-pull provides:
    - stronger drive capability
    - clean digital transitions
    */

    GPIOA->OSPEEDR |= (3UL << (2*8));

    /*
    Configure HIGH SPEED output [1]

    Faster transitions improve:
    - square wave quality
    - audio signal sharpness
    */

    GPIOA->ODR &= ~(1UL << 8);

    /*
    Start PA8 LOW

    Prevents accidental audio pulses
    during startup.
    */
}

/*======================================================
  PRIVATE MICROSECOND DELAY FUNCTION
======================================================*/

static void delay_us(uint32_t us)
{
    for(uint32_t i = 0; i < us * 8; i++)
    {
        __NOP();

        /*
        NOP = No Operation instruction [1]

        Consumes CPU clock cycles to create
        approximate microsecond timing delay.
        */
    }
}

/*======================================================
  PLAY SINGLE AUDIO TONE
======================================================*/

void Audio_Play_Tone(uint32_t frequency,
                     uint32_t duration_ms)
{
    if(frequency == 0 || duration_ms == 0)
        return;

    /*
    Prevent invalid audio generation.

    Avoid:
    - divide-by-zero error
    - zero-duration playback
    */

    uint32_t period_us = 1000000 / frequency;

    /*
    Frequency equation [8]

    T = 1 / f

    Converts frequency into waveform period.

    Example:
    1000 Hz -> 1000 us period
    */

    uint32_t half_period = period_us / 2;

    /*
    Square wave alternates:
    HIGH -> LOW

    every half period [8]
    */

    uint32_t cycles =
    (frequency * duration_ms) / 1000;

    /*
    Calculate total waveform cycles.

    Equation:

    cycles = frequency × time
    */

    for(uint32_t i = 0; i < cycles; i++)
    {
        /*==============================================
          OUTPUT HIGH
        ==============================================*/

        GPIOA->ODR |= (1UL << 8);

        /*
        Set PA8 HIGH

        Sends HIGH signal to PAM8302 input.
        */

        delay_us(half_period);

        /*==============================================
          OUTPUT LOW
        ==============================================*/

        GPIOA->ODR &= ~(1UL << 8);

        /*
        Set PA8 LOW

        Completes square-wave oscillation.
        */

        delay_us(half_period);
    }
}

/*======================================================
  PLAY AUDIO MELODY
======================================================*/

void Audio_Play_Melody(void)
{
    /*
    This function plays a simple ascending
    musical scale [9]
    */

    Audio_Play_Tone(262, 200);

    // C4 note

    delay_ms(50);

    // Small pause between notes

    Audio_Play_Tone(294, 200);

    // D4 note

    delay_ms(50);

    Audio_Play_Tone(330, 200);

    // E4 note

    delay_ms(50);

    Audio_Play_Tone(349, 200);

    // F4 note

    delay_ms(50);

    Audio_Play_Tone(392, 200);

    // G4 note

    delay_ms(50);

    Audio_Play_Tone(440, 200);

    // A4 note

    delay_ms(50);

    Audio_Play_Tone(494, 200);

    // B4 note

    delay_ms(50);

    Audio_Play_Tone(523, 400);

    // C5 note
}

/*======================================================
  START MUSIC FUNCTION
======================================================*/

void Start_Music(void)
{
    /*
    Calls melody playback routine
    */

    Audio_Play_Melody();
}

/*======================================================
  STOP MUSIC FUNCTION
======================================================*/

void Stop_Music(void)
{
    GPIOA->ODR &= ~(1UL << 8);

    /*
    Set PA8 LOW

    Stops audio signal output to PAM8302.
    */
}
