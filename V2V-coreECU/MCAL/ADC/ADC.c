/*
 * ADC.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Ahmed Dwidar
 */
#include "ADC_prv.h"
#include "ADC.h"
#include "RCC.h"

void(*ADCClbk_ptr)(void) = PTR_NULL;

void ADC_Init(ADC_config *ADC_config_ptr)
{
	//GPIO_INPUT_FLOAT_MODE
	GPIO_configurationsType input_channel = {ADC_INPUT_CHANNEL_PORT,ADC_INPUT_CHANNEL_PIN,GPIO_ANALOG_MODE,GPIO_LOW_SPEED};

	// enable clock to ADC1
	RCC_voidEnablePeripheral(AHB_BUS,ADC_EN);
	RCC_voidEnablePeripheral(AHB_BUS,GPIOA_EN);
	ADC2 ->CCR |= (1<<17); ///////////////
	ADC2 ->CCR |= (1<<22);  //VREFINT
	GPIO_configurePin(&input_channel);
//	ADC1->CR = (ADC_config_ptr ->refVolt<<28);
		for(int i = 0; i<100000;i++){}
	ADC1->SMPR1 = (ADC_config_ptr ->samplingTime<<3);

	//SET_BIT(ADC1 ->CR,0);
//	ADC1->CR = (ADC_config_ptr ->refVolt<<28);

	ADC1->CFGR |= (ADC_config_ptr ->conversion<<13);   // set conversion
	ADC1->CFGR |= (ADC_config_ptr ->allignment<<5);   // set allignment
	ADC1->CFGR |= (ADC_config_ptr ->resolution<<3);  // set resolution
	ADC1->SQR1 |= (18<<6); // ch1 is first to be converted

//#if POLLING == 0
	// enable global interrupt
//	ADC1 ->IER |= (1<<2);
//#else
//	ADC1 ->IER &= ~(1<<2);
//#endif

SET_BIT(ADC1 ->CR,0); // enable ADC

}

void ADC_StartConversion(void)
{
	 while(BIT_IS_CLEAR(ADC1->ISR,0)); // wait ADC ready flag
   SET_BIT(ADC1->CR,2);  //start conversion
	 //SET_BIT(ADC1->ISR , 0 ) ; // clear the ready flag
}

#if(POLLING == 1)
void ADC_GetConversionState(u8 *convStateP )
{
	*convStateP = (ADC1->ISR) & (1<<2);  // get state of ADC EOF flag
}
#endif

u8 ADC_ReadData(u16* convertedData)
{
  while(BIT_IS_CLEAR(ADC1->ISR,2)){}
	if(GET_BIT(ADC1->ISR,3) == 1)
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

