#ifndef PWM_H_
#define PWM_H_


// General purpose Timers Indexes
typedef enum
{
	TIM_2,
	TIM_3,
	TIM_4,
	TIM_MAX
}PWM_enu_TIMx_t;


// Timer Channels
typedef enum
{
	CHANNEL_1,
	CHANNEL_2,
	CHANNEL_3,
	CHANNEL_4,
	CHANNEL_MAX
}PWM_enu_Channelx_t;


// Status Codes
typedef enum
{
  PWM_OKAY,
	PWM_TIM_INDEX_ERROR,
	PWM_CHANNEL_ERROR,
	PWM_DUTY_ERROR
}PWM_enu_Error_t;


/*
  NAME         : PWM_enu_Init
	DESCRIPTION  : Initilize PWM channel with specific Timer
	ARGS         : PWM_enu_TIMx_t         ---> TIMER THAT GENETRATES PWM
	               PWM_enu_Channelx_t     ---> CHANNEL FROM 1 TO 4 
	RETURN       : PWM_OKAY               In case of success operation,
	               PWM_TIM_INDEX_ERROR    In case of TIMx error number,
								 PWM_CHANNEL_ERROR      In case of Channelx error number,
*/
PWM_enu_Error_t PWM_enu_Init        (PWM_enu_TIMx_t,PWM_enu_Channelx_t);

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
PWM_enu_Error_t PWM_enu_SetDutyCycle(PWM_enu_TIMx_t,PWM_enu_Channelx_t,u8  Copy_DutyCycle);


#endif





