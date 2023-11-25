#ifndef		RTOS_PRIVATE_H
#define		RTOS_PRIVATE_H

typedef	struct
{
	u16		u16_Periodicty;
	
	void	(*PF)	(void);
	
}Task_TCB;

void	RTOS_voidScheduler(void);

#endif