/*
 * EXTI_private.h
 *
 *  Created on: january 18, 2023
 *      Author: beshoy
 */
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

typedef	struct
{
	volatile	u32		IMR	;
	volatile	u32		EMR	;
	volatile	u32		RSTR;
	volatile	u32		FSTR;
	volatile	u32		SWIER;
	volatile	u32		PR;
	
}EXTI_Type;

#define EXTI			((EXTI_Type *)0x40010400)
#define AFIO_OFFSET		(0x40010000)
#define AFIO_EXTICR1	*((volatile u32 *)(AFIO_OFFSET+0x08))
#define AFIO_EXTICR2	*((volatile u32 *)(AFIO_OFFSET+0x0C))
#define AFIO_EXTICR3	*((volatile u32 *)(AFIO_OFFSET+0x10))
#define AFIO_EXTICR4	*((volatile u32 *)(AFIO_OFFSET+0x14))
#endif
