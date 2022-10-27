/*
 * ultrasoni.c
 *
 *  Created on: Oct 17, 2022
 *      Author:
 */

#include "ultrasonic.h"


//static void add_scheduled_event(timer_a2_callback);
static volatile uint32_t capture_values[CAP_VALS];


float ultrasonic_calc_distance_cm(volatile uint32_t cap_vals[])
{
    uint32_t ticks = cap_vals[1] - cap_vals[0];

    // convert ticks to time (s)
    double time = (ticks / TIMER_A_CTL_SSEL__SMCLK) * 0.000001;


    // calculate distance (cm)
    float dist = (time * SPEED) / ECHO;

    if(dist >= MIN_DIST)
    {
        if(dist <= MAX_DIST)
        {
            // return calculated distance
            return dist;
        }
        else
        {
            // return error
            return ERROR_OUT_OF_RANGE;
        }
    }
    else
    {
        // return error
        return ERROR_OUT_OF_RANGE;
    }
}


void config_timer_a2(void)
{
    // disable interrupts
        __NVIC_DisableIRQ(TA2_N_IRQn);

    // stop timer
    TIMER_A2->CTL = TIMER_A_CTL_MC_0;

    // clear R register
    TIMER_A2->CTL |= TIMER_A_CTL_CLR;

    // select clock source
    TIMER_A2->CTL |= TIMER_A_CTL_SSEL__SMCLK;

    // set input divider
    TIMER_A2->CTL |= TIMER_A_CTL_ID__1;

    // set capture/compare input select
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CCIS__CCIA;

    // synchronize capture source
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_SCS;

    // set capture mode
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CAP;

    // set capture mode for rising and falling edges (TRM 19.3.3)
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CM__BOTH;

    // enable interrupt flags
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CCIE;

    // clear interrupt flag register
    TIMER_A2->CCTL[3] &= ~TIMER_A_CCTLN_CCIFG;

    // enable interrupts
    TIMER_A2->CTL |= TIMER_A_CTL_IE;
    enable_NVIC_TA2();
}


void enable_NVIC_TA2(void)
{
    __NVIC_EnableIRQ(TA2_N_IRQn);
}

void ultrasonic_open(void)
{
    config_gpio_timera2();
    config_timer_a2();
    timer_a2_start();

    __enable_interrupt();
}

void timer_a2_start(void)
{
    // set TA2 continuous mode
    TIMER_A2 ->CTL |= TIMER_A_CTL_MC__CONTINUOUS;
}

void TA2_N_IRQHandler(void)
{
    // lower interrupts
    TIMER_A2->CTL &= ~TIMER_A_CTL_IFG;
    TIMER_A2->CCTL[3] &= ~TIMER_A_CCTLN_CCIFG;

    // store state of CCTL register
    uint16_t cctl_state = TIMER_A2->CCTL[3];
    uint32_t cctl_r = TIMER_A2->R;

    // handle CCTL[3] interrupt
    // if CCI is HIGH ...
    if(cctl_state & TIMER_A_CCTLN_CCI)
    {
        // store CCR3 value
        capture_values[0] = cctl_r;
    }

    // ... if CCI is LOW ...
    if(!(cctl_state & TIMER_A_CCTLN_CCI))
    {
        // check if overflow bit set...
        if(cctl_state & TIMER_A_CCTLN_COV)
        {
            // ...  clear COV bit
            TIMER_A2->CCTL[3] &= ~TIMER_A_CCTLN_COV;

            // calculate capture value
            capture_values[1] = cctl_r + MAX_TICKS;
        }
        // ... overflow bit not set ...
        else
        {
            // set capture value
            capture_values[1] = cctl_r;
        }

        float calc_dist = ultrasonic_calc_distance_cm(capture_values);

        if(calc_dist == ERROR_OUT_OF_RANGE)
        {
            printf("ERROR: Calculated distances out of bounds\n");
        }
        else
        {
            printf("Calculuated distance: %f\n", calc_dist);
        }

        pwm_open();

        TIMER_A2->CCTL[3] = cctl_state;
        TIMER_A2->R = cctl_r;
    }
}
