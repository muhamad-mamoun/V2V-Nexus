

#include"../Inc/LIB/STD_TYPES.h"
#include"../Inc/LIB/BIT_MATH.h"

/*********************************************************************************

**********************************************************************************/

#include"../Inc/MCAL/NVIC/NVIC_private.h"
#include"../Inc/MCAL/NVIC/NVIC_interface.h"
#include"../Inc/MCAL/NVIC/NVIC_config.h"

void MNVIC_voidInit(void)
{
	
	SCB_AIRCR = MNVIC_GROUB_SUB_DISTRIBUTION;
}

void MNVIC_voidEnableInterrupt(NVIC_Per_Position Copy_IntNumber)
{
	if(Copy_IntNumber <= 31 )
	{
		NVIC_ISER0 = (1 << Copy_IntNumber);

	}
	else if(Copy_IntNumber <=59 )
	{

		Copy_IntNumber -=32;

		NVIC_ISER1 = (1 << Copy_IntNumber);

	}
	else
	{
		/* return error */
	}


}

void MNVIC_voidDisableInterrupt(NVIC_Per_Position Copy_IntNumber)
{
	if(Copy_IntNumber <= 31 )
	{
		NVIC_ICER0 = (1 << Copy_IntNumber);

	}
	else if(Copy_IntNumber <=59 )
	{

		Copy_IntNumber -=32;

		NVIC_ICER1 = (1 << Copy_IntNumber);

	}
	else
	{
		/* return error */
	}


}

void MNVIC_voidSetPendingFlag(NVIC_Per_Position Copy_IntNumber)
{
	if(Copy_IntNumber <= 31 )
	{
		NVIC_ISPR0 = (1 << Copy_IntNumber);

	}
	else if(Copy_IntNumber <=59 )
	{

		Copy_IntNumber -=32;

		NVIC_ISPR1 = (1 << Copy_IntNumber);

	}
	else
	{
		/* return error */
	}


}


void MNVIC_voidClearPendingFlag(NVIC_Per_Position Copy_IntNumber)
{
	if(Copy_IntNumber <= 31 )
	{
		NVIC_ICPR0 = (1 << Copy_IntNumber);

	}
	else if(Copy_IntNumber <=59 )
	{

		Copy_IntNumber -=32;

		NVIC_ICPR1 = (1 << Copy_IntNumber);

	}
	else
	{
		/* return error */
	}


}

u8 MNVIC_u8GetActiveFlag(NVIC_Per_Position Copy_IntNumber)
{

	u8 Local_u8Result;

	if(Copy_IntNumber <= 31 )
	{
		Local_u8Result = GET_BIT(NVIC_IABR0 , Copy_IntNumber );
	}
	else if(Copy_IntNumber <=59 )
	{

		Copy_IntNumber -=32;

		Local_u8Result = GET_BIT(NVIC_IABR1 , Copy_IntNumber );

	}
	else
	{
		/* return error */
	}
return  Local_u8Result ;

}


void MNVIC_voidSetPriority_2(NVIC_Per_Position Copy_IntNumber ,u8 copy_u8GroupPriority ,u8 copy_u8SupPriority , u32 copy_u32GroupSubDiv  )
{
	/* core      peripheral */
	u8 Local_u8GroubFirstBit = 0;

	switch(copy_u32GroupSubDiv)
	{
		case GROUP4_SUB_0 : Local_u8GroubFirstBit =0 ;  break ;
		case GROUP3_SUB_1 : Local_u8GroubFirstBit =1 ;  break ;
		case GROUP2_SUB_2 : Local_u8GroubFirstBit =2 ;  break ;
		case GROUP1_SUB_3 : Local_u8GroubFirstBit =3 ;  break ;
		case GROUP0_SUB_4 : Local_u8GroubFirstBit =4 ;  break ;
	}

	u8 Local_u8Priority =  copy_u8SupPriority|(copy_u8GroupPriority << Local_u8GroubFirstBit );


		NVIC_IPR[Copy_IntNumber] =  Local_u8Priority << 4;



	SCB_AIRCR = copy_u32GroupSubDiv;

	/* external peripheral */
}

void MNVIC_voidSetPriority(NVIC_Per_Position Copy_IntNumber , u8 Copy_u8Prority )
{
	if(Copy_IntNumber < 60)
	{
		NVIC_IPR[Copy_IntNumber]=Copy_u8Prority;
	}
	else
	{
		// report error 
	}
}
