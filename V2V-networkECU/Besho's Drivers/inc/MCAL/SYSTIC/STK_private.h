/*
 * STK_private.h
 *
 *  Created on: january 25, 2023
 *      Author: beshoy
 */

#ifndef MCAL_STK_STK_PRIVATE_H_
#define MCAL_STK_STK_PRIVATE_H_

#include "../Inc/LIB/STD_TYPES.h"

#define MSTK ((volatile STK_t *) 0xE000E010)

typedef struct
{
// volatile not used here because it used previous
	 u32 CTRL;
	 u32 LOAD;
	 u32 VAL;
	 u32 CALIB;
}STK_t;

#define MSTK_SOURCE_AHB_8   0
#define MSTK_SOURCE_AHB     1

#define MSTK_SINGLE_INTERVAL   0
#define MSTK_PERIOD_INTERVAL   1

#endif /* MCAL_STK_STK_PRIVATE_H_ */
