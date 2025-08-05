/*
 * uart_driver.h
 *
 *  Created on: Jul 24, 2025
 *      Author: benkempers
 */

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include <stdio.h>

#define GPIOAEN               (1U<<0)
#define GPIOBEN               (1U<<1)
#define GPIOCEN               (1U<<2)
#define GPIODEN               (1U<<3)

#define SYS_FREQ 16000000
#define ABP1_CLK SYS_FREQ

#define UART_BAUDRATE 115200

#define CR1_FIFOEN_DISABLE    (0U<<29)
#define CR1_TE                (1U<<3)
#define CR1_RE                (1U<<2)
#define CR1_UE                (1U<<0)

#define ISR_ALT_RXNE           (1U<<5)
#define ISR_ALT_TXE           (1U<<7)

/* LED DEBUG */

// LED definitions (from your earlier LED code)
#define LED1_PIN (1U<<10)  // PD10 - Green LED
#define LED2_PIN (1U<<13)  // PD13 - Yellow LED
#define LED3_PIN (1U<<7)   // PB7 - Red LED

void led_init(void)
{
    // Enable GPIO clocks
    RCC->AHB4ENR |= GPIOBEN | GPIODEN;

    // Configure LED pins as outputs
    // LED1 (PD10) and LED2 (PD13)
    GPIOD->MODER |= (1U<<20) | (1U<<26);  // Set bits for output mode
    GPIOD->MODER &= ~((1U<<21) | (1U<<27)); // Clear upper bits

    // LED3 (PB7)
    GPIOB->MODER |= (1U<<14);   // Set bit for output mode
    GPIOB->MODER &= ~(1U<<15);  // Clear upper bit
}

void led_toggle(int led_num)
{
    switch(led_num) {
        case 1: GPIOD->ODR ^= LED1_PIN; break;  // Green
        case 2: GPIOD->ODR ^= LED2_PIN; break;  // Yellow
        case 3: GPIOB->ODR ^= LED3_PIN; break;  // Red
    }
}

/* UART DRIVER */

#define USART3EN               (1U<<18)

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U)) / BaudRate);
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

void usart_rxtx_init(void)
{
	/* configure GPIO pin */
	// enable clock access
	RCC->AHB4ENR |= GPIODEN;

    // LED indication: Starting UART init
    led_toggle(1); // Green LED on

//	// set PD8 to alternate function
//	GPIOD->MODER &=~ (1U<<16); //set bit 16 to 0
//	GPIOD->MODER |= (1U<<17); //set bit 17 to 1
//	// set PD8 to alternate function type UART_TX AF7 (0111)
//	GPIOD->AFR[1] |= (1U<<0);
//	GPIOD->AFR[1] |= (1U<<1);
//	GPIOD->AFR[1] |= (1U<<2);
//	GPIOD->AFR[1] &=~ (1U<<3);

    /* TX Enable for USART3 GPIO */
    // set PD8 to alternate function
	GPIOD->MODER &=~ (1U<<16); //set bit 16 to 0
	GPIOD->MODER |= (1U<<17); //set bit 17 to 1

	// set PD8 to alternate function type UART_TX AF7 (0111)
	GPIOD->AFR[1] &= ~(0xF<<0);  // Clear bits first
	GPIOD->AFR[1] |= (7U<<0);    // Set AF7

	/* RX Enable for USART3 GPIO */
    // set PD9 to alternate function
	GPIOD->MODER &=~ (1U<<18); //set bit 18 to 0
	GPIOD->MODER |= (1U<<19); //set bit 19 to 1

	// set PD9 to alternate function type UART_RX AF7 (0111)
	GPIOD->AFR[1] &= ~(0xF<<4);  // Clear bits first
	GPIOD->AFR[1] |= (7U<<4);    // Set AF7

	/* configure UART module */
	// enable clock access to UART3
	RCC->APB1ENR1 |= USART3EN;

	// LED indication: UART clocks enabled
	led_toggle(2); // Yellow LED on

	// configure baudrate
	uart_set_baudrate(USART3, ABP1_CLK, UART_BAUDRATE);

	// configure transfer direction
	USART3->CR1 = CR1_FIFOEN_DISABLE | CR1_TE | CR1_RE;
	// enable uart module
	USART3->CR1 |= CR1_UE;

	// LED indication: UART fully configured
	led_toggle(3); // Red LED on
}

char uart3_read(void)
{
	// make sure rx data reg is not empty
	while(!(USART3->ISR & ISR_ALT_RXNE)) {}

	// read data
	return USART3->RDR;
}

void uart3_write(int ch)
{
	// LED indication: Attempting to send character
	led_toggle(1); // Toggle green LED for each character

	// make sure tx data reg is empty
	while(!(USART3->ISR & ISR_ALT_TXE)) {}
	// write to transmit data reg
	USART3->TDR = (ch & 0xFF);

	// LED indication: Character sent
	led_toggle(2); // Toggle yellow LED after sending

	// Delay between characters
	for(volatile int i = 0; i < 10000; i++) {}
}

int __io_putchar(int ch)
{
	uart3_write(ch);
	return ch;
}

void uart_driver(int ch)
{
    led_init();
    usart_rxtx_init();

    while(1)
    {
    	printf("Hello STM32H7....\n\r");
        led_toggle(3);
    }
}


#endif /* UART_DRIVER_H_ */
