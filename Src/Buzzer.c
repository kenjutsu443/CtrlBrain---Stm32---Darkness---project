
/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

Buzzer.c
STM32L476RG Passive Buzzer Driver

PA7 -> Passive Buzzer Output
========================================================
*/

#include "Buzzer.h"

/*======================================================
  PRIVATE MICROSECOND DELAY FUNCTION
======================================================*/
static void delay_us(uint32_t us)
{
    for(uint32_t i = 0; i < us * 8; i++)
    {
        __NOP();

        /*
        __NOP(): No Operation instruction [1]

        Used to consume CPU cycles for timing delay.

        This creates approximate microsecond timing.
        */
    }
}

/*======================================================
  BUZZER INITIALIZATION
======================================================*/
void Buzzer_Init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    // Enable GPIOA clock [1]

    GPIOA->MODER &= ~(3UL << (2 * 7));
    // Clear PA7 mode bits

    GPIOA->MODER |= (1UL << (2 * 7));
    // Set PA7 as OUTPUT mode [1]

    GPIOA->OTYPER &= ~(1UL << 7);
    // Configure push-pull output [1]

    GPIOA->OSPEEDR |= (3UL << (2 * 7));
    // High-speed output for clean signal [1]

    GPIOA->ODR &= ~(1UL << 7);
    // Initialize buzzer OFF (LOW)
}

/*======================================================
  BUZZER CONTROL FUNCTIONS
======================================================*/
void Buzzer_On(void)
{
    GPIOA->ODR |= (1UL << 7);
    // Set PA7 HIGH -> buzzer ON
}

void Buzzer_Off(void)
{
    GPIOA->ODR &= ~(1UL << 7);
    // Set PA7 LOW -> buzzer OFF
}

/*======================================================
  BUZZER TONE GENERATION
======================================================*/
void Buzzer_Play_Tone(uint32_t frequency,
                      uint32_t duration_ms)
{
    if(frequency == 0 || duration_ms == 0)
        return;

    /*
    Prevent invalid inputs:
    - frequency = 0 → divide-by-zero error
    - duration = 0 → no output
    */

    uint32_t period_us = 1000000 / frequency;

    /*
    Frequency equation [8]:

    T = 1 / f
    Convert frequency to period in microseconds
    */

    uint32_t half_period = period_us / 2;

    /*
    Square wave generation:

    HIGH time = LOW time = half period [8]
    */

    uint32_t cycles =
    (frequency * duration_ms) / 1000;

    /*
    Total oscillation cycles
    */

    for(uint32_t i = 0; i < cycles; i++)
    {
        /*===============================
          SIGNAL HIGH
        ===============================*/
        Buzzer_On();

        delay_us(half_period);

        /*===============================
          SIGNAL LOW
        ===============================*/
        Buzzer_Off();

        delay_us(half_period);
    }
}
