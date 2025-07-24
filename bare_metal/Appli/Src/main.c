#define STM32H7S3xx
#include "stm32h7rsxx.h"

#include <led_driver.h>
#include <uart_driver.h>

#include <stdint.h>
#include <stdbool.h>

int main(void)
{

	//run_gpio_led(true);
	uart_driver('Y');
	return 1;
}
