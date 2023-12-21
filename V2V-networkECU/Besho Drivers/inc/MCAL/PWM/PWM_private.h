/*
 * PWM_private.h
 *
 *  Created on: April 7, 2023
 *      Author: beshoy
 */

#ifndef PWM_PRIVATE_H
#define PWM_PRIVATE_H

#define TIM2_ADDRESS 0x40000000
#define TIM3_ADDRESS 0x40000400
#define TIM4_ADDRESS 0x40000800
#define TIM5_ADDRESS 0x40000C00
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
}TIMx_T;
TIMx_T *TIM[4] = 
{
	( TIMx_T *)TIM2_ADDRESS,
	( TIMx_T *)TIM3_ADDRESS,
	( TIMx_T *)TIM4_ADDRESS,
	( TIMx_T *)TIM5_ADDRESS
};   
#define PWM_M1 0b110
#define PWM_M2 0b111

/*CR1*/
#define ARPE   7
#define CMS1   6
#define CMS0   5
#define DIR    4
#define CEN    0
/*EGR*/
#define UG     0
/*CCER*/
#define CC1E   0
#define CC2E   4
#define CC3E   8
#define CC4E   12
/*CCMR1 and CCMR2*/
#define OC1PE  3
#define OC2PE  11
#define OC3PE  3
#define OC4PE  11
#define OC1M   4
#define OC2M   12
#define OC3M   4
#define OC4M   12
#endif
