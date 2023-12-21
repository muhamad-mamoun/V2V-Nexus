#include "std_types.h"
#include "common_macros.h"
#include "RCC.h"
#include "gpio.h"
#include "PWM_prv.h"
#include "PWM_cfg.h"
#include "PWM.h"

GPIO_configurationsType PA0  =  {GPIO_PORTA_ID,GPIO_PIN00_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_HIGH_SPEED};
GPIO_configurationsType PB6  =  {GPIO_PORTB_ID,GPIO_PIN06_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_HIGH_SPEED};

/*
  NAME         : PWM_enu_Init
	DESCRIPTION  : Initilize PWM channel with specific Timer
	ARGS         : PWM_enu_TIMx_t         ---> TIMER THAT GENETRATES PWM
	               PWM_enu_Channelx_t     ---> CHANNEL FROM 1 TO 4 
	RETURN       : PWM_OKAY               In case of success operation,
	               PWM_TIM_INDEX_ERROR    In case of TIMx error number,
								 PWM_CHANNEL_ERROR      In case of Channelx error number,
*/
PWM_enu_Error_t PWM_enu_Init(PWM_enu_TIMx_t Copy_enu_TIMx,PWM_enu_Channelx_t Copy_enu_CHx)
{
	
	// Initilize local return variable
	PWM_enu_Error_t loc_enu_ReturnValue = PWM_OKAY;
	// Initilize local array that store Base address of Timers
	u32             Timx_BASE[TIM_MAX]  = {TIM2_BASE,TIM3_BASE,TIM4_BASE};
	
	// check on Timer Index
	if ( Copy_enu_TIMx >= TIM_MAX)
	{
		// Case of Wrong Choice
		loc_enu_ReturnValue = PWM_TIM_INDEX_ERROR;
	}
	// check on Channel Index
	else if (Copy_enu_CHx >= CHANNEL_MAX)
	{
		// Case of Wrong Choice
		loc_enu_ReturnValue = PWM_CHANNEL_ERROR;
	}
	else
	{
		
		// ENABLE the auto-reload preload register
		SET_BIT_BAND(&REG(Timx_BASE[Copy_enu_TIMx],TIMx_CR1),ARPE);
		
		 
		// Edge Aligned Selection
		CLR_BIT_BAND(&REG(Timx_BASE[Copy_enu_TIMx],TIMx_CR1),CMS1);
		CLR_BIT_BAND(&REG(Timx_BASE[Copy_enu_TIMx],TIMx_CR1),CMS0);
		
	  //COUNTER UPCOUNTING
		CLR_BIT_BAND(&REG(Timx_BASE[Copy_enu_TIMx],TIMx_CR1),DIR);
		
		// SET Prescaller
		REG(Timx_BASE[Copy_enu_TIMx],TIMx_PSC) = PRESCALLER-1;
		
		// FREQ 
		REG(Timx_BASE[Copy_enu_TIMx],TIMx_ARR) = ARR_VALUE-1;
		
		// SWITCH ON CHANNELS FROM 1 TO 4.
		switch (Copy_enu_CHx)
		{
			// CASE CHANNEL 1
			case CHANNEL_1:
			{
				// CASE TIM2 
				if ( Copy_enu_TIMx == TIM_2)
				{
					GPIO_configurePin(&PA0);
					// Configure PIN and Send Alternate function corresponding to pin.
					GPIO_setPinFuction(GPIO_PORTA_ID, GPIO_PIN00_ID,GPIO_AF01);
					
				}
				// CASE TIM3 
				else if ( Copy_enu_TIMx == TIM_3)
				{
					// Configure PIN and Send Alternate function corresponding to pin. //PE2 ALSO
					GPIO_setPinFuction(GPIO_PORTB_ID, GPIO_PIN04_ID,GPIO_AF02);
				}
				// CASE TIM4
				else if ( Copy_enu_TIMx == TIM_4)
				{
					GPIO_configurePin(&PB6);
					// Configure PIN and Send Alternate function corresponding to pin.
					GPIO_setPinFuction(GPIO_PORTB_ID, GPIO_PIN06_ID,GPIO_AF02);
				}
				
				// ENABLE OUTPUT PIN FOR CHANNEL 1 
				SET_BIT_BAND(&REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCER),CC1E);
				
				// ENABLE the corresponding preload
				SET_BIT_BAND(&REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCMR1),OC1PE);
				
				// SELECT PWM MODE
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCMR1) &= ~(MASK_MODE<<OC1M); 
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCMR1) |= (PWM_MODE_SELECTED<<OC1M); 
				
				// SET PWM WITH MAX 
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCR1)    = ARR_VALUE;
				break;
			}
			
			// CASE CHANNEL 2
			case CHANNEL_2:
			{
				
				// CASE TIM2 
				if ( Copy_enu_TIMx == TIM_2)
				{
					
				}
				// CASE TIM3 
				else if ( Copy_enu_TIMx == TIM_3)
				{
					// Configure PIN and Send Alternate function corresponding to pin.
					GPIO_setPinFuction(GPIO_PORTC_ID, GPIO_PIN07_ID,GPIO_AF02);
				}
				// CASE TIM4
				else if ( Copy_enu_TIMx == TIM_4)
				{
					// Configure PIN and Send Alternate function corresponding to pin.
					GPIO_setPinFuction(GPIO_PORTB_ID, GPIO_PIN07_ID,GPIO_AF02);
				}
			
				// ENABLE OUTPUT PIN FOR CHANNEL 2
				SET_BIT_BAND(&REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCER),CC2E);
				
				// // ENABLE the corresponding preload
				SET_BIT_BAND(&REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCMR1),OC2PE);
				
				// SELECT PWM MODE
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCMR1) &= ~(MASK_MODE<<OC2M); 
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCMR1) |= (PWM_MODE_SELECTED<<OC2M); 
				
				// SET PWM WITH MAX 
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCR2)    = ARR_VALUE;
				break;
			}
			
			// CASE CHANNEL 3
			case CHANNEL_3:
			{
				// CASE TIM2 
				if ( Copy_enu_TIMx == TIM_2)
				{
					//GPIO_configurePin(&PA2);
					// Configure PIN and Send Alternate function corresponding to pin.
					GPIO_setPinFuction(GPIO_PORTA_ID, GPIO_PIN02_ID,GPIO_AF01);
				}
				// CASE TIM3
				else if ( Copy_enu_TIMx == TIM_3)
				{
					// Configure PIN and Send Alternate function corresponding to pin.
					GPIO_setPinFuction(GPIO_PORTC_ID, GPIO_PIN08_ID,GPIO_AF02);
				}
				// CASE TIM4
				else if ( Copy_enu_TIMx == TIM_4)
				{
					// Configure PIN and Send Alternate function corresponding to pin.
					GPIO_setPinFuction(GPIO_PORTD_ID, GPIO_PIN14_ID,GPIO_AF02);
				}
			
				// ENABLE OUTPUT PIN FOR CHANNEL 3
				SET_BIT_BAND(&REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCER),CC3E);
				
				// ENABLE the corresponding preload
				SET_BIT_BAND(&REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCMR2),OC3PE);
				
				// // SELECT PWM MODE
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCMR2) &= ~(MASK_MODE<<OC3M); 
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCMR2) |= (PWM_MODE_SELECTED<<OC3M); 
				
				// SET PWM WITH MAX 
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCR3)    = ARR_VALUE;
				break;
			}
			// CASE CHANNEL 4
			case CHANNEL_4:
			{
				// CASE TIM2 
				if ( Copy_enu_TIMx == TIM_2)
				{
					// Configure PIN and Send Alternate function corresponding to pin.
					GPIO_setPinFuction(GPIO_PORTD_ID, GPIO_PIN06_ID,GPIO_AF01);
				}
				// CASE TIM3
				else if ( Copy_enu_TIMx == TIM_3)
				{
					// Configure PIN and Send Alternate function corresponding to pin.
					GPIO_setPinFuction(GPIO_PORTB_ID, GPIO_PIN01_ID,GPIO_AF02);
				}
				// CASE TIM4
				else if ( Copy_enu_TIMx == TIM_4)
				{
					// Configure PIN and Send Alternate function corresponding to pin.
					GPIO_setPinFuction(GPIO_PORTD_ID, GPIO_PIN15_ID,GPIO_AF02);
				}
			
				// ENABLE OUTPUT PIN FOR CHANNEL 4
			  SET_BIT_BAND(&REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCER),CC4E);
				// ENABLE the corresponding preload
				SET_BIT_BAND(&REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCMR2),OC4PE);
				
				// SELECT PWM MODE
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCMR2) &= ~(MASK_MODE<<OC4M); 
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCMR2) |= (PWM_MODE_SELECTED<<OC4M); 
				
				// SET PWM WITH MAX 
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCR4)    = ARR_VALUE;
				break;
			}
			default:break;
		}
		
		//  initialize all the registers
		SET_BIT(REG(Timx_BASE[Copy_enu_TIMx],TIMx_EGR),UG);
		// TIMER ENABLE
		SET_BIT(REG(Timx_BASE[Copy_enu_TIMx],TIMx_CR1),CEN);
	}
	
	// RETUTN STATUS CODE
	return loc_enu_ReturnValue;
}

