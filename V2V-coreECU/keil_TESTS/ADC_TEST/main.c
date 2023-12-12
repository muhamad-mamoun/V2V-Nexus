#include "common_macros.h"
#include "std_types.h"
#include "RCC.h"
#include "gpio.h"
#include "ADC.h"

int main()
{

	u16 data;
	ADC_config ADC_initialization = {voltageRedEnable,singleConv,rightAllign,bit_10,clksycles_601AndHAlf};

	ADC_Init(&ADC_initialization);
	while (1)
	{

			ADC_StartConversion();
		  ADC_ReadData(&data);
		//  __asm("NOP");
	}

	return 0;
}
