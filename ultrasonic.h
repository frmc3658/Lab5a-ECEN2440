/*
 * ultrasonic.h
 *
 *  Created on: Oct 17, 2022
 *      Author:
 */

#ifndef ULTRASONIC_HG
#define ULTRASONIC_HG

#include <stdint.h>
#include <stdio.h>
#include "msp.h"
#include "gpio.h"
#include "pwm.h"

#define CAP_VALS            2                       // number of capture values
#define MAX_TICKS           ((uint16_t) 0XFFFF)     // max value of ticks is 65535
#define SPEED               0x85FC                  // 34300 cm/s; speed of sound assuming dry air @ 68°F
#define ECHO                2                       // divide echo length by 2
#define MIN_DIST            (uint32_t)0X02          // 2cm
#define MAX_DIST            (uint32_t)0X190         // 400cm
#define ERROR_OUT_OF_RANGE  0                       // error code: measured distance out of range

float ultrasonic_calc_distance_cm(volatile uint32_t cap_vals[]);
void ultrasonic_open(void);
void config_timer_a2(void);
void timer_a2_start(void);
void enable_NVIC_TA2(void);


#endif
