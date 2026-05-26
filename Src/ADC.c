

/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

ADC.c
STM32L476RG Analog-to-Digital Converter Driver

PA1 -> ADC Channel 6 (LDR)
PA2 -> ADC Channel 7 (Potentiometer)

Created on: May 20, 2026
Author: kenjutsu
========================================================
*/

/*======================================================
  HEADER FILE
======================================================*/

#include "ADC.h"

/*
ADC.h contains:
- ADC function prototypes
- STM32 definitions
- register configurations
*/

/*======================================================
  ADC PIN INITIALIZATION
======================================================*/

void ADC_Pin_Init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    // Enable clock for GPIO Port A [1]

    /*==================================================
      PA1 -> ADC CHANNEL 6 (LDR)
    ==================================================*/

    GPIOA->MODER |= (3UL << (2*1));

    /*
    Configure PA1 as ANALOG mode [1]

    MODER bits:
    00 = Input
    01 = Output
    10 = Alternate Function
    11 = Analog
    */

    GPIOA->ASCR |= GPIO_ASCR_ASC1;

    /*
    Connect analog switch for PA1 [1]

    Required for ADC analog operation
    */

    /*==================================================
      PA2 -> ADC CHANNEL 7 (POTENTIOMETER)
    ==================================================*/

    GPIOA->MODER |= (3UL << (2*2));

    // Configure PA2 as ANALOG mode

    GPIOA->ASCR |= GPIO_ASCR_ASC2;

    // Enable analog switch connection
}

/*======================================================
  ADC INITIALIZATION
======================================================*/

void ADC_Init(void)
{
    uint32_t timeout = 0;

    // Timeout variable prevents infinite loops [2]

    RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;

    // Enable ADC peripheral clock [1]

    ADC_Pin_Init();

    // Configure analog pins

    ADC123_COMMON->CCR |= ADC_CCR_CKMODE_0;

    /*
    Configure ADC clock mode [1]

    CKMODE_0:
    Select synchronous clock mode
    */

    ADC1->CR &= ~ADC_CR_DEEPPWD;

    /*
    Exit deep power-down mode [1]

    ADC cannot operate while in deep power-down.
    */

    ADC1->CR |= ADC_CR_ADVREGEN;

    /*
    Enable ADC voltage regulator [1]

    Required before calibration.
    */

    for(volatile int i = 0; i < 1000; i++);

    /*
    Small stabilization delay [3]

    Allows regulator voltage to stabilize.
    */

    ADC1->CR |= ADC_CR_ADCAL;

    /*
    Start ADC self-calibration [1]

    Improves conversion accuracy.
    */

    while((ADC1->CR & ADC_CR_ADCAL) && (timeout < 10000))
    {
        timeout++;

        // Wait until calibration complete
    }

    ADC1->CFGR &= ~ADC_CFGR_RES;

    /*
    Configure ADC resolution [1]

    Clearing RES bits selects:
    12-bit resolution
    */

    ADC1->SQR1 &= ~ADC_SQR1_L;

    /*
    Configure sequence length [1]

    L = 0 means:
    only one conversion in sequence.
    */

    /*==================================================
      SAMPLING TIME CONFIGURATION
    ==================================================*/

    ADC1->SMPR1 |= (7UL << ADC_SMPR1_SMP6_Pos);

    /*
    Channel 6 sampling time:
    247.5 ADC cycles [1]

    Longer sampling improves:
    - noise reduction
    - stable readings
    - potentiometer accuracy
    */

    ADC1->SMPR1 |= (7UL << ADC_SMPR1_SMP7_Pos);

    // Same long sampling time for Channel 7

    ADC1->CR |= ADC_CR_ADEN;

    // Enable ADC peripheral [1]

    timeout = 0;

    while((!(ADC1->ISR & ADC_ISR_ADRDY)) &&
          (timeout < 10000))
    {
        timeout++;

        // Wait until ADC becomes ready
    }
}

/*======================================================
  SINGLE ADC CHANNEL READ
======================================================*/

uint32_t ADC_Read_Channel(uint32_t channel)
{
    uint32_t timeout = 0;

    ADC1->SQR1 &= ~ADC_SQR1_SQ1;

    /*
    Clear previous channel selection [1]
    */

    ADC1->SQR1 |= (channel << 6);

    /*
    Select ADC channel [1]

    Example:
    channel = 6 -> LDR
    channel = 7 -> Potentiometer
    */

    ADC1->ISR |= ADC_ISR_EOC;

    /*
    Clear End Of Conversion flag [1]
    */

    ADC1->CR |= ADC_CR_ADSTART;

    /*
    Start ADC conversion [1]
    */

    while((!(ADC1->ISR & ADC_ISR_EOC)) &&
          (timeout < 10000))
    {
        timeout++;

        // Wait until conversion complete
    }

    return ADC1->DR;

    /*
    Return ADC digital result [1]

    12-bit ADC range:
    0 to 4095

    Equation [8]:

    Digital Value =
    (Vin / Vref) × (2^12 - 1)
    */
}

/*======================================================
  STABLE ADC READ WITH AVERAGING
======================================================*/

uint32_t ADC_Read_Channel_Stable(uint32_t channel)
{
    uint32_t sum = 0;

    /*
    sum stores total of all ADC samples
    */

    /*==================================================
      TAKE 16 SAMPLES
    ==================================================*/

    for(uint32_t i = 0; i < 16; i++)
    {
        sum += ADC_Read_Channel(channel);

        /*
        Read ADC repeatedly and accumulate values

        Multiple sampling reduces:
        - electrical noise
        - signal fluctuation
        - potentiometer instability
        */
    }

    return sum / 16;

    /*
    Average equation [10]:

    Average =
    (x1 + x2 + x3 + ... + xn) / n

    Averaging improves ADC stability [10]
    */
}
