/*
 * PWM_config.h
 *
 *  Created on: April 7, 2023
 *      Author: beshoy
 */
#ifndef PWM_CONFIG_H_
#define PWM_CONFIG_H_

/** NOTE THAT
TIM2-> "CH1 PA0" - "CH2 PA1" - "CH3 PA2" - "CH4 PA3"
TIM3-> "CH1 PA6" - "CH2 PA7" - "CH3 PB0" - "CH4 PB1"
TIM4-> "CH1 PB6" - "CH2 PB7" - "CH3 PB8" - "CH4 PB9"
TIM5-> 									   "CH4 PA3"
*/

/*Choose between PWM_M1 - PWM_M2*/
#define PWM_MODE PWM_M1
/*SET PRESCALLER*/
#define TIMER_PRESCALLER 1
/*SET auto reload value*/
#define AUTO_RELOAD_VAL  8000
#endif
