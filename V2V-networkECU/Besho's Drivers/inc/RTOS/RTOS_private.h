/*
 * RTOS_private.h
 *
 *  Created on: Aug 22, 2022
 *      Author: Loka
 */

#ifndef SERVICE_RTOS_RTOS_PRIVATE_H_
#define SERVICE_RTOS_RTOS_PRIVATE_H_

typedef struct
{
	u16 u16_periodicty;
  u16 First_Delay;
	void (*PF)  (void);
}TASK_TCB;

 void RTOS_voidScheduler(void);

#endif /* SERVICE_RTOS_RTOS_PRIVATE_H_ */
