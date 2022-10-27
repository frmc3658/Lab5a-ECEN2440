/*
 * gpio.c
 *
 *  Created on: Oct 24, 2022
 *      Author:
 */


#include "gpio.h"

void config_gpio_timera2(void)
{
    // set P6.6 as input
    P6->DIR &= ~BIT6;

    // selecting primary function for TA2.3
    P6->SEL0 |= BIT6;
    P6->SEL1 &= ~BIT6;

    // input with pulldown resistor (TRM 12.2.4)
    P6->REN |= BIT6;
    P6->OUT |= BIT6;
}
