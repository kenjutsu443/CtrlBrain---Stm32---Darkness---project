
/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

USART.h
STM32L476RG USART2 Driver Header File

Purpose:
Defines function prototypes for UART communication
using USART2 (PA2 TX, PA3 RX).
========================================================
*/

#ifndef USART_H_
#define USART_H_

#include "stm32l476xx.h"

/*======================================================
  USART INITIALIZATION
======================================================*/

void USART2_Init(void);

/*
Initializes USART2 peripheral for serial communication.

Configuration includes:
- GPIO alternate function setup
- baud rate configuration
- transmitter/receiver enable

Reference [1]
*/

/*======================================================
  DATA TRANSMISSION FUNCTION
======================================================*/

void USART2_Write(char ch);

/*
Transmits a single character via USART2.

Waits until TXE flag is set before sending data [1]
*/

/*======================================================
  STDIO RETARGET FUNCTION
======================================================*/

int _write(int file, char *ptr, int len);

/*
Redirects printf() output to USART2.

Used for:
- debugging via serial monitor
- logging system output

Reference [3]
*/

#endif
