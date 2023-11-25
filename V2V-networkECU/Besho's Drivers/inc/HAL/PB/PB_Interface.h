/*
 * PB_Interface.h
 *
 *  Created on: Aug 24, 2022
 *      Author: Asmaa Hashim
 */

#ifndef HAL_PUSH_BUTTON_PB_INTERFACE_H_
#define HAL_PUSH_BUTTON_PB_INTERFACE_H_

// this means PB pin Pull down
#define PRESED_VOLTAGE   (1)

#define RELEASED_VOLTAGE (0)



#define MAX_NUM_PB   7
typedef enum
{
	Pressed,
	Pre_pressed,
	Pre_Released,
	Released
}PB_states;

typedef enum
{
	PB_1,
	PB_2,
	PB_3,
	PB_4,
	PB_5,
	PB_6,
	PB_7
}tPBs;

typedef struct
{
	u8 port;
	u8 pin;
	PB_states state ;
	u8 samples[2];
}PB_info;

extern PB_info PB_config[MAX_NUM_PB];

void HPB_init( tPBs  PB ,  PB_states  initi_state );

void HPB_Update(void);

PB_states HPB_get_state(tPBs  PB);



#endif /* HAL_PUSH_BUTTON_PB_INTERFACE_H_ */
