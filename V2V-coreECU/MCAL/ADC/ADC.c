/*
 * ADC.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Ahmed Dwidar
 */
#include"ADC_prv.h"
#include"ADC.h"
#include"RCC.h"

void(*ADCClbk_ptr)(void) = PTR_NULL;

void ADC_Init(ADC_confic *ADC_config_ptr)
{

	// enable clock to ADC1
	RCC_voidEnablePeripheral(APB2_BUS,ADC1);
	GPIO_configurePin(&input_channel);

	ADC1 ->CR |= (ADC_config_ptr ->refVolt<<28);

	ADC1->CFGR |= (ADC_config_ptr ->conversion<<13);   // set conversion

	ADC1->CFGR |= (ADC_config_ptr ->allignment<<5);   // set allignment

	ADC1->CFGR |= (ADC_config_ptr ->resolution<<3);  // set resolution

	ADC1 ->SQR3 |= (1<<0); // ch1 is first to be converted

	ADC1 ->SMPR1 = (ADC_config_ptr ->samplingTime<<3);

#if(POLLING == 0)
	// enable global interrupt
	ADC1 ->IER |= (1<<2);
#else
	ADC1 ->IER &= ~(1<<2);
#endif
}

void ADC_StartConversion(void)
{

	SET_BIT(ADC1 ->CR,0); // enable ADC

	while(BIT_IS_CLEAR(ADC1->ISR,0)){}   // wait ADC ready flag

	SET_BIT(ADC1->CR,2); // start convert

}

#if(POLLING == 1)
void ADC_GetConversionState(u8 *convStateP )
{
	*convStateP = (ADC1->ISR) & (1<<2);  // get state of ADC EOF flag
}
#endif

u8 ADC_ReadData(u16* convertedData)
{
	if(GET_BIT(ADC1->ISR,2) == 1)
	{
		*convertedData = ADC1 ->DR; // store the data converted
		return 0;
	}

	return 1;

}

void ADC_setCallBack(void(*loc_ADCClbk_ptr)(void))
{
	ADCClbk_ptr = loc_ADCClbk_ptr;
}

int main()
{
	u16 *ptr;
	/*
	 * 	voltageConfig            refVolt;
	conversionMode_config    conversion	;
	dataAllignment_config    allignment;
	dataResolution_config    resolution;
	smplTime_config          samplingTime;
	 * */
	ADC_confic ADC_initialization = {voltageRedEnable,singleConv,rightAllign,bit_12,clksycles_181AndHAlf};

	ADC_Init(&ADC_initialization);
//	ADC_StartConversion();
//	ADC_ReadData(ptr);
}
