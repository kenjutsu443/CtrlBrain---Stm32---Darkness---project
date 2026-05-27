/*
 * main.c
 *
 *  Created on: May 26, 2026
 *      Author: kenjutsu
 */

/*======================================================
  HEADER FILES
======================================================*/

#include "stm32l476xx.h"
#include "ADC.h"
#include "LED.h"
#include "Buzzer.h"
#include "Audio.h"
#include "Systick_timer.h"

/*======================================================
  GLOBAL VARIABLE
======================================================*/

volatile uint8_t music_enable = 1;

/*======================================================
  BUTTON PC13 INITIALIZATION
======================================================*/

void Button_PC13_Init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    GPIOC->MODER &= ~(3UL << (13 * 2));
    GPIOC->PUPDR &= ~(3UL << (13 * 2));
    GPIOC->PUPDR |= (1UL << (13 * 2));  // Enable pull-up
}

/*======================================================
  BUTTON PRESS DETECTION
======================================================*/

int Button_PC13_Pressed(void)
{
    return !(GPIOC->IDR & (1 << 13));
}

/*======================================================
  MICROSECOND DELAY FUNCTION
======================================================*/

static void delay_us(uint32_t us)
{
    for(uint32_t i = 0; i < us * 8; i++)
    {
        __NOP();
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
        if(Button_PC13_Pressed())
        {
            music_enable ^= 1;  // Toggle music ON/OFF
            while(Button_PC13_Pressed());  // Wait for release
            delay_ms(30);
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

    uint32_t period_us = 1000000 / frequency;
    uint32_t half_period = period_us / 2;
    uint32_t cycles = (frequency * duration_ms) / 1000;

    for(uint32_t i = 0; i < cycles; i++)
    {
        Check_Button();

        if(!music_enable)
        {
            GPIOA->ODR &= ~(1UL << 7);  // Buzzer OFF
            GPIOA->ODR &= ~(1UL << 8);  // Audio OFF
            return;
        }

        GPIOA->ODR |= (1UL << 7);   // Buzzer HIGH
        GPIOA->ODR |= (1UL << 8);   // Audio HIGH
        delay_us(half_period);

        GPIOA->ODR &= ~(1UL << 7);  // Buzzer LOW
        GPIOA->ODR &= ~(1UL << 8);  // Audio LOW
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

    Play_Note(392, 250);  // G4
    Play_Note(392, 250);  // G4
    Play_Note(392, 250);  // G4
    Play_Note(311, 180);  // D#4
    Play_Note(466, 80);   // A#4
    Play_Note(392, 250);  // G4
    Play_Note(311, 180);  // D#4
    Play_Note(466, 80);   // A#4
    Play_Note(392, 500);  // Long G4
    delay_ms(100);
}

/*======================================================
  MAIN FUNCTION - UPDATED FOR PA4 POTENTIOMETER
======================================================*/

int main(void)
{
    uint32_t ldr_value;
    uint32_t pot_value;

    SysTick_Init();
    ADC_Init();
    LED_Init();
    Buzzer_Init();
    Audio_Init();
    Button_PC13_Init();
    turn_off_LED();

    while(1)
    {
        ldr_value = ADC_Read_Channel_Stable(6);  // PA1 - LDR (Channel 6)

        /*==================================================
          CHANGED: Potentiometer now on PA4 (Channel 9)
          Previously was PA2 (Channel 7)
        ==================================================*/
        pot_value = ADC_Read_Channel_Stable(9);  // PA4 - Potentiometer (Channel 9)

        Check_Button();

        if(ldr_value < pot_value)  // Darkness detected
        {
            turn_on_LED();
            if(music_enable)
            {
                Play_March();
            }
        }
        else  // Bright environment
        {
            turn_off_LED();
            GPIOA->ODR &= ~(1UL << 7);  // Buzzer OFF
            GPIOA->ODR &= ~(1UL << 8);  // Audio OFF
        }

        delay_ms(10);  // System stabilization delay
    }
}
