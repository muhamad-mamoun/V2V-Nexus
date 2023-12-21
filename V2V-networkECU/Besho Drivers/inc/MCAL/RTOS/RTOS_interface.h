#ifndef		RTOS_INTERFACE_H
#define		RTOS_INTERFACE_H

void	RTOS_voidInit(void);
void	RTOS_voidCreateTask(u8 Copy_u8Priority , u16 Copy_u16Periodicity , void (*Copy_PF)(void));

#endif