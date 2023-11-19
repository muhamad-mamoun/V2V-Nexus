
#include"../INCLUDES/motor.h"


DcMotor_State state;
/*
initialize DCmotor by passing channel and timer IDs to the PWM init
*/
void DCmotor_Init(PWM_enu_TIMx_t timer_num,PWM_enu_Channelx_t chan_num)
{
	PWM_enu_Init(timer_num,chan_num);
}

void DCmotor_frontMove(u8 dutyCycle)
{
	GPIO_writePin(H_BRIDGE_INPUT1_PORT,H_BRIDGE_INPUT1_PIN_HIGH,GPIO_HIGH_PIN);
	GPIO_writePin(H_BRIDGE_INPUT1_PORT,H_BRIDGE_INPUT1_PIN_LOW,GPIO_LOW_PIN);

	GPIO_writePin(H_BRIDGE_INPUT2_PORT,H_BRIDGE_INPUT2_PIN_HIGH,GPIO_HIGH_PIN);
	GPIO_writePin(H_BRIDGE_INPUT2_PORT,H_BRIDGE_INPUT2_PIN_LOW,GPIO_LOW_PIN);

	PWM_enu_SetDutyCycle(DCMOTOR_SELECT_TIMER,DCMOTOR_SELECT_CHANNEL,dutyCycle);
}
void DCmotor_backMove(u8 dutyCycle)
{
	GPIO_writePin(H_BRIDGE_INPUT1_PORT,H_BRIDGE_INPUT1_PIN_HIGH,GPIO_LOW_PIN);
	GPIO_writePin(H_BRIDGE_INPUT1_PORT,H_BRIDGE_INPUT1_PIN_LOW,GPIO_HIGH_PIN);

	GPIO_writePin(H_BRIDGE_INPUT2_PORT,H_BRIDGE_INPUT2_PIN_HIGH,GPIO_LOW_PIN);
	GPIO_writePin(H_BRIDGE_INPUT2_PORT,H_BRIDGE_INPUT2_PIN_LOW,GPIO_HIGH_PIN);

	PWM_enu_SetDutyCycle(DCMOTOR_SELECT_TIMER,DCMOTOR_SELECT_CHANNEL,dutyCycle);
}

// input1 right motors , input2 left motors
void DCmotor_rightMove(u8 dutyCycle)
{
	GPIO_writePin(H_BRIDGE_INPUT1_PORT,H_BRIDGE_INPUT1_PIN_HIGH,GPIO_HIGH_PIN);
	GPIO_writePin(H_BRIDGE_INPUT1_PORT,H_BRIDGE_INPUT1_PIN_LOW,GPIO_LOW_PIN);

	GPIO_writePin(H_BRIDGE_INPUT2_PORT,H_BRIDGE_INPUT2_PIN_HIGH,GPIO_LOW_PIN);
	GPIO_writePin(H_BRIDGE_INPUT2_PORT,H_BRIDGE_INPUT2_PIN_LOW,GPIO_LOW_PIN);

	PWM_enu_SetDutyCycle(DCMOTOR_SELECT_TIMER,DCMOTOR_SELECT_CHANNEL,dutyCycle);
}
void DCmotor_leftMove(u8 dutyCycle)
{
	GPIO_writePin(H_BRIDGE_INPUT1_PORT,H_BRIDGE_INPUT1_PIN_HIGH,GPIO_LOW_PIN);
	GPIO_writePin(H_BRIDGE_INPUT1_PORT,H_BRIDGE_INPUT1_PIN_LOW,GPIO_LOW_PIN);

	GPIO_writePin(H_BRIDGE_INPUT2_PORT,H_BRIDGE_INPUT2_PIN_HIGH,GPIO_HIGH_PIN);
	GPIO_writePin(H_BRIDGE_INPUT2_PORT,H_BRIDGE_INPUT2_PIN_LOW,GPIO_LOW_PIN);

	PWM_enu_SetDutyCycle(DCMOTOR_SELECT_TIMER,DCMOTOR_SELECT_CHANNEL,dutyCycle);
}
/*
stop the DCmotor by passing dutycycle = 0
*/
void DCmotor_stop(void)
{
	PWM_enu_SetDutyCycle(DCMOTOR_SELECT_TIMER,DCMOTOR_SELECT_CHANNEL,DCMOTOR_STOP);
}
