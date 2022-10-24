/**
 * main.c
 */

#include "msp.h"
#include "ultrasonic.h"
#include "pwm.h"
#include <stdio.h>

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    pwm_open();

    // TODO: gpio_open()

    while(1)
    {
        // TODO: call ultrasonic_calc_dist_cm()

        // TODO: print calculated distance
    }
}
