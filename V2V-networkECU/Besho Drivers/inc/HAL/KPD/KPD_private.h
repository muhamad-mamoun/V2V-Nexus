/*
 * KPD_private.h
 *
 *  Created on: Sep 2, 2022
 *      Author: M-TECH
 */

#ifndef HAL_KPD_KPD_PRIVATE_H_
#define HAL_KPD_KPD_PRIVATE_H_



/************************************************************************************************/
/*                                       KPD connections                                        */
/************************************************************************************************/

/*Keypad rows and columns sizes*/
#define HKPD_ROWS     (4)
#define HKPD_COLS     (3)

/*Keypad DIO Port*/
#define HKPD_PORT     (GPIOA)

/*Keypad DIO rows pins*/
#define HKPD_ROW_0    (PIN8)
#define HKPD_ROW_1    (PIN9)
#define HKPD_ROW_2    (PIN10)
#define HKPD_ROW_3    (PIN11)

/*Keypad DIO columns pins*/
#define HKPD_COL_0    (PIN12)
#define HKPD_COL_1    (PIN13)
#define HKPD_COL_2    (PIN14)





#endif /* HAL_KPD_KPD_PRIVATE_H_ */
