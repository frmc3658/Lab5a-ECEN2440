/*
 * ultrasoni.c
 *
 *  Created on: Oct 17, 2022
 *      Author: fjmcd
 */

#include "ultrasonic.h"
#include "msp.h"


//static void add_scheduled_event(timer_a2_callback);
static volatile uint32_t capture_values[CAP_VALS];

uint32_t ultrasonic_calc_distance_cm(volatile uint32_t *cap_vals)
{
    uint32_t ticks = cap_vals[1] - cap_vals[2];

    // TODO: convert ticks to time
    uint32_t time;

    // TODO: calculate distance
    uint32_t dist;

    if(dist >= ERR_LESS_THAN_MIN_DIST)
    {
        if(dist <= ERR_GREATER_THAN_MAX_DIST)
        {
            // return calculated distance
            return dist;
        }
        else
        {
            // TODO: handle return error
            return 1;
        }
    }
    else
    {
        // TODO: handle return error
        return 0;
    }
}


void timer_a_0_init_trig(void)
{

}

void timer_a_2_init_measure_echo_cci(void)
{
    // set P6.6 as input
    P6->DIR &= ~BIT6;

    // selecting primary function for TA2.3
    P6->SEL0 |= BIT6;
    P6->SEL1 &= ~BIT6;

    enable_NVIC_TA2();
}

void config_timer_a2(void)
{
    // clear R register
    TIMER_A2->CTL |= TIMER_A_CTL_CLR;

    // select clock source
    TIMER_A2->CTL |= TIMER_A_CTL_SSEL__SMCLK;

    // set continuous mode
    TIMER_A2 -> CTL &= TIMER_A_CTL_MC__CONTINUOUS;

    // enable interrupts
    TIMER_A2->CTL |= TIMER_A_CTL_IE;

    // set capture mode for rising and falling edges (TRM 19.3.3)
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CM__BOTH;

    // set capture/compare input select
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CCIS__CCIA;

    // set capture mode
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CAP;

    // enable interrupt flags
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CCIE;

    // clear interrupt flag register
    TIMER_A2->CCTL[3] &= ~TIMER_A_CCTLN_CCIFG;
}

void enable_NVIC_TA2(void)
{
    __NVIC_EnableIRQ(TA2_N_IRQn);
}

void TA2_N_IRQHandler(void)
{
    // store state of CCTL register
    uint16_t flags;
    flags = TIMER_A2->CCTL[3];

    // lower interrupt flags
    TIMER_A2->CTL &= ~TIMER_A_CTL_IFG;
    TIMER_A2->CCTL[3] &= ~TIMER_A_CCTLN_CCIFG;

    // handle CCTL[3] interrupt
    // if CCI is HIGH ...
    if(flags & TIMER_A_CCTLN_CCI)
    {
        // ...  clear COV bit
        TIMER_A2->CCTL[3] &= ~TIMER_A_CCTLN_COV;

        // store CCR3 value
        capture_values[0] = TIMER_A2->CCR[3];
    }

    // ... if CCI is LOW ...
    if(!(flags & TIMER_A_CCTLN_CCI))
    {
        // check if overflow bit set...
        if(flags & TIMER_A_CCTLN_COV)
        {
            // calculate capture value
            capture_values[1] = TIMER_A2->CCR[3] + MAX_TICKS;
        }
        // ... overflow bit not set ...
        else
        {
            // set capture value
            capture_values[1] = TIMER_A2->CCR[3];
        }
    }

    ultrasonic_calc_distance_cm(capture_values);
}
