/*
 * LED.h
 *
 *  Created on: Nov 15, 2023
 *      Author: Ahmed Dwidar
 */

#ifndef LED_H_
#define LED_H_

#include"../../../OTHERS/common_macros.h"
#include"../../../OTHERS/std_types.h"
#include"../../../MCAL/GPIO/INCLUDES/gpio.h"


/*drive led1 pin to logic high*/
void LED_on(void);
/*drive led1 pin to logic low*/
void LED_off(void);


#endif /* LED_H_ */
