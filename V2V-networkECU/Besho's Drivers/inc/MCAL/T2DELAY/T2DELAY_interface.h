/*
 * T2DELAY_interface.h
 *
 *  Created on: February 2, 2023
 *      Author: beshoy
 */

#ifndef T2DELAY_INTERFACE_H_
#define T2DELAY_INTERFACE_H_

void MTIMER2_voidInitTimer2Delay(void);
void MTIMER2_voidSetinterruptTimer(void);
void MTIMER2_voidSetCallBack(void (*ptr)(void));
void MTIMER2_voidStartDealyInMicroSeconds(u32 Copy_u32Delay);

#endif