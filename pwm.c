/*
 * pwm.c
 *
 * Authors: Brendan N, Frank M, Shane M
 */

//***************************************************************
// include header file
//**************************************************************/
#include "pwm.h"


//***************************************************************
// static variables
//**************************************************************/


//***************************************************************
// function definitions
//**************************************************************/
// open PWM peripheral
void pwm_open(void)
{
    //disables interrupts
    __disable_interrupt();

    // stop timer_a before modifying operation; per: TRM 19.2.1
    stop_pwm();

    // configure TA0 for PWM operation to function as a trigger signal
    config_trigger_timer();

    // configure P2.5 for TA0 trigger operation
    config_gpio_trigger_timer();

    // Set CCR1 to value for 10 micro-seconds
    TIMER_A0->CCR[2] = CCR1_10_MICRO_SEC;


    // start PWM timer
    start_pwm();

    // enable timer interrupts in NVIC
    __NVIC_EnableIRQ(TA0_N_IRQn);

    //enable interrupts
    __enable_interrupt();
}


// stop PWM peripheral
void stop_pwm(void)
{
    // set MC to halt/stop mode
    TIMER_A0->CTL = TIMER_A_CTL_MC__STOP;
}


// start PWM peripheral
void start_pwm(void)
{
    // set TA0 to up mode
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP;
}


// configure TA0 to function as a trigger for
// the HC-SR04 Ultrasonic Ranging Module
void config_trigger_timer(void)
{
    // clear R register
    TIMER_A0->CTL |= TIMER_A_CTL_CLR;

    // select SMCLK as source
    TIMER_A0->CTL |= TIMER_A_CTL_SSEL__SMCLK;

    // set input divider; 2^1
    TIMER_A0->CTL |= TIMER_A_CTL_ID__1;

    // intermediary state; see note at bottom of page (TRM 19.2.5.1.3)
    TIMER_A0-> CCTL[2] |= TIMER_A_CCTLN_OUTMOD_7;

    // Set/Reset mode
    TIMER_A0-> CCTL[2] &= TIMER_A_CCTLN_OUTMOD_3;

    // set capture/compare register 0 value
    TIMER_A0-> CCR[0] = TICKS;

    // capture compare interrupt enable
    TIMER_A0->CCTL[2] |= TIMER_A_CCTLN_CCIE;
}


// TIMER_A0 IRQ Handler stops the timer to prevent signal overlap
void TA0_N_IRQHandler(void)
{
    // stop PWM
    stop_pwm();

    // disable interrupts
    __NVIC_DisableIRQ(TA0_N_IRQn);

    // lower capture/compare flag
    TIMER_A0->CCTL[2] &= ~TIMER_A_CCTLN_CCIFG;
}

