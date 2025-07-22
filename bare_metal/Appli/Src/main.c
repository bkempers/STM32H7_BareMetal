#define STM32H7S3xx
#include "stm32h7rsxx.h"

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

#define LED1_PIN              (PIN10) //PD10
#define LED2_PIN              (PIN13) //PD13
#define LED3_PIN              (PIN7) //PB7

#define BTN2_PIN              (PIN13) //PC13

int main(void)
{

	run_gpio_led(true);
	return 1;
}

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
