
/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

Button.c
STM32L476RG Push Button Driver

PC13 -> Push Button Input

Created on: May 20, 2026
Author: kenjutsu
========================================================
*/

/*======================================================
  HEADER FILE
======================================================*/

#include "BUTTON.h"

/*
BUTTON.h contains:
- button function prototypes
- STM32 register definitions
- GPIO configuration definitions
*/

/*======================================================
  BUTTON INITIALIZATION
======================================================*/

void Button_Init(void)
{
    /*==================================================
      ENABLE GPIOC CLOCK
    ==================================================*/

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    /*
    Enable clock access for GPIO Port C [1]

    GPIO registers cannot operate unless
    the peripheral clock is enabled.
    */

    /*==================================================
      CONFIGURE PC13 AS INPUT
    ==================================================*/

    GPIOC->MODER &= ~(3UL << (2 * 13));

    /*
    Configure PC13 as INPUT mode [1]

    MODER register:
    00 = Input
    01 = Output
    10 = Alternate Function
    11 = Analog

    Clearing both bits selects INPUT mode.
    */

    /*==================================================
      ENABLE INTERNAL PULL-UP RESISTOR
    ==================================================*/

    GPIOC->PUPDR &= ~(3UL << (2 * 13));

    // Clear previous pull resistor configuration

    GPIOC->PUPDR |= (1UL << (2 * 13));

    /*
    Configure internal pull-up resistor [5]

    Pull-up resistor keeps the pin normally HIGH.

    Without pull-up:
    - input may float
    - unstable readings may occur
    - false button detection possible
    */
}

/*======================================================
  BUTTON PRESS DETECTION
======================================================*/

uint8_t Button_Pressed(void)
{
    return !(GPIOC->IDR & (1UL << 13));

    /*
    GPIOC->IDR:
    Input Data Register [1]

    Reads the logic level present on PC13.

    Operation:
    - Button NOT pressed -> HIGH
    - Button pressed     -> LOW

    Because pull-up resistor is enabled,
    pressing the button connects pin to GND.

    ! operator converts:
    LOW  -> TRUE (1)
    HIGH -> FALSE (0)

    uint8_t:
    Unsigned 8-bit integer return type [7]
    */
}
