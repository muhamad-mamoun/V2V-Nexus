
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "../../../OTHERS/std_types.h"
#include "../../../OTHERS/common_macros.h"
#include "../../../MCAL/GPIO/INCLUDES/gpio.h"
#include "../../../MCAL/PWM/includes/PWM.h"

/////////////////////////////////////////////////////channels and timers configurations ////////////////////////////////////////////////////////////////////////////////
// Pins and ports configurations for H-bridge
#define H_BRIDGE_INPUT1_PORT       GPIO_PORTA_ID
#define H_BRIDGE_INPUT1_PIN_HIGH   GPIO_PIN13_ID
#define H_BRIDGE_INPUT1_PIN_LOW    GPIO_PIN14_ID

#define H_BRIDGE_INPUT2_PORT       GPIO_PORTC_ID
#define H_BRIDGE_INPUT2_PIN_HIGH   GPIO_PIN13_ID
#define H_BRIDGE_INPUT2_PIN_LOW    GPIO_PIN14_ID

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



//GPIO_configurationsType input1EnablePin = {H_BRIDGE_BACK_ENABLE_PORT,H_BRIDGE1_BACK_ENABLE_PIN,GPIO_OUTPUT_OPEN_DRAIN_MODE,GPIO_LOW_SPEED};
//GPIO_configurationsType input2EnablePin = {H_BRIDGE_FRONT_ENABLE_PORT,H_BRIDGE_FRONT_ENABLE_PIN,GPIO_OUTPUT_OPEN_DRAIN_MODE,GPIO_LOW_SPEED};

/////////////////////////////////////////////////////functions prototypes////////////////////////////////////////////////////////////////////////////////
/*
pins and ports setting
*/
void DCmotor_Init(void);
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
