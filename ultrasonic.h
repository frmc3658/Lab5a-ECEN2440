/*
 * ultrasonic.h
 *
 *  Created on: Oct 17, 2022
 *      Author: fjmcd
 */

#ifndef ULTRASONIC_HG
#define ULTRASONIC_HG

#include <stdint.h>


typedef struct
{
    uint32_t lower_bound;
    uint32_t upper_bound;
    uint32_t distance;
    uint32_t speed;
    uint32_t time;
    uint32_t current_R;
    uint32_t previous_R;
    uint32_t echo_length;
}Sensor;


#define ERR_LESS_THAN_MIN_DIST          (uint32_t)0X02    // 2CM
#define ERR_GREATER_THAN_MAX_DIST       (uint32_t)0X190   // 400CM

uint32_t ultrasonic_calc_distance_cm(uint32_t *cap_vals);
void timer_a_0_init_trig(void);


#endif
