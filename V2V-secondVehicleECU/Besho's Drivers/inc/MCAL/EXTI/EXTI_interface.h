/*
 * EXTI_interface.h
 *
 *  Created on: january 18, 2023
 *      Author: beshoy
 */
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

void	MEXTI_voidInit			(void);
void	MEXTI_voidEnableExti	(u8	Copy_u8ExtiNum);
void	MEXTI_voidSetExtiEdge	(u8 Copy_u8ExtiNum , u8 Copy_u8Edge);
void 	MEXTI_voidSetEXTILinePin	(u8 Copy_u8ExtiNum, u8 Copy_u8Port);
void	MEXTI_voidDisableExti	(u8	Copy_u8ExtiNum);
void	MEXTI_voidEnableSWI		(u8	Copy_u8ExtiNum);
void	MEXTI_voidSetCallBack	(void (*ptr) (void));

#define	MEXTI_RISING_EDGE			0
#define	MEXTI_FALLING_EDGE			1
#define	MEXTI_IOC_EDGE				2

#define	MEXTI_LINE0					0
#define	MEXTI_LINE1					1
#define	MEXTI_LINE2					2
#define	MEXTI_LINE3					3
#define	MEXTI_LINE4					4
#define	MEXTI_LINE5					5
#define	MEXTI_LINE6					6
#define	MEXTI_LINE7					7
#define	MEXTI_LINE8					8
#define	MEXTI_LINE9					9
#define	MEXTI_LINE10				10
#define	MEXTI_LINE11				11
#define	MEXTI_LINE12				12
#define	MEXTI_LINE13				13
#define	MEXTI_LINE14				14
#define	MEXTI_LINE15				15

#define EXTI_PORTA 					0b0000
#define EXTI_PORTB 					0b0001
#define EXTI_PORTC 					0b0010

#endif
