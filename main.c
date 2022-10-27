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
    ultrasonic_open();

    while(1)
    {

    }
}
