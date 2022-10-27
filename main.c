/**
 * main.c
 *
 *  Authors: Brendan N, Frank M, Shane M
 */

//***************************************************************
// included files
//**************************************************************/
/* System include statements */
#include <stdbool.h>

/* Texas Instruments includes */
#include "msp.h"

/* Developer includes */
#include "pwm.h"
#include "ultrasonic.h"


//***************************************************************
// static variables
//**************************************************************/


//***************************************************************
// main function
//**************************************************************/
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    pwm_open();
    ultrasonic_open();

    while(true)
    {

    }
}
