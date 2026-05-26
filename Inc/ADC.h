/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

ADC.h
STM32L476RG ADC Driver Header File

Purpose:
Defines function prototypes for ADC initialization and
analog signal reading (LDR + potentiometer system).
========================================================
*/

#ifndef __STM32L476G_ADC_H
#define __STM32L476G_ADC_H

#include "stm32l476xx.h"

/*======================================================
  ADC INITIALIZATION FUNCTION
======================================================*/

void ADC_Init(void);

/*
ADC_Init():
Initializes ADC peripheral including:
- clock enable
- calibration
- sampling configuration
- ADC enable state

Reference [1]
*/

/*======================================================
  ADC SINGLE CHANNEL READ FUNCTION
======================================================*/

uint32_t ADC_Read_Channel(uint32_t channel);

/*
Reads raw ADC value from selected channel.

Parameters:
- channel: ADC input channel number (e.g., 6 or 7)

Returns:
- 12-bit ADC value (0–4095)

Used for:
- LDR sensor reading
- potentiometer input

Reference [1]
*/

/*======================================================
  ADC STABLE READ FUNCTION (AVERAGING FILTER)
======================================================*/

uint32_t ADC_Read_Channel_Stable(uint32_t channel);

/*
Performs multiple ADC samples and returns average value.

Purpose:
- reduce noise
- stabilize sensor readings
- improve reliability of analog inputs

Algorithm:
- take multiple samples
- compute arithmetic mean [10]
*/

/*======================================================
  OPTIONAL / LEGACY FUNCTIONS (COMMENTED)
======================================================*/

/*
The following functions were part of earlier design
iterations but are currently disabled:

- adc_result global variable
- ADC wake-up from deep power-down
- ADC pin initialization split functions
- ADC common configuration function
- direct ADC read interrupt-based version

These were replaced by modular ADC_Init() design.
*/

/*
extern volatile uint32_t adc_result;

void ADC1_Wakeup(void);
void ADC_Pin_Init(void);
void ADC_Common_Configuration(void);
void ADC_Read(void);
*/

#endif
