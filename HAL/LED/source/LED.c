/*
 * LED.c
 *
 *  Created on: Nov 15, 2023
 *      Author: Ahmed Dwidar
 */
#include"../includes/LED.h"

/*
configure leds pins initialization
*/
/*
write Led pin to logic high
*/
void LED_on(GPIO_portIDType a_ledPort,GPIO_pinIDType a_ledPin)
{
	GPIO_writePin(a_ledPort,a_ledPin,GPIO_HIGH_PIN);
}
void LED_off(GPIO_portIDType a_ledPort,GPIO_pinIDType a_ledPin)
{
	GPIO_writePin(a_ledPort,a_ledPin,GPIO_LOW_PIN);
}
