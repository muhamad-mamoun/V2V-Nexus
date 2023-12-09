/*
 * PB_program.c
 *
 *  Created on: Aug 24, 2022
 *      Author: Asmaa Hashim
 */

#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/LIB/STD_TYPES.h"


#include "../Inc/MCAL/DIO/DIO_interface.h"

#include "../Inc/HAL/PB/PB_Interface.h"


void HPB_init( tPBs  PB ,  PB_states  initi_state )
{
	MGPIO_voidSetPinDirection(PB_config[PB].port  , PB_config[PB].pin  , INPUT_FLOATING);

	PB_config[PB].state = initi_state;

}


void HPB_Update(void)
{
	tPBs current_PB = PB_1;
	while(current_PB < MAX_NUM_PB)
	{
		PB_config[current_PB].samples[0] = PB_config[current_PB].samples[1];
		PB_config[current_PB].samples[1] = MGPIO_u8GetPinValue(PB_config[current_PB].port  , PB_config[current_PB].pin );

		switch(PB_config[current_PB].state)
		{
			case Released :

				if(PB_config[current_PB].samples[0] == PRESED_VOLTAGE &&
				   PB_config[current_PB].samples[1] == PRESED_VOLTAGE )
				{
					PB_config[current_PB].state = Pre_pressed;
				}

				break;

/*========================================================================================================================*/

			case Pre_pressed :
						if( PB_config[current_PB].samples[1] == PRESED_VOLTAGE )
						{
							PB_config[current_PB].state = Pressed;
						}
						break;

/*========================================================================================================================*/

			case Pressed :
								if( PB_config[current_PB].samples[0] == RELEASED_VOLTAGE &&
									PB_config[current_PB].samples[1] == RELEASED_VOLTAGE )
								{
									PB_config[current_PB].state = Pre_Released;
								}
								break;

/*========================================================================================================================*/

			case Pre_Released :
									if( PB_config[current_PB].samples[1] == RELEASED_VOLTAGE )
									{
										PB_config[current_PB].state = Released;
									}
									break;

			default :               break ;

		}

		current_PB++;
	}



}

PB_states HPB_get_state(tPBs  PB)
{
	return (PB_config[PB].state) ;
}