/*
  NAME         : PWM_enu_SetDutyCycle
	DESCRIPTION  : Set DutyCycle On channel with specific Timer
	ARGS         : PWM_enu_TIMx_t         ---> TIMER THAT GENETRATES PWM
	               PWM_enu_Channelx_t     ---> CHANNEL FROM 1 TO 4 
                 u8                     ---> DUTY CYCLE FROM 0 TO 100
	RETURN       : PWM_OKAY               In case of success operation,
	               PWM_TIM_INDEX_ERROR    In case of TIMx error number,
								 PWM_CHANNEL_ERROR      In case of Channelx error number,
                 PWM_DUTY_ERROR         In case of wrong Duty Cycle
*/
PWM_enu_Error_t PWM_enu_SetDutyCycle(PWM_enu_TIMx_t Copy_enu_TIMx,PWM_enu_Channelx_t Copy_enu_CHx,u8  Copy_DutyCycle)
{
	
	// Initilize local return variable
	PWM_enu_Error_t loc_enu_ReturnValue = PWM_OKAY;
	
	// Initilize local array that store Base address of Timers
	u32             Timx_BASE[TIM_MAX]  = {TIM2_BASE,TIM3_BASE,TIM4_BASE};
	
	// check on Timer Index
	if ( Copy_enu_TIMx >= TIM_MAX)
	{
		// Case of Wrong Choice
		loc_enu_ReturnValue = PWM_TIM_INDEX_ERROR;
	}
	// check on Channel Index
	else if (Copy_enu_CHx >= CHANNEL_MAX)
	{
		// Case of Wrong Choice
		loc_enu_ReturnValue = PWM_CHANNEL_ERROR;
	}
	// check on DUTY CYCLE
	else if (Copy_DutyCycle > DUTY_MAX)
	{
		// Case of Wrong Choice
		loc_enu_ReturnValue = PWM_DUTY_ERROR;
	}
	else
	{
		
		// Switch On Channel
		switch (Copy_enu_CHx)
		{
			
			// CASE CHANNEL 1
			case CHANNEL_1:
			{
				// SET CCRx With Duty Cycle % of ARR VALUE
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCR1) = (ARR_VALUE/DUTY_MAX)*Copy_DutyCycle;
				break;
			}
			// CASE CHANNEL 2
			case CHANNEL_2:
			{
				// SET CCRx With Duty Cycle % of ARR VALUE
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCR2) = (ARR_VALUE/DUTY_MAX)*Copy_DutyCycle;
				break;
			}
			// CASE CHANNEL 3
			case CHANNEL_3:
			{
				// SET CCRx With Duty Cycle % of ARR VALUE
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCR3) = (ARR_VALUE/DUTY_MAX)*Copy_DutyCycle;
				break;
			}
			// CASE CHANNEL 4
			case CHANNEL_4:
			{
				// SET CCRx With Duty Cycle % of ARR VALUE
				REG(Timx_BASE[Copy_enu_TIMx],TIMx_CCR4) = (ARR_VALUE/DUTY_MAX)*Copy_DutyCycle;
				break;
			}
			default:break;
		}
		
		//  initialize all the registers
		SET_BIT(REG(Timx_BASE[Copy_enu_TIMx],TIMx_EGR),UG);
	}
	
	// RETURN STATUS CODE
	return loc_enu_ReturnValue;
}




