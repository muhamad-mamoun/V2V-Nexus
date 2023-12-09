/*
 * KPD_interface.h
 *
 *  Created on: Sep 2, 2022
 *      Author: M-TECH
 */

#ifndef HAL_KPD_KPD_INTERFACE_H_
#define HAL_KPD_KPD_INTERFACE_H_





/************************************************************************************************/
/*                                    Functions' prototypes                                     */
/************************************************************************************************/

/*This function is used to initialize KPD module*/
void hkpd_init(void);

/*This function is used to get the pressed keypad key*/
void hkpd_getPressedKey(u8* pu8_key);



#endif /* HAL_KPD_KPD_INTERFACE_H_ */
