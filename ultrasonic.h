/*
 * ultrasonic.h
 *
 *  Authors: Brendan N, Frank M, Shane M
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_


//***************************************************************
// included files
//**************************************************************/
/* System include statements */
#include <stdint.h>
#include <stdio.h>

/* Texas Instruments includes */
#include "msp.h"

/* Developer includes */
#include "gpio.h"
#include "pwm.h"


//***************************************************************
// enums
//**************************************************************/


//***************************************************************
// structs
//**************************************************************/


//***************************************************************
// defined macros
//**************************************************************/
#define CAP_VALS            2                       // number of capture values
#define MAX_TICKS           ((uint16_t) 0XFFFF)     // max value of ticks is 65535
#define SPEED               0x85FC                  // 34300 cm/s; speed of sound assuming dry air @ 68°F
#define MICRO_S_TO_SEC      0XF4240                 // divide by 1,000,000 to convert micro_s to s
#define ECHO                2                       // divide echo length by 2
#define MIN_DIST            (uint32_t)0X02          // 2cm
#define MAX_DIST            (uint32_t)0X190         // 400cm
#define ERROR_OUT_OF_RANGE  0                       // error code: measured distance out of range


//***************************************************************
// function prototypes
//**************************************************************/
void ultrasonic_open(void);
void config_echo_timer(void);
void echo_timer_start(void);
float ultrasonic_calc_distance_cm(volatile uint32_t cap_vals[]);

#endif /* ULTRASONIC_H_ */
