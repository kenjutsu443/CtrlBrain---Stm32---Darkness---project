
/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

MAIN.C
STM32L476RG Smart Darkness Detection Audio System

PA6  -> LED
PA7  -> Passive buzzer
PA8  -> PAM8302 preamp
PC13 -> Push button
ADC6 -> LDR
ADC7 -> Potentiometer
========================================================
*/

/*======================================================
  HEADER FILES
======================================================*/

#include "stm32l476xx.h"
// STM32L476RG register definitions [1]

#include "ADC.h"
// ADC initialization and analog read functions [2]

#include "LED.h"
// LED control functions [2]

#include "Buzzer.h"
// Passive buzzer initialization functions [2]

#include "Audio.h"
// PAM8302 audio output functions [2]

#include "Systick_timer.h"
// Delay and timing functions using SysTick timer [3]

/*======================================================
  GLOBAL VARIABLE
======================================================*/

volatile uint8_t music_enable = 1;

// volatile:
// Prevents compiler optimization because variable
// may change during execution [4]
//
// uint8_t:
// Unsigned 8-bit integer
//
// music_enable = 1:
// Music initially ON

/*======================================================
  BUTTON PC13 INITIALIZATION
======================================================*/

void Button_PC13_Init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    // Enable clock for GPIO Port C [1]

    GPIOC->MODER &= ~(3UL << (13 * 2));

    // Configure PC13 as INPUT mode [1]

    GPIOC->PUPDR &= ~(3UL << (13 * 2));

    // Clear pull-up/pull-down bits

    GPIOC->PUPDR |= (1UL << (13 * 2));

    // Enable internal pull-up resistor [5]
}

/*======================================================
  BUTTON PRESS DETECTION
======================================================*/

int Button_PC13_Pressed(void)
{
    return !(GPIOC->IDR & (1 << 13));

    /*
    GPIOC->IDR:
    Input Data Register

    Reads logic level from PC13 pin.

    Pull-up resistor keeps pin HIGH normally.

    When button is pressed:
    pin becomes LOW.

    ! operator converts:
    LOW  -> TRUE
    HIGH -> FALSE
    */
}

/*======================================================
  MICROSECOND DELAY FUNCTION
======================================================*/

static void delay_us(uint32_t us)
{
    for(uint32_t i = 0; i < us * 8; i++)
    {
        __NOP();

        // NOP = No Operation instruction
        // Consumes CPU cycle for timing delay [1]
    }
}

/*======================================================
  BUTTON CHECK + DEBOUNCING
======================================================*/

void Check_Button(void)
{
    if(Button_PC13_Pressed())
    {
        delay_ms(30);

        // Software debounce delay [6]

        if(Button_PC13_Pressed())
        {
            music_enable ^= 1;

            /*
            XOR toggle operation [7]

            1 XOR 1 = 0
            0 XOR 1 = 1

            Toggles music ON/OFF
            */

            while(Button_PC13_Pressed());

            // Wait until button released

            delay_ms(30);

            // Additional debounce delay
        }
    }
}

/*======================================================
  PLAY SINGLE AUDIO NOTE
======================================================*/

void Play_Note(uint32_t frequency, uint32_t duration_ms)
{
    if(frequency == 0 || duration_ms == 0)
        return;

    // Prevent divide-by-zero error

    uint32_t period_us = 1000000 / frequency;

    /*
    Period equation [8]

    T = 1 / f

    Converts frequency to period in microseconds
    */

    uint32_t half_period = period_us / 2;

    // Square wave changes state every half period

    uint32_t cycles = (frequency * duration_ms) / 1000;

    // Total number of oscillation cycles

    for(uint32_t i = 0; i < cycles; i++)
    {
        Check_Button();

        // Allow button response during playback

        if(!music_enable)
        {
            GPIOA->ODR &= ~(1UL << 7);
            GPIOA->ODR &= ~(1UL << 8);

            // Turn OFF buzzer and PAM8302

            return;
        }

        /*====================================
          OUTPUT HIGH
        ====================================*/

        GPIOA->ODR |= (1UL << 7);

        // PA7 HIGH -> passive buzzer signal

        GPIOA->ODR |= (1UL << 8);

        // PA8 HIGH -> PAM8302 signal

        delay_us(half_period);

        /*====================================
          OUTPUT LOW
        ====================================*/

        GPIOA->ODR &= ~(1UL << 7);

        // PA7 LOW

        GPIOA->ODR &= ~(1UL << 8);

        // PA8 LOW

        delay_us(half_period);
    }
}

/*======================================================
  PLAY HISTORIC MARCH
======================================================*/

void Play_March(void)
{
    if(!music_enable)
        return;

    // Exit if music disabled

    Play_Note(392, 250);

    // G4 note [9]

    Play_Note(392, 250);

    // G4 note

    Play_Note(392, 250);

    // G4 note

    Play_Note(311, 180);

    // D#4 note

    Play_Note(466, 80);

    // A#4 note

    Play_Note(392, 250);

    // G4 note

    Play_Note(311, 180);

    // D#4 note

    Play_Note(466, 80);

    // A#4 note

    Play_Note(392, 500);

    // Long G4 note

    delay_ms(100);

    // Small pause between repetitions
}

/*======================================================
  MAIN FUNCTION
======================================================*/

int main(void)
{
    uint32_t ldr_value;

    // Stores LDR ADC reading

    uint32_t pot_value;

    // Stores potentiometer ADC reading

    SysTick_Init();

    // Initialize system timer [3]

    ADC_Init();

    // Initialize ADC peripheral [2]

    LED_Init();

    // Configure LED pin [2]

    Buzzer_Init();

    // Configure buzzer output pin [2]

    Audio_Init();

    // Configure PAM8302 output pin [2]

    Button_PC13_Init();

    // Configure push button input

    turn_off_LED();

    // Start with LED OFF

    while(1)
    {
        ldr_value = ADC_Read_Channel_Stable(6);

        // Read LDR on ADC channel 6

        pot_value = ADC_Read_Channel_Stable(7);

        // Read potentiometer on ADC channel 7

        Check_Button();

        // Check ON/OFF button state

        /*====================================
          DARKNESS DETECTION
        ====================================*/

        if(ldr_value < pot_value)
        {
            /*
            Darkness condition:

            LDR voltage lower than threshold
            set by potentiometer.
            */

            turn_on_LED();

            // Turn ON indicator LED

            if(music_enable)
            {
                Play_March();

                // Play audio melody
            }
        }
        else
        {
            /*================================
              BRIGHT ENVIRONMENT
            ================================*/

            turn_off_LED();

            // Turn OFF LED

            GPIOA->ODR &= ~(1UL << 7);

            // Turn OFF buzzer signal

            GPIOA->ODR &= ~(1UL << 8);

            // Turn OFF PAM8302 signal
        }

        delay_ms(10);

        // Small system stabilization delay
    }
}

