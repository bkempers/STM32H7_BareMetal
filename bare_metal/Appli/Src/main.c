#define STM32H7S3xx
#include "stm32h7rsxx.h"

#include <led_driver.h>
#include <uart_driver.h>
#include <adc.h>
#include <systick.h>

#include <stdint.h>
#include <stdbool.h>

int main(void)
{

	//run_gpio_led(false);
	//uart_driver('Y');
	//adc_driver();
	systick_driver(1000);

	return 1;
}
