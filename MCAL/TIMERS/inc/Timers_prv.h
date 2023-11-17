/*
 * Timers_prv.h
 *
 * Created: 11/16/2023 
 *  Author: Ahmed Wael
 */

#ifndef _TIMERS_PRV_H_
#define _TIMERS_PRV_H_


#define TIMER_2_BASE_ADDRESS	0x40000000
#define TIMER_3_BASE_ADDRESS	0x40000400
#define TIMER_4_BASE_ADDRESS	0x40000800  


typedef struct
{
	volatile u32 Timerx_CR1;   //
	volatile u32 Timerx_CR2;
	volatile u32 Timerx_SMCR;
	volatile u32 Timerx_DIER;
	volatile u32 Timerx_SR;
	volatile u32 Timerx_EGR;
	volatile u32 Timerx_CCMR1;
	volatile u32 Timerx_CCMR2;
	volatile u32 Timerx_CCER;
	volatile u32 Timerx_CNT;
	volatile u32 Timerx_PSC; //
	volatile u32 Timerx_ARR; //
	volatile u32 Timerx_Reserved;
	volatile u32 Timerx_CCR1;
	volatile u32 Timerx_CCR2;
	volatile u32 Timerx_CCR3;	
	volatile u32 Timerx_CCR4;
	volatile u32 Timerx_Reserved2;
	volatile u32 Timerx_DCR;
	volatile u32 Timerx_DMAR;
}Timerx_Regs_t;



#define TIMER_2_REGS ((Timerx_Regs_t*)TIMER_2_BASE_ADDRESS)
#define TIMER_3_REGS ((Timerx_Regs_t*)TIMER_3_BASE_ADDRESS)
#define TIMER_4_REGS ((Timerx_Regs_t*)TIMER_4_BASE_ADDRESS)





#endif


