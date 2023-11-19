
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include"../../../OTHERS/std_types.h"
#include"../../../OTHERS/common_macros.h"
#include"../../../MCAL/GPIO/INCLUDES/gpio.h"
#include"../../../MCAL/PWM/includes/PWM.h"

/////////////////////////////////////////////////////channels and timers configurations ////////////////////////////////////////////////////////////////////////////////
// Pins and ports configurations for H-bridge
#define H_BRIDGE_INPUT1_PORT       GPIO_PORTA_ID
#define H_BRIDGE_INPUT1_PIN_HIGH   GPIO_PIN01_ID
#define H_BRIDGE_INPUT1_PIN_LOW    GPIO_PIN02_ID

#define H_BRIDGE_INPUT2_PORT       GPIO_PORTA_ID
#define H_BRIDGE_INPUT2_PIN_HIGH   GPIO_PIN03_ID
#define H_BRIDGE_INPUT2_PIN_LOW    GPIO_PIN04_ID

// selection of channel and timer IDs for PWM init
#define DCMOTOR_SELECT_TIMER          TIM_2
#define DCMOTOR_SELECT_CHANNEL        CHANNEL_1

// macro to drive dutycycle to zero
#define DCMOTOR_STOP                   0


/*motor states at the beginning and during run time*/
typedef enum
{
	DcMotor_stop,DcMotor_ACW,DcMotor_CW
}DcMotor_State;

/////////////////////////////////////////////////////functions prototypes////////////////////////////////////////////////////////////////////////////////
/*
pins and ports setting
*/
void DCmotor_Init(PWM_enu_TIMx_t timer_num,PWM_enu_Channelx_t chan_num);
/*
setting DCmotor to move forward
*/
void DCmotor_frontMove(u8 dutyCycle);
/*
setting DCmotor to move backward
*/
void DCmotor_backMove(u8 dutyCycle);
/*
setting DCmotor to move right
*/
void DCmotor_rightMove(u8 dutyCycle);
/*
setting DCmotor to move left
*/
void DCmotor_leftMove(u8 dutyCycle);
/*
stop the DCmotor
*/
void DCmotor_stop(void);

#endif /* DC_MOTOR_H_ */
