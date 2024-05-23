/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   100

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)

#define SW0_NODE	DT_ALIAS(sw4) 
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);


/* this struct contains the device information like pointer to device, pin number, etc */
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);


int main(void)
{
	int ret;

	/* checking if the gpio pin is ready to use */
	if (!gpio_is_ready_dt(&led0)) {
		return 0;
	}

	if (!gpio_is_ready_dt(&led1)) {
		return 0;
	}

	if (!gpio_is_ready_dt(&led2)) {
		return 0;
	}

	

	/* configuring the gpio pin */
	ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

	/* configuring button */
	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);

	while (1) {

		bool val = gpio_pin_get_dt(&button);

		// while(val == 1) {
		// 	gpio_pin_set_dt(&led0, 1);
		// 	gpio_pin_set_dt(&led0, 0);
		// 	k_msleep(SLEEP_TIME_MS);

		// 	gpio_pin_set_dt(&led1, 1);
		// 	gpio_pin_set_dt(&led1, 0);
		// 	k_msleep(SLEEP_TIME_MS);

		// 	gpio_pin_set_dt(&led2, 1);
		// 	gpio_pin_set_dt(&led2, 0);
		// 	k_msleep(SLEEP_TIME_MS);
		// }

		if(val == 1) {
			gpio_pin_set_dt(&led0, 1);
			k_msleep(SLEEP_TIME_MS);
			gpio_pin_set_dt(&led0, 0);
			k_msleep(SLEEP_TIME_MS);

			gpio_pin_set_dt(&led1, 1);
			k_msleep(SLEEP_TIME_MS);
			gpio_pin_set_dt(&led1, 0);
			k_msleep(SLEEP_TIME_MS);

			gpio_pin_set_dt(&led2, 1);
			k_msleep(SLEEP_TIME_MS);
			gpio_pin_set_dt(&led2, 0);
			k_msleep(SLEEP_TIME_MS);

		} else {
			gpio_pin_set_dt(&led0, 0);
			gpio_pin_set_dt(&led1, 0);
			gpio_pin_set_dt(&led2, 0);
		}

		// gpio_pin_set_dt(&led0, val);
		k_msleep(SLEEP_TIME_MS);



		
		

	}
	return 0;
}
