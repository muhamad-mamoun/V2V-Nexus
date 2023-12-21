/*
 * RTOS_interface.h
 *
 *  Created on: Aug 22, 2022
 *      Author: Loka
 */

#ifndef SERVICE_RTOS_RTOS_INTERFACE_H_
#define SERVICE_RTOS_RTOS_INTERFACE_H_

void RTOS_voidInit(void);
void RTOS_voidCreateTask(u8 A_u8Priority , u16 A_u16Periodicity , void(*A_PF)(void),u16 A_u16First_Delay);

#endif /* SERVICE_RTOS_RTOS_INTERFACE_H_ */
