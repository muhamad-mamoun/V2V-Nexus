/*
 * ADC_prv.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Ahmed Dwidar
 */

#ifndef ADC_PRV_H_
#define ADC_PRV_H_

#include"gpio.h"
#include"gpio_cfg.h"
#include"gpio_prv.h"
#include"ADC.h"

#define ADC_BASE_ADDRESS                  0x50000000

typedef struct
{
	volatile u32 ISR;
	volatile u32 IER;
	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 SMPR1;
	volatile u32 SMPR2;
	volatile u32 TR1;
	volatile u32 TR2;
	volatile u32 TR3;
	volatile u32 SQR1;
	volatile u32 SQR2;
	volatile u32 SQR3;
	volatile u32 SQR4;
	volatile u32 DR;
	volatile u32 Reserved1;
	volatile u32 Reserved2;
	volatile u32 JSQR;
	volatile u32 Reserved3;
	volatile u32 Reserved4;
	volatile u32 OFR1;
	volatile u32 OFR2;
	volatile u32 OFR3;
	volatile u32 OFR4;
	volatile u32 Reserved5;
	volatile u32 Reserved6;
	volatile u32 JDR1;
	volatile u32 JDR2;
	volatile u32 JDR3;
	volatile u32 JDR4;
	volatile u32 Reserved7;
	volatile u32 Reserved8;
	volatile u32 Reserved9;
	volatile u32 Reserved10;
	volatile u32 AWD2CR;
	volatile u32 AWD3CR;
	volatile u32 Reserved11;
	volatile u32 Reserved12;
	volatile u32 DIFSEL;
	volatile u32 CALFACT;

}ADC_T;

#define ADC1 ((volatile ADC_T *) ADC_BASE_ADDRESS)


#endif /* ADC_PRV_H_ */
