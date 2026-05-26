
/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

USART.c
STM32L476RG USART2 Driver (Serial Communication)

Purpose:
Provides UART communication for debugging and data
transmission via PA2 (TX) and PA3 (RX).
========================================================
*/

#include "USART.h"
#include "stm32l476xx.h"

/*======================================================
  USART2 INITIALIZATION
======================================================*/

void USART2_Init(void)
{
    /*==================================================
      ENABLE CLOCKS
    ==================================================*/

    RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
    // Enable USART2 peripheral clock [1]

    RCC->AHB2ENR  |= RCC_AHB2ENR_GPIOAEN;
    // Enable GPIOA clock [1]

    /*==================================================
      CONFIGURE GPIO PINS (PA2, PA3)
    ==================================================*/

    GPIOA->MODER &= ~(3UL << (2*2));
    // Clear PA2 mode bits

    GPIOA->MODER |= (2UL << (2*2));
    // Set PA2 to Alternate Function mode [1]

    GPIOA->MODER &= ~(3UL << (2*3));
    // Clear PA3 mode bits

    GPIOA->MODER |= (2UL << (2*3));
    // Set PA3 to Alternate Function mode [1]

    /*==================================================
      SELECT ALTERNATE FUNCTION AF7 (USART2)
    ==================================================*/

    GPIOA->AFR[0] &= ~(0xF << (4*2));
    // Clear PA2 AF selection

    GPIOA->AFR[0] |= (7 << (4*2));
    // Set PA2 = AF7 (USART2 TX) [1]

    GPIOA->AFR[0] &= ~(0xF << (4*3));
    // Clear PA3 AF selection

    GPIOA->AFR[0] |= (7 << (4*3));
    // Set PA3 = AF7 (USART2 RX) [1]

    /*==================================================
      BAUD RATE CONFIGURATION
    ==================================================*/

    USART2->BRR = 4000000 / 115200;

    /*
    Baud rate calculation [4]:

    BRR = System Clock / Baud Rate

    Sets communication speed to 115200 bps
    */

    /*==================================================
      ENABLE USART FUNCTIONALITY
    ==================================================*/

    USART2->CR1 |= USART_CR1_TE;
    // Enable transmitter [1]

    USART2->CR1 |= USART_CR1_RE;
    // Enable receiver [1]

    USART2->CR1 |= USART_CR1_UE;
    // Enable USART module [1]
}

/*======================================================
  USART WRITE FUNCTION
======================================================*/

void USART2_Write(char ch)
{
    while(!(USART2->ISR & USART_ISR_TXE));

    /*
    Wait until transmit data register is empty [1]

    TXE = 1 means ready to send next byte
    */

    USART2->TDR = ch;

    /*
    Load character into transmit register
    */
}

/*======================================================
  RETARGET _write FUNCTION (PRINTF SUPPORT)
======================================================*/

int _write(int file, char *ptr, int len)
{
    for(int i = 0; i < len; i++)
    {
        USART2_Write(ptr[i]);

        /*
        Sends each character via USART2
        Enables printf() output in STM32 [3]
        */
    }

    return len;
}
