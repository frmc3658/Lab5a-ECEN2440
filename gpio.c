/*
 * gpio.c
 *
 *  Created on: Oct 24, 2022
 *      Author:
 */


#include "gpio.h"

void config_gpio_timera2(void)
{
    // input with pulldown resistor (TRM 12.2.4)
    P6->REN |= BIT6;
    P6->OUT &= ~BIT6;
}
