/*
 * gpio.h
 *
 *  Authors: Brendan N, Frank M, Shane M
 */

#ifndef GPIO_H_
#define GPIO_H_

//***************************************************************
// included files
//**************************************************************/
/* System include statements */

/* Texas Instruments includes */
#include "msp.h"

/* Developer includes */

//***************************************************************
// defined macros
//**************************************************************/


//***************************************************************
// enums
//**************************************************************/


//***************************************************************
// structs
//**************************************************************/


//***************************************************************
// function prototypes
//**************************************************************/
void config_gpio_trigger_timer(void);
void config_gpio_echo_timer(void);

#endif /* GPIO_H_ */
