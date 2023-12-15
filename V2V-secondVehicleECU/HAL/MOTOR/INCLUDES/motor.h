#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_



/////////////////////////////////////////////////////channels and timers configurations ////////////////////////////////////////////////////////////////////////////////
// Pins and ports configurations for H-bridge
#define H_BRIDGE_INPUT1_PORT         GPIOB_driver
#define H_BRIDGE_INPUT1_PIN    		 PIN0
#define H_BRIDGE_INPUT2_PIN    		 PIN1

#define H_BRIDGE_INPUT2_PORT         GPIOA_driver
#define H_BRIDGE_INPUT3_PIN   		 PIN0
#define H_BRIDGE_INPUT4_PIN    		 PIN1

// selection of channel and timer IDs for PWM init
#define DCMOTOR_SELECT_TIMER         TIMER4
#define DCMOTOR_SELECT_CHANNEL       CH1

// macro to drive dutycycle to zero
#define DCMOTOR_STOP                 0

#define DCMOTOR_MAX_SPEED              50000


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

void MOTOR_setMotor(u8 a_direction, u8 a_speed);

// /*
// setting DCmotor to move forward
// */
// void DCmotor_frontMove(u8 dutyCycle);
// /*
// setting DCmotor to move backward
// */
// void DCmotor_backMove(u8 dutyCycle);
// /*
// setting DCmotor to move right
// */
// void DCmotor_rightMove(u8 dutyCycle);
// /*
// setting DCmotor to move left
// */
// void DCmotor_leftMove(u8 dutyCycle);
// /*
// stop the DCmotor
// */
// void DCmotor_stop(void);

#endif /* DC_MOTOR_H_ */
// void DCmotor1_(void);
// void DCmotor2_(void);
// void DCmotor3_(void);
// void DCmotor4_(void);


