/**
 * main.c
 */

#include "msp.h"
#include "ultrasonic.h"
#include "pwm.h"
#include <stdio.h>

#define TEST 401

uint32_t ultrasonic_calc_distance(void)
{
    uint32_t *test_val;
    uint32_t test = TEST;
    test_val = &test;

    return ultrasonic_calc_distance_cm(test_val);
}

void unit_test(uint32_t test_value)
{
    if(test_value < ERR_LESS_THAN_MIN_DIST)
    {
        printf("Test for distance less than minimum of 2cm: FAIL\n");
    }
    else if(test_value > ERR_GREATER_THAN_MAX_DIST)
    {
        printf("Test for distance greater than maximum of 400cm: FAIL\n");
    }
    else
    {
        printf("GOOD Data\n");
    }
}

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    uint32_t result = ultrasonic_calc_distance();

    pwm_open();

    while(1)
    {
        unit_test(result);
    }
}
