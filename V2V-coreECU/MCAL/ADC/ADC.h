/*
 * ADC.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Ahmed Dwidar
 */

#ifndef ADC_H_
#define ADC_H_

#include"std_types.h"
#include"common_macros.h"

#define POLLING              1

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1<<BIT)))

#define ADC_INPUT_CHANNEL_PORT   GPIO_PORTA_ID
#define ADC_INPUT_CHANNEL_PIN    GPIO_PIN00_ID

GPIO_configurationsType input_channel = {ADC_INPUT_CHANNEL_PORT,ADC_INPUT_CHANNEL_PIN,GPIO_ANALOG_MODE,GPIO_LOW_SPEED};

typedef enum
{
	singleConv,
	continuousConv
}conversionMode_config;

typedef enum
{
	rightAllign,
	leftAllign
}dataAllignment_config;

typedef enum
{
	intermidiateState,
	voltageRedEnable,
	voltageRedEdisable
}voltageConfig;

typedef enum
{
	bit_12,
	bit_10,
	bit_8,
	bit_6
}dataResolution_config;

typedef enum
{
	clksycles_oneAndHAlf,
	clksycles_twoAndHAlf,
	clksycles_fourAndHAlf,
	clksycles_sevenAndHAlf,
	clksycles_19AndHAlf,
	clksycles_61AndHAlf,
	clksycles_181AndHAlf,
	clksycles_601AndHAlf,
}smplTime_config;

typedef struct
{
	voltageConfig            refVolt;
	conversionMode_config    conversion	;
	dataAllignment_config    allignment;
	dataResolution_config    resolution;
	smplTime_config          samplingTime;
}ADC_confic;




void ADC_Init(ADC_confic *ADC_config_ptr);

// Start ADC conversion
void ADC_StartConversion(void);

// Get ADC conversion result
void ADC_GetConversionState(u8 *convStateP );

u8 ADC_ReadData(u16* convertedData);



#endif /* ADC_H_ */
