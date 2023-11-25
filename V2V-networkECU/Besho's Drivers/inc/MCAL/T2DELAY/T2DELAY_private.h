/*
 * T2DELAY_private.h
 *
 *  Created on: February 2, 2023
 *      Author: beshoy
 */

#ifndef T2DELAY_PRIVATE_H_
#define T2DELAY_PRIVATE_H_

typedef struct
{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMCR;
	volatile u32 DIER;
	volatile u32 SR;
	volatile u32 EGR;
	volatile u32 CCMR1;
	volatile u32 CCMR2;
	volatile u32 CCER;
	volatile u32 CNT;
	volatile u32 PSC;
	volatile u32 ARR;
	volatile u32 Reserved1;
	volatile u32 CCR1;
	volatile u32 CCR2;
	volatile u32 CCR3;
	volatile u32 CCR4;
	volatile u32 Reserved2;
	volatile u32 DCR;
	volatile u32 DMAR;
}TIMER_T;

#define TIMER2 ((TIMER_T *)0x40000400)
#define CEN 0
#define ARPE 7
#define DIR 4
#define UIE 0 

#endif
