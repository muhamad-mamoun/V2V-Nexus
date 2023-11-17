/*
 * RCC_prv.h
 *
 * Created: 11/17/2023 
 *  Author: Ahmed Wael
 */

#ifndef _RCC_PRV_H_
#define _RCC_PRV_H_

typedef struct {
volatile u32 RCC_CR;
volatile u32 RCC_CFGR;
volatile u32 RCC_CIR;
volatile u32 RCC_APB2RSTR;
volatile u32 RCC_APB1RSTR;
volatile u32 RCC_AHBENR;
volatile u32 RCC_APB2ENR;
volatile u32 RCC_APB1ENR;
volatile u32 RCC_BDCR;
volatile u32 RCC_CSR;
volatile u32 RCC_AHBRSTR;
volatile u32 RCC_CFGR2;
volatile u32 RCC_CFGR3;
}RCC_t;

#define RCC ((RCC_t*)0x40021000)





#endif