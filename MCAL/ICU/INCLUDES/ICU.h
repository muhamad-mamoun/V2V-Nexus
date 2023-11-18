#ifndef ICU_H_
#define ICU_H_
#include "std_types.h"
#include "bit_math.h"

#define Timer2	0
#define Timer3	1
#define Timer4	2

#define	CH1		0
#define	CH2		1
#define	CH3		2
#define	CH4		3


#define Falling_Edge	0
#define Rising_Edge		1
#define Any_Egdy		2

void ICU_voidInitTimer(u8 Copy_u8Channel, u8 Copy_u8Timer);
void ICU_voidSetSensingEdge(u8 Copy_u8Channel, u8 Copy_u8Timer, u8 Copy_u8SignalSense);
void ICU_voidSetCountTime(u8 Copy_u8Timer, u32 Copy_u32CountTime);
void ICU_voidEnableTimer(u8 Copy_u8Timer);
void ICU_voidGetICU_Count(u8 Copy_u8Channel, u8 Copy_u8Timer, u32* Ptr_ICU_Count);
void ICU_voidGetTimerOvStatus(u8 Copy_u8Timer, u8* Ptr_OvStauts);
void ICU_voidGetTimerIcuStatus(u8 Copy_u8Channel, u8 Copy_u8Timer, u8* Ptr_IcuStauts);
void ICU_voidSetArrTime(u8 Copy_u8Timer, u32 Copy_u32ArrTime);



#endif


