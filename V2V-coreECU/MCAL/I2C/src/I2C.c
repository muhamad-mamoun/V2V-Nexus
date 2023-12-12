
#include "std_types.h"
#include "common_macros.h"
#include "I2C_prv.h"
#include "I2C.h"


I2C_enu_Error_t I2C_init(I2C_enu_index_t Copy_enu_I2C_index)
{
    I2C_enu_Error_t loc_enu_retStatus = I2C_OKAY;
    u32 loc_u32_I2Cx[I2C_MAX_INDEX] = {I2C_1_BASE,I2C_2_BASE,I2C_3_BASE};
    if (Copy_enu_I2C_index >= I2C_MAX_INDEX)
    {
        loc_enu_retStatus = I2C_INDEX_ERROR;
    }
    else
    {
        I2Cx(loc_u32_I2Cx[Copy_enu_I2C_index])->I2C_CR1 = FALSE; // Clear CR1 register
			  I2Cx(loc_u32_I2Cx[Copy_enu_I2C_index])->I2C_CR1 |= (1<<12) | (1<<17) |(1<<16); // Clear CR1 register
        I2Cx(loc_u32_I2Cx[Copy_enu_I2C_index])->I2C_CR2 = FALSE; // Clear CR2 register
        I2Cx(loc_u32_I2Cx[Copy_enu_I2C_index])->I2C_TIMINGR = MASTER_TIMING; // Adjust this timing value
        I2Cx(loc_u32_I2Cx[Copy_enu_I2C_index])->I2C_OAR1 = FALSE; // Clear OAR1 register
			   
        I2Cx(loc_u32_I2Cx[Copy_enu_I2C_index])->I2C_CR1 |= I2C_CR1_PE; // Enable I2C1 peripheral
    }
   
   return loc_enu_retStatus;
}

static void I2C_SW_RESET(void)
{
	I2Cx(I2C_1_BASE)->I2C_CR1 &= ~(1);
	I2Cx(I2C_1_BASE)->I2C_CR1 & (0x00000001);
	I2Cx(I2C_1_BASE)->I2C_CR1 |= (1);
}
void I2C_MASTER_init(u8 Address_Size,u16 SlaveAddress,u8 WriteOrRead,u8 bytes)
{
    if (Address_Size == SEVEN_BIT_ADDRESS)
    {
        I2Cx(I2C_1_BASE)->I2C_CR2 &= ~(1<<11);
        I2Cx(I2C_1_BASE)->I2C_CR2 |= (SlaveAddress);

    }
    else if (Address_Size == TEN_BIT_ADDRESS)
    {
        I2Cx(I2C_1_BASE)->I2C_CR2 |= (1<<11);
        I2Cx(I2C_1_BASE)->I2C_CR2 &= 0xFFFFFC00;
        SlaveAddress &= (0x000003FF); 
        I2Cx(I2C_1_BASE)->I2C_CR2 |= (SlaveAddress<<1);
    }
    if (WriteOrRead == WRITE_REQUEST)
    {
        I2Cx(I2C_1_BASE)->I2C_CR2 &=~(1<<10);
    }
    else if (WriteOrRead == READ_REQUEST)
    {
        I2Cx(I2C_1_BASE)->I2C_CR2 |=(1<<10);
    }
    
		
    I2Cx(I2C_1_BASE)->I2C_CR2 &= (0xFF00FFFF);
    I2Cx(I2C_1_BASE)->I2C_CR2 |= (bytes<<16);
}


I2C_enu_Error_t I2C_Start(I2C_enu_index_t Copy_enu_I2C_index)
{
    I2C_enu_Error_t loc_enu_retStatus = I2C_OKAY;
    u32 loc_u32_I2Cx[I2C_MAX_INDEX] = {I2C_1_BASE,I2C_2_BASE,I2C_3_BASE};
    if (Copy_enu_I2C_index >= I2C_MAX_INDEX)
    {
        loc_enu_retStatus = I2C_INDEX_ERROR;
    }
    else
    {
        //while ((GET_BIT(I2Cx(loc_u32_I2Cx[Copy_enu_I2C_index])->I2C_ISR,15)));
        I2Cx(loc_u32_I2Cx[Copy_enu_I2C_index])->I2C_CR2 |= (1<<13); // generate start
    }
    
    return loc_enu_retStatus;
}



I2C_enu_Error_t I2C_Stop(I2C_enu_index_t Copy_enu_I2C_index)
{
    I2C_enu_Error_t loc_enu_retStatus = I2C_OKAY;
    u32 loc_u32_I2Cx[I2C_MAX_INDEX] = {I2C_1_BASE,I2C_2_BASE,I2C_3_BASE};
    if (Copy_enu_I2C_index >= I2C_MAX_INDEX)
    {
        loc_enu_retStatus = I2C_INDEX_ERROR;
    }
    else
    {
        I2Cx(loc_u32_I2Cx[Copy_enu_I2C_index])->I2C_CR2 |= (1<<14);
        while (!(I2Cx(loc_u32_I2Cx[Copy_enu_I2C_index])->I2C_ISR & 0x00000020));
			  I2Cx(loc_u32_I2Cx[Copy_enu_I2C_index])->I2C_ICR = (1<<5);
    }
    
    return loc_enu_retStatus;
}


void I2C1_Write_byte(u8 data)
{
    I2Cx(I2C_1_BASE)->I2C_TXDR = data;
    while (!(I2Cx(I2C_1_BASE)->I2C_ISR & 0x00000001));
}

void I2C1_Read_byte(u8 *data)
{
    *data = I2Cx(I2C_1_BASE)->I2C_RXDR;
}


