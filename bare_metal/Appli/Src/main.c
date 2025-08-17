#define STM32H7S3xx
#include "stm32h7rsxx.h"

#include <led_driver.h>
#include <uart_driver.h>
#include <adc.h>

#include <stdint.h>
#include <stdbool.h>

void adc_driver(void)
{
	led_init();
	usart_rxtx_init();

	pa4_adc_init();
	start_conversion();

	while(true)
	{
		uint32_t sensor_value = adc_read();
		printf("Sensor value : %d \n\r", (int)sensor_value);
		led_toggle(1);
	}
}

int main(void)
{

	//run_gpio_led(false);
	//uart_driver('Y');
	adc_driver();

	return 1;
}
