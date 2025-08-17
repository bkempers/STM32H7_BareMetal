/*
 * includes.h
 *
 *  Created on: Aug 15, 2025
 *      Author: benkempers
 */

#ifndef INCLUDES_H_
#define INCLUDES_H_

#define STM32H7S3xx
#include "stm32h7rsxx.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define GPIOAEN               (1U<<0)
#define GPIOBEN               (1U<<1)
#define GPIOCEN               (1U<<2)
#define GPIODEN               (1U<<3)

#define PIN5                  (1U<<5)
#define PIN7                  (1U<<7)
#define PIN10                 (1U<<10)
#define PIN13                 (1U<<13)

/* LED DEFINES */

#define LED1_PIN              (PIN10) //PD10
#define LED2_PIN              (PIN13) //PD13
#define LED3_PIN              (PIN7) //PB7

#define BTN2_PIN              (PIN13) //PC13

/* UART DEFINES */

#define SYS_FREQ 64000000
#define ABP1_CLK SYS_FREQ

#define UART_BAUDRATE 115200

#define CR1_FIFOEN_DISABLE    (0U<<29)
#define CR1_TE                (1U<<3)
#define CR1_RE                (1U<<2)
#define CR1_UE                (1U<<0)

#define ISR_ALT_RXNE           (1U<<5)
#define ISR_ALT_TXE            (1U<<7)

#define USART3EN               (1U<<18)

/* ADC DEFINES */

#define ADC12EN                 (1U<<5)
#define ADC_CH1                 (1U<<6)
#define ADC_SEQ_LEN_1           (0U<<0)
#define ADC_CR_ADEN             (1U<<0)

#define ADC_CR_ADSTART          (1U<<2)
#define ADC_CR_ADSTP            (1U<<4)

#define ADC_SR_EOC              (1U<<2)

#define ADC_CFGR_CONT           (1U<<13)


#endif /* INCLUDES_H_ */
