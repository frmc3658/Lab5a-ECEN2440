/*
 * pwm.h
 *
 */

//***************************************************************
// header guards
//**************************************************************/
#ifndef PWM_H_
#define PWM_H_

//***************************************************************
// included files
//**************************************************************/
#include "msp.h"


//***************************************************************
// defined macros
//**************************************************************/
#define TICKS               ((uint16_t) 0x12C)//300
#define CCR1_DUTY_10mics        ((uint16_t) 0x10E)//370

//***************************************************************
// function prototypes
//**************************************************************/
void pwm_open(void);
void stop_pwm(void);
void start_pwm(void);
void config_pwm_timer(void);
void config_pwm_timer_10mics(void);
//void config_pwm_timer_50_int(void);
//void config_pwm_timer_50(void);
//void config_pwm_timer_75(void);
void config_gpio(void);
void config_gpio_int(void);

//***************************************************************
// nvic-nested vector interrupt controller
//**************************************************************/
void config_nvic(void);

#endif /* PWM_H_ */
