/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

LED.c
STM32L476RG LED Driver

PA6 -> LED Output
========================================================
*/

#include "LED.h"
#include "stm32l476xx.h"

/*======================================================
  LED INITIALIZATION
======================================================*/
void LED_Init()
{
    /*==================================================
      ENABLE GPIOA CLOCK
    ==================================================*/

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    /*
    Enable clock for GPIO Port A [1]

    Required before accessing GPIO registers.
    */

    /*==================================================
      CONFIGURE PA6 AS OUTPUT
    ==================================================*/

    GPIOA->MODER &= ~(3UL << (2*6));

    /*
    Clear PA6 mode bits [1]

    This resets pin configuration before setting mode.
    */

    GPIOA->MODER |= (1UL << (2*6));

    /*
    Set PA6 as OUTPUT mode [1]

    MODER:
    00 = Input
    01 = Output
    10 = Alternate Function
    11 = Analog
    */

    /*==================================================
      CONFIGURE OUTPUT TYPE
    ==================================================*/

    GPIOA->OTYPER &= ~(1UL << 6);

    /*
    Push-pull configuration [1]

    - 0 = Push-pull
    - 1 = Open-drain
    */

    /*==================================================
      CONFIGURE PULL-UP / PULL-DOWN
    ==================================================*/

    GPIOA->PUPDR &= ~(3UL << (2*6));

    /*
    No pull-up, no pull-down [1]

    Ensures stable digital output behavior.
    */
}

/*======================================================
  LED CONTROL FUNCTIONS
======================================================*/

/* Toggle LED state */
void toggle_LED()
{
    GPIOA->ODR ^= (1UL << 6);

    /*
    XOR operation toggles the LED state:

    0 -> 1 (ON)
    1 -> 0 (OFF)

    Efficient bitwise control [7]
    */
}

/* Turn LED OFF */
void turn_off_LED()
{
    GPIOA->ODR &= ~(1UL << 6);

    /*
    Clears bit 6 -> LED OFF
    */
}

/* Turn LED ON */
void turn_on_LED()
{
    GPIOA->ODR |= (1UL << 6);

    /*
    Sets bit 6 -> LED ON
    */
}
