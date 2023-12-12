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

#define ADC_BASE_ADDRESS    0x50000000
#define ADC_COMM_REG_BASE_ADDRESS         0x50000300

typedef struct
{
	volatile u32 ISR;
	volatile u32 IER;
	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 R1;
	volatile u32 SMPR1;
	volatile u32 SMPR2;
	volatile u32 R2;

	volatile u32 TR1;
	volatile u32 TR2;
	volatile u32 TR3;
	volatile u32 R3;

	volatile u32 SQR1;
	volatile u32 SQR2;
	volatile u32 SQR3;
	volatile u32 SQR4;
	volatile u32 DR;
	volatile u32 Reserved1;
	volatile u32 Reserved2;
	volatile u32 JSQR;
	volatile u32 Reserved[4];
	volatile u32 OFR1;
	volatile u32 OFR2;
	volatile u32 OFR3;
	volatile u32 OFR4;
	volatile u32 Reserved5[4];
	volatile u32 JDR1;
	volatile u32 JDR2;
	volatile u32 JDR3;
	volatile u32 JDR4;
	volatile u32 Reserved6[4];
	volatile u32 AWD2CR;
	volatile u32 AWD3CR;
	volatile u32 Reserved11;
	volatile u32 Reserved12;
	volatile u32 DIFSEL;
	volatile u32 CALFACT;

}ADC_T;
typedef struct
{
	volatile u32 CSR;
	volatile u32 Reserved12;
	volatile u32 CCR;
	volatile u32 CDR;
}ADC_C;

#define ADC1 ((volatile ADC_T *) ADC_BASE_ADDRESS)
#define ADC2 ((volatile ADC_C *) ADC_COMM_REG_BASE_ADDRESS)


#endif /* ADC_PRV_H_ */
