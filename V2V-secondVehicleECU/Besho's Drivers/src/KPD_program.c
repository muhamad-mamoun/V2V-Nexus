/*
 * KPD_program.c
 *
 *  Created on: Sep 2, 2022
 *      Author: M-TECH
 */



/************************************************************************************************/
/*                                           Includes                                           */
/************************************************************************************************/
#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"

#include "../Inc/HAL/KPD/KPD_interface.h"
#include "../Inc/HAL/KPD/KPD_private.h"
#include "../Inc/HAL/KPD/KPD_config.h"


#include "../Inc/MCAL/DIO/DIO_interface.h"
#include "../Inc/MCAL/DIO/DIO_private.h"
#include "../Inc/MCAL/DIO/DIO_config.h"



/************************************************************************************************/
/*                                    Important variables                                       */
/************************************************************************************************/

/*Global 2-D array used to draw the keypad map*/
u8 gu8_kpdMap[HKPD_ROWS][HKPD_COLS] = {
											{'1', '2', '3'},
											{'4', '5', '6'},
											{'7', '8', '9'},
											{'*', '0', '#'}
										};

/************************************************************************************************/
/*                                    Functions' definitions                                    */
/************************************************************************************************/

void hkpd_init(void)
{
	/*Setting rows pins as input pull-up*/
	MGPIO_voidSetPinDirection(HKPD_PORT, (HKPD_ROW_0 | HKPD_ROW_1 | HKPD_ROW_2 | HKPD_ROW_3), INPUT_PULL_UP_DOWN);

	/*Setting columns pins as output*/
	MGPIO_voidSetPinDirection(HKPD_PORT, (HKPD_COL_0 | HKPD_COL_1 | HKPD_COL_2), OUTPUT_SPEED_10MHZ_PP);

	/*Setting columns pins to high*/
	MGPIO_voidSetPinValue(HKPD_PORT, (HKPD_COL_0 | HKPD_COL_1 | HKPD_COL_2), GPIO_HIGH);

	/*Return from this function*/
	return;
}

void hkpd_getPressedKey(u8* pu8_key)
{
	/*Local variable used in rows looping operations*/
	u8 au8_rowIterator = 0;

	/*Local variable used in columns looping operations*/
	u8 au8_colIterator = 0;

	/*Local variable used to report a pressed key*/
	u8 au8_keyFlag = 0;

	/*Resetting the key value holder variable*/
	*pu8_key = 0;

	/*Looping over KPD columns*/
	for(au8_colIterator = 0; au8_colIterator < HKPD_COLS; au8_colIterator++)
	{
		/*Setting specific column pin to LOW*/
		MGPIO_voidSetPinValue(HKPD_PORT, (HKPD_COL_0 << au8_colIterator), GPIO_LOW);

		/*Looping over KPD rows*/
		for(au8_rowIterator = 0; au8_rowIterator < HKPD_ROWS; au8_rowIterator++)
		{
			/*Checking if there's any pressed button*/
			if( MGPIO_u8GetPinValue(HKPD_PORT, (HKPD_ROW_0 << au8_rowIterator)) == GPIO_LOW )
			{
				/*Report the pressed pin*/
				*pu8_key = gu8_kpdMap[au8_rowIterator][au8_colIterator];

				/*Increment the pressed key flag*/
				au8_keyFlag++;

				/*Break from rows loop*/
				break;
			}
			else
			{
				/*Do nothing*/
			}
		}

		/*Setting specific column pin to HIGH*/
		MGPIO_voidSetPinValue(HKPD_PORT, (HKPD_COL_0 << au8_colIterator), GPIO_HIGH);

		/*Checking if the key flag is raised or not*/
		if(au8_keyFlag)
		{
			/*Break from columns loop*/
			break;
		}
		else
		{
			/*Do nothing*/
		}
	}

	/*Return from this function*/
	return;
}

