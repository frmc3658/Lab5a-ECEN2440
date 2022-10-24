/*
 * ultrasoni.c
 *
 *  Created on: Oct 17, 2022
 *      Author: fjmcd
 */

#include "ultrasonic.h"
#include "msp.h"


//static void add_scheduled_event(timer_a2_callback);

uint32_t ultrasonic_calc_distance_cm(uint32_t *cap_vals)
{
    uint32_t dist;
    dist = *cap_vals;

    if(dist >= ERR_LESS_THAN_MIN_DIST)
    {
        if(dist <= ERR_GREATER_THAN_MAX_DIST)
        {
            // return calculated distance
            return dist;
        }
        else
        {
            // return error
            return 401;
        }
    }
    else
    {
        // return error
        return 1;
    }
}


void timer_a_0_init_trig(void)
{

}
