/*
 * ADC_program.c
 *
 *  Created on: Apr 23, 2023
 *      Author: Loka
 */
#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/MCAL/DIO/DIO_interface.h"

#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/ADC/ADC_private.h"
#include "../Inc/MCAL/ADC/ADC_config.h"
#include "../Inc/MCAL/ADC/ADC_interface.h"

void MADC_ON(void)
{
	// enable adc (ADON bit =1)
	SET_BIT(ADC1->CR2,0);
}
void MADC_OFF(void)
{
	// disable adc (ADON bit =0)
	CLR_BIT(ADC1->CR2,0);
}
void MADC_Init(void)
{
	MRCC_voidPerClock_State(APB2 ,ADC1_PERIPHERAL ,PClock_enable );
	MGPIO_voidSetPinDirection(GPIOA , PIN1  , INPUT_ANALOG);
	//enable cognitions mode( CONT=1)
	SET_BIT(ADC1->CR2,1);

}
u16 MADC_Read(u8 channel)
{
	//ADC1 power on
	MADC_ON();
	MADC_ON();
	//clear all channels
	ADC1->SQR3 &=0XFFFFFFF0;
	//choose the selected channel
	ADC1->SQR3 |=channel;
	//start conversion (SWSTART =1)
	SET_BIT(ADC1->CR2,22);
	//SET_BIT(ADC1->CR2,0);

	//waiting until end conversion flag is up (EOC)
	while(GET_BIT(ADC1->SR,1)==0);
	//Read converted data from adc
	u16 Read=ADC1->DR;

	return Read;



}






