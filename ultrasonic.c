/*
 * ultrasoni.c
 *
 *  Authors: Brendan N, Frank M, Shane M
 */

//***************************************************************
// included files
//**************************************************************/
#include "ultrasonic.h"


//***************************************************************
// static variables
//**************************************************************/
static volatile uint32_t capture_values[CAP_VALS];


//***************************************************************
// function definitions
//**************************************************************/
void ultrasonic_open(void)
{
    config_gpio_echo_timer();
    config_echo_timer();
    echo_timer_start();

    __enable_interrupt();
}


float ultrasonic_calc_distance_cm(volatile uint32_t cap_vals[])
{
    // calculate ticks
    uint32_t ticks = cap_vals[1] - cap_vals[0];

    // convert ticks to time (s)
    double time = (ticks / TIMER_A_CTL_SSEL__SMCLK) / MICRO_S_TO_SEC;


    // calculate distance (cm)
    float dist = (time * SPEED) / ECHO;

    // if distance >= 2cm ...
    if(dist >= MIN_DIST)
    {
        // ... and if distance <= 400cm
        if(dist <= MAX_DIST)
        {
            // return calculated distance
            return dist;
        }
        // ... else ...
        else
        {
            // return error
            return ERROR_OUT_OF_RANGE;
        }
    }
    // ... else ...
    else
    {
        // return error
        return ERROR_OUT_OF_RANGE;
    }
}


void config_echo_timer(void)
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

    // set capture/compare input select for CCIA
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CCIS__CCIA;

    // synchronize capture source
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_SCS;

    // set capture mode
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CAP;

    // set capture mode for rising and falling edges (TRM 19.3.3)
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CM__BOTH;

    // enable capture/compare interrupts
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CCIE;

    // lower capture/compare interrupt flag
    TIMER_A2->CCTL[3] &= ~TIMER_A_CCTLN_CCIFG;

    // enable timer interrupts
    TIMER_A2->CTL |= TIMER_A_CTL_IE;

    // enable interrupts in NVIC
    __NVIC_EnableIRQ(TA2_N_IRQn);
}



void echo_timer_start(void)
{
    // set TA2 mode control: continuous mode
    TIMER_A2 ->CTL |= TIMER_A_CTL_MC__CONTINUOUS;
}

void TA2_N_IRQHandler(void)
{
    // lower timer and capture/compare interrupt flags
    TIMER_A2->CTL &= ~TIMER_A_CTL_IFG;
    TIMER_A2->CCTL[3] &= ~TIMER_A_CCTLN_CCIFG;

    // save capture/compare and counter states
    uint16_t cctl_state = TIMER_A2->CCTL[3];
    uint16_t cctl_r = TIMER_A2->R;

    // if CCI is HIGH ...
    if(cctl_state & TIMER_A_CCTLN_CCI)
    {
        // store capture value
        capture_values[0] = cctl_r;
    }

    // if CCI is LOW ...
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
            // store capture value
            capture_values[1] = cctl_r;
        }

        // calculate ultrasonic distance
        float calc_dist = ultrasonic_calc_distance_cm(capture_values);

        // if distance is within range (2cm - 400cm)
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
