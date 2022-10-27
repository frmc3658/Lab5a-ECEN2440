/*
 * gpio.c
 *
 *  Authors: Brendan N, Frank M, Shane M
 */

//***************************************************************
// included header file
//**************************************************************/
#include "gpio.h"


//***************************************************************
// static variables
//**************************************************************/


//***************************************************************
// function definitions
//**************************************************************/
// configure GPIO port 2.5 for primary TIMER_A0 (TA0.1) functionality
// for use with the HC-SR04 Ultrasonic Ranging Module
void config_gpio_trigger_timer(void)
{
    // set P2.5 as output (TRM 12.2.3) to send trigger signal
    P2->DIR |= BIT5;

    // select primary module function of P2.5 (TRM 12.2.6)
    P2->SEL0 |= BIT5;
    P2->SEL1 &= ~BIT5;

    // set OUT register to low (TRM 12.2.2)
    P2->OUT &= ~(BIT5);
}


// configure GPIO port 6.6 for primary TIMER_A2 (TA2.3) functionality
// for use with the HC-SR04 Ultrasonic Ranging Module
void config_gpio_echo_timer(void)
{
    // set P6.6 as input to reach echo pulses
    P6->DIR &= ~BIT6;

    // selecting primary functionality: TA2.3
    P6->SEL0 |= BIT6;
    P6->SEL1 &= ~BIT6;

    // input with pullup resistor (TRM 12.2.4)
    P6->REN |= BIT6;
    P6->OUT |= BIT6;
}

