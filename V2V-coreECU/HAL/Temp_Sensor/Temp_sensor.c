/*
 * Temp_sensor.c
 *
 *  Created on: Dec 9, 2023
 *      Author: Ahmed Dwidar
 */
#include "ADC.h"
#include "Temp_sensor.h"

u16 TEMP_Get(void)
{
	u16 tempRead = 0;

	u16 ADc_readValue = FALSE;
	ADC_StartConversion();
	ADC_ReadData(&ADc_readValue);
	
	//tempRead = (u16)(((u32)(*ADc_readValue)*TEMP_SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*TEMP_SENSOR_MAX_VOLT_VALUE));

	tempRead = ((ADc_readValue * 5.0)/4096);
	__asm("NOP");

	return tempRead;
}

