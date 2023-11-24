#include "std_types.h"
#include "common_macros.h"

#include "gpio.h"
#include "US.h"
#include "ICU.h"

void US_voidInit(void)
{
	GPIO_configurationsType US_TrigPin; 
	US_TrigPin.portID = GPIO_PORTC_ID;                      /*      *******                                                 */
	US_TrigPin.pinID = GPIO_PIN08_ID;                       /*      *******            configure as #define in US.h File    */
	US_TrigPin.pinMode = GPIO_OUTPUT_PUSH_PULL_MODE;        /*      *******                                                 */
	US_TrigPin.pinSpeed = GPIO_MEDIUM_SPEED;                /*      *******                                               	*/
	GPIO_configurePin(&US_TrigPin);	

	GPIO_configurationsType US_EchoPin;                      /*      *******            configure as #define in US.h File    */
	US_EchoPin.portID = GPIO_PORTC_ID;						 /*      *******                                                 */			
	US_EchoPin.pinID = GPIO_PIN06_ID;                        /*      *******                                               	*/
	US_EchoPin.pinMode = GPIO_ALTERNATE_PUSH_PULL_MODE;                 
	US_EchoPin.pinSpeed = GPIO_MEDIUM_SPEED;
	GPIO_configurePin(&US_EchoPin);
	GPIO_setPinFuction(GPIO_PORTC_ID, GPIO_PIN06_ID, GPIO_AF02);
	ICU_voidInitTimer(CH1, Timer3);
}
void US_voidGetUSSensorDistance(u16 *Ptr_u16DistanceCM)
{
	u8 Local_OvStauts = 0;
	u8 flag = 0;
	u32 Local_u32TimeCount=0;
	
	
	GPIO_writePin(GPIO_PORTC_ID, GPIO_PIN08_ID, GPIO_LOW_PIN);
	ICU_voidSetArrTime(Timer3, 2);
	ICU_voidClrTimerOvFlag(Timer3);
	ICU_voidEnableTimer(Timer3);
	ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
	while(Local_OvStauts == 0)
	{
		ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
	}
	Local_OvStauts = 0;	
	
	GPIO_writePin(GPIO_PORTC_ID, GPIO_PIN08_ID, GPIO_HIGH_PIN);
	ICU_voidSetArrTime(Timer3, 12);
	ICU_voidClrTimerOvFlag(Timer3);
	ICU_voidEnableTimer(Timer3);
	ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
	while(Local_OvStauts == 0)
	{
		ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
	}
	Local_OvStauts = 0;
	GPIO_writePin(GPIO_PORTC_ID, GPIO_PIN08_ID, GPIO_LOW_PIN);
	ICU_voidSetArrTime(Timer3, 60000);
	ICU_voidSetCountTime(Timer3, 0);
	
	ICU_voidClrTimerOvFlag(Timer3);
	ICU_voidClrTimerIcuFlag(CH1, Timer3);
	
	ICU_voidEnableTimer(Timer3);
	ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
	while(Local_OvStauts == 0)
	{
			ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
			ICU_voidGetICU_Count(CH1, Timer3, &Local_u32TimeCount);
			if(Local_u32TimeCount != 0)
			{
					*Ptr_u16DistanceCM = Local_u32TimeCount /58;
					ICU_voidClrTimerIcuFlag(CH1, Timer3);
					flag =1;
			}
			if(flag == 0)
			{
				*Ptr_u16DistanceCM = 0xFEFE;
			}
	}
	ICU_voidClrTimerOvFlag(Timer3);
}
void US_voidSetTrigger(void)
{
	u8 Local_OvStauts = 0;
	GPIO_writePin(GPIO_PORTC_ID, GPIO_PIN08_ID, GPIO_LOW_PIN);
	ICU_voidDisableTimer(Timer3);
	ICU_voidSetCountTime(Timer3, 0);
	ICU_voidSetArrTime(Timer3, 2);
	ICU_voidClrTimerOvFlag(Timer3);
	ICU_voidEnableTimer(Timer3);
	ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
	while(Local_OvStauts == 0)
	{
		ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
	}
	Local_OvStauts = 0;	
	GPIO_writePin(GPIO_PORTC_ID, GPIO_PIN08_ID, GPIO_HIGH_PIN);
	ICU_voidSetArrTime(Timer3, 12);
	ICU_voidClrTimerOvFlag(Timer3);
	ICU_voidEnableTimer(Timer3);
	ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
	while(Local_OvStauts == 0)
	{
		ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
	}
	Local_OvStauts = 0;
	GPIO_writePin(GPIO_PORTC_ID, GPIO_PIN08_ID, GPIO_LOW_PIN);
}
void US_voidSetICUTime(void)
{
	ICU_voidSetArrTime(Timer3, 40000);
	ICU_voidSetCountTime(Timer3, 0);
	ICU_voidClrTimerOvFlag(Timer3);
	ICU_voidClrTimerIcuFlag(CH1, Timer3);
	ICU_voidEnableTimer(Timer3);
}
void US_voidGetTimeStatus(u8* Ptr_u8Flag)
{
	ICU_voidGetTimerOvStatus(Timer3, Ptr_u8Flag);
}
void US_voidGetICU_Distance(u16 *Ptr_u16DistanceCM)
{
	u32 Local_u32TimeCount;
	ICU_voidGetICU_Count(CH1, Timer3, &Local_u32TimeCount);
	if(Local_u32TimeCount != 0)
	{
		*Ptr_u16DistanceCM = Local_u32TimeCount / 58;
	}
	else
	{
		*Ptr_u16DistanceCM =0xFEFE;
	}
	ICU_voidClrTimerOvFlag(Timer3);
}
/**************************************/
void US_voidGetUSSensorDistanceAsync(u16 *Ptr_u16DistanceCM)
{
	static u8 US_flag = 0;
	static u8 US_TimerStatus = 0;

	if(US_flag == 0)
	{
		US_voidSetTrigger();
		US_voidSetICUTime();
		US_flag = 1;
	}
	if(US_flag == 1)
	{
		US_voidGetTimeStatus(&US_TimerStatus);
		if(US_TimerStatus == 1)
		{
			US_voidGetICU_Distance(Ptr_u16DistanceCM);
			US_flag = 0;
		}
		else
		{
			*Ptr_u16DistanceCM =0xDDDD;
		}
	}
}
/************************************************/
void US_voidGetDistancePolling(u16 *Ptr_u16DistanceCM)
{
	u8 Local_OvStauts = 0;
	u8 Local_ICUStatus = 0;
	u8 flag = 0;
	u32 Local_u32TimeCount=0;
	GPIO_writePin(GPIO_PORTC_ID, GPIO_PIN08_ID, GPIO_LOW_PIN);
	ICU_voidSetArrTime(Timer3, 2);
	ICU_voidClrTimerOvFlag(Timer3);
	ICU_voidEnableTimer(Timer3);
	ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
	while(Local_OvStauts == 0)
	{
		ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
	}
	Local_OvStauts = 0;	
	
	GPIO_writePin(GPIO_PORTC_ID, GPIO_PIN08_ID, GPIO_HIGH_PIN);
	ICU_voidSetArrTime(Timer3, 12);
	ICU_voidClrTimerOvFlag(Timer3);
	ICU_voidEnableTimer(Timer3);
	ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
	while(Local_OvStauts == 0)
	{
		ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
	}
	Local_OvStauts = 0;
	GPIO_writePin(GPIO_PORTC_ID, GPIO_PIN08_ID, GPIO_LOW_PIN);
	ICU_voidSetArrTime(Timer3, 60000);
	ICU_voidSetCountTime(Timer3, 0);
	
	ICU_voidClrTimerOvFlag(Timer3);
	ICU_voidClrTimerIcuFlag(CH1, Timer3);
	
	ICU_voidEnableTimer(Timer3);
	ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
	while(Local_OvStauts == 0)
	{
			ICU_voidGetTimerOvStatus(Timer3, &Local_OvStauts);
			ICU_voidGetTimerIcuStatus(CH1, Timer3, &Local_ICUStatus);
			if(Local_ICUStatus != 0)
			{
					ICU_voidGetICU_Count(CH1, Timer3, &Local_u32TimeCount);
					*Ptr_u16DistanceCM = Local_u32TimeCount / (u16)58;
					ICU_voidClrTimerIcuFlag(CH1, Timer3);
					flag =1;
			}
			if(flag == 0)
			{
				*Ptr_u16DistanceCM = 0xFEFE;
			}
	}
	ICU_voidClrTimerOvFlag(Timer3);
}
void US_voidGetTimeICUStatus(u8* Ptr_u8Flag)
{
	ICU_voidGetTimerIcuStatus(CH1, Timer3, Ptr_u8Flag);
}
void US_voidGetUSSensorDistanceAsyncTask(u16 *Ptr_u16DistanceCM)
{
	static u8 US_flag = 0;
	static u8 US_TimerStatus = 0;
	static u8 US_TimerICUStatus = 0;

	if(US_flag == 0)
	{
		US_voidSetTrigger();
		US_voidSetICUTime();
		US_flag = 1;
	}
	if(US_flag == 1)
	{
		US_voidGetTimeStatus(&US_TimerStatus);
		US_voidGetTimeICUStatus(&US_TimerICUStatus);
		if(US_TimerStatus == 0)
		{
			if(US_TimerICUStatus == 1)
			{
				US_voidGetICU_Distance(Ptr_u16DistanceCM);
				US_flag = 0;
				ICU_voidClrTimerIcuFlag(CH1, Timer3);
			}
		}
		else
		{
			
			if(US_TimerICUStatus == 1)
			{
				US_voidGetICU_Distance(Ptr_u16DistanceCM);
				ICU_voidClrTimerIcuFlag(CH1, Timer3);
			}
			else 
			{
					*Ptr_u16DistanceCM = 0xDDDD;
			}
			US_flag = 0;
			ICU_voidClrTimerOvFlag(Timer3);
		}
	}
}
void US_voidUltraSonicStart(void)
{
	US_voidSetTrigger();
	US_voidSetICUTime();
}
void US_voidGetUSSensorDistanceTask(u16 *Ptr_u16DistanceCM)
{
	static u8 US_TimerStatus = 0;
	static u8 US_TimerICUStatus = 0;
		US_voidGetTimeStatus(&US_TimerStatus);
		US_voidGetTimeICUStatus(&US_TimerICUStatus);
		if(US_TimerStatus == 0)
		{
			if(US_TimerICUStatus == 1)
			{
												/*if Ptr_u16DistanceCM == 0xFEFE data garbage*/

				US_voidGetICU_Distance(Ptr_u16DistanceCM);
				ICU_voidClrTimerIcuFlag(CH1, Timer3);
			}
		}
		else
		{
			if(US_TimerICUStatus == 1)
			{
								/*if Ptr_u16DistanceCM == 0xFEFE data garbage*/
				US_voidGetICU_Distance(Ptr_u16DistanceCM);
				ICU_voidClrTimerIcuFlag(CH1, Timer3);
			}
			else 
			{
				/*US No response*/
					*Ptr_u16DistanceCM = 0xDDDD;
			}
			ICU_voidClrTimerOvFlag(Timer3);
		}
	
}
