/*
 * led_driver.c
 *
 *  Created on: Aug 15, 2025
 *      Author: benkempers
 */

#include "led_driver.h"


void run_gpio_led(bool button)
{
	/* enable clock access for gpio */
	RCC->AHB4ENR |= GPIOBEN;
	RCC->AHB4ENR |= GPIODEN;

	/* set PDN as output pin */
	//PB7
	GPIOB->MODER |= (1U<<14); //set bit 20 to 1
	GPIOB->MODER &=~ (1U<<15); //set bit 21 to 0

	//PD10
	GPIOD->MODER |= (1U<<20); //set bit 20 to 1
	GPIOD->MODER &=~ (1U<<21); //set bit 21 to 0

	//PD13
	GPIOD->MODER |= (1U<<26); //set bit 20 to 1
	GPIOD->MODER &=~ (1U<<27); //set bit 21 to 0

	/* enable button mode */
	if (button)
	{
		RCC->AHB4ENR |= GPIOCEN;

		/* set PC13 as input pin */
		GPIOC->MODER &=~ (1U<<26);
		GPIOC->MODER &=~ (1U<<27);
	}

	while(1)
	{
		/* toggle pin high/low */

		if(!button)
		{
			/* using ODR reg */
			GPIOB->ODR ^= LED3_PIN;
			for(int i =0; i<500000; i++) {}

			GPIOD->ODR ^= LED2_PIN;
			for(int i =0; i<500000; i++) {}

			GPIOD->ODR ^= LED1_PIN;
			for(int i =0; i<500000; i++) {}
		}
		else
		{
			/* using BSRR reg */
			if(GPIOC->IDR & BTN2_PIN) {
				GPIOB->BSRR = LED3_PIN;
				GPIOD->BSRR = LED2_PIN;
				GPIOD->BSRR = LED1_PIN;
			} else {
				GPIOB->BSRR = (1U<<23);
				for(int i =0; i<1000000; i++) {}
				GPIOD->BSRR = (1U<<29);
				for(int i =0; i<1000000; i++) {}
				GPIOD->BSRR = (1U<<26);
				for(int i =0; i<1000000; i++) {}
			}
		}
	}
}
