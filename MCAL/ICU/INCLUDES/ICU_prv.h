#ifndef ICU_PRV_H_
#define ICU_PRV_H_
#include "std_types.h"
#include "common_macros.h"

typedef struct
{
	u32 CR1;
	u32 CR2;
	u32 SMCR;
	u32 DIER;
	u32 SR;
	u32 EGR;
	u32 CCMR1;
	u32 CCMR2;
	u32 CCER;
	u32 CNT;
	u32 PSC;
	u32 ARR;
	u32 Reseved1;
	u32 CCR1;
	u32 CCR2;
	u32 CCR3;
	u32 CCR4;
	u32 Reseved2;
	u32 DCR;
	u32 DMAR;

}TIMx_t;


TIMx_t *Timer[3] = 
{
	((volatile TIMx_t *)0x40000000),
	((volatile TIMx_t *)0x40000400),
	((volatile TIMx_t *)0x40000800)	
};

#define ICU_INTEnable		1
#define ICU_INTDisable		0

#define TIMER_INTEnable		1
#define TIMER_INTDisable	0


#define OPM	3

#define CC1IE	1
#define UIE		0
#define CEN		0
#define UIF		0
#define CC1IF	1
#endif
