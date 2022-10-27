/*
 * pwm.h
 *
 */

#ifndef PWM_H_
#define PWM_H_

//***************************************************************
// included files
//**************************************************************/
#include "msp.h"


//***************************************************************
// defined macros
//**************************************************************/
#define TICKS                   ((uint16_t) 0x12C)  //300
#define CCR1_DUTY_10mics        ((uint16_t) 0x10E)  //270

//***************************************************************
// function prototypes
//**************************************************************/
void pwm_open(void);
void stop_pwm(void);
void start_pwm(void);
void config_pwm_timer(void);
void config_gpio_timera0(void);

//***************************************************************
// nvic-nested vector interrupt controller
//**************************************************************/
void config_nvic(void);

#endif /* PWM_H_ */
