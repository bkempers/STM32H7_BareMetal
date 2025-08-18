/*
 * systick.c
 *
 *  Created on: Aug 18, 2025
 *      Author: benkempers
 */

#include "systick.h"

void systickDelayMS(int delay)
{
	/* configure systick for # of clks / ms */
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/* clear systick current value reg */
	SysTick->VAL = 0;

	/* enable and select clk source */
	SysTick->CTRL = SYSTICK_CR_EN | SYSTICK_CR_CLK_SRC;

	for(int i = 0; i < delay; i++)
	{
		while((SysTick->CTRL & SYSTICK_CR_COUNTFLAG) == 0) {}
	}

	/* clear systick current value reg */
	SysTick->CTRL = 0;
}

void systick_driver(int delay)
{
	led_init();
	usart_rxtx_init();

	while(true)
	{
		printf("1 second\n\r");
		led_toggle(1);
		systickDelayMS(delay);
	}
}
