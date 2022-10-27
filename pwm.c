/*
 * pwm.c
 *
 */

//***************************************************************
// include header file
//**************************************************************/
#include "pwm.h"


//***************************************************************
// function definitions
//**************************************************************/
void pwm_open(void)
{
    //disables interrupt
    __disable_interrupt();

    // stop timer_a before modifying operation; per: TRM 19.2.1
    stop_pwm();

    // configure timer_a for PWM operation
    config_pwm_timer();

    // configure P2.5 for TA0
    config_gpio_timera0();

    // enable NVIC
    config_nvic();

    // Set CCR1 to value for 10ms
    TIMER_A0->CCR[2] = CCR1_DUTY_10mics;

    // start PWM timer
    start_pwm();

    //enable interrupt
    __enable_interrupt();
}


void start_pwm(void)
{
    // set TA0 to up mode
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP;
}


void stop_pwm(void)
{
    // set MC to halt/stop mode
    TIMER_A0->CTL = TIMER_A_CTL_MC__STOP;
}


void config_pwm_timer(void)
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

void config_nvic(void)
{
    // enable interrupts
    __NVIC_EnableIRQ(TA0_N_IRQn);
}

void TA0_N_IRQHandler(void)
{
    // stop PWM
    stop_pwm();

    // disable interrupts
    __NVIC_DisableIRQ(TA0_N_IRQn);

    // lower capture/compare flag
    TIMER_A0->CCTL[2] &= ~TIMER_A_CCTLN_CCIFG;
}


void config_gpio_timera0(void)
{
    // set P2.5 as output (TRM 12.2.3)
    P2->DIR |= BIT5;

    // select primary module function of P2.5 (TRM 12.2.6)
    P2->SEL0 |= BIT5;
    P2->SEL1 &= ~BIT5;

    // set OUT register to low (TRM 12.2.2)
    P2->OUT &= ~(BIT5);
}

