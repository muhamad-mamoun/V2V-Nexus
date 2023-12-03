/***********************************************

Description : HEADER FILE FOR Can DRIVER 

Date        : 25-11-2023

Author      : Mohamed Khaled

***********************************************/
/**************************************************|| Includes ||********************************************************************/

#include "std_types.h"
#include "common_macros.h"
#include "Can.h"
#include "Can_Cfg.h"
#include "Can_Prv.h"
#include "RCC.h"
#include "gpio.h"
#include "gpio_prv.h"
/**************************************************||Function Implementation ||********************************************************************/
u32 ARR_Recieved_Data[14][8];

/*
 *Function Name : CAN_enuInit
 *Description   : Function to Initialize the CAN Peripheral
 *Parameters    : Config_Ptr -> Pointer to CAN_ConfigType configuration struct 
 *Return Type   : Error_status->Error Status Enum
 */
Error_status CAN_enuInit(const CAN_ConfigType* Config_Ptr)
{
	//Error Status Variable
	u8 ErrorStatus=CAN_enuOK;
	//if the Config_Ptr in Null 
	if(Config_Ptr == PTR_NULL)
	{
		//return null pointer error 
		ErrorStatus=CAN_NullPointerError;
	}
	
	//GPIO _ INIt
//	RCC_voidEnablePeripheral(AHB_BUS,GPIOA_EN);
//	GPIO_configurationsType CAN_GPIOConfig={GPIO_PORTA_ID,GPIO_PIN11_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_HIGH_SPEED};
//	GPIO_configurePin(&CAN_GPIOConfig);
//  GPIOA->AFRH |=(GPIO_AF09<<12);
//	GPIO_configurationsType CAN_GPIOConfig1={GPIO_PORTA_ID,GPIO_PIN12_ID,GPIO_ALTERNATE_PUSH_PULL_MODE,GPIO_HIGH_SPEED};
//	GPIO_configurePin(&CAN_GPIOConfig1);
//  GPIOA->AFRH |=(GPIO_AF09<<16);
//	RCC_voidEnablePeripheral(APB1_BUS,CAN_EN);
	
	//Init Mode In
	CAN_REG->CAN_MCR.INRQ=SET;
	//wait untill Init mode flag raise
	while(CAN_REG->CAN_MSR.INAK==CLR);
	//Sleep Mode out
	CAN_REG->CAN_MCR.SLEEP=CLR;
	//Wait untill sleep mode flag cleared
	while(CAN_REG->CAN_MSR.SLAK==SET);
	//Debug Freeze 
	CAN_REG->CAN_MCR.DBF=Config_Ptr->DebugFreeze;
	
	//Automatic WakeUP
	CAN_REG->CAN_MCR.AWUM= Config_Ptr->WakeUp;
	//BussOff
	CAN_REG->CAN_MCR.ABOM=Config_Ptr->BussOffManag;
	//Retransmission
	CAN_REG->CAN_MCR.NART=Config_Ptr->Retransmission;
	//LockedMode
	CAN_REG->CAN_MCR.RFLM=Config_Ptr->LockedMode;
	//TimeTriggered
	CAN_REG->CAN_MCR.TTCM=Config_Ptr->TimeTriggered;
	//FifoPriority
	CAN_REG->CAN_MCR.TXFP=Config_Ptr->FifoPriority;
	//BuadRate_prescaler
	CAN_REG->CAN_BTR.BRP=Config_Ptr->BuadRate_prescaler;
	
	
	//Interrupts Configurations
	//Busoff
	CAN_REG->CAN_IER.BOFIE=Busoff_interrupt_enable;
	//Error_passive_interrupt_enable
	CAN_REG->CAN_IER.EPVIE=Error_passive_interrupt_enable;
  //Error_interrupt_enable
	CAN_REG->CAN_IER.ERRIE=Error_interrupt_enable;
	//Error_warning_interrupt_enable
	CAN_REG->CAN_IER.EWGIE=Error_warning_interrupt_enable;
	//FIFO0_full_interrupt_enable
	CAN_REG->CAN_IER.FFIE0=FIFO0_full_interrupt_enable;
	//FIFO1_full_interrupt_enable
	CAN_REG->CAN_IER.FFIE1=FIFO1_full_interrupt_enable;
	//FIFO0_message_pending_interrupt_enable
	CAN_REG->CAN_IER.FMPIE0=FIFO0_message_pending_interrupt_enable;
	//FIFO1_message_pending_interrupt_enable
	CAN_REG->CAN_IER.FMPIE1=FIFO1_message_pending_interrupt_enable;
	//FIFO0_overrun_interrupt_enable
	CAN_REG->CAN_IER.FOVIE0=FIFO0_overrun_interrupt_enable;
	//FIFO1_overrun_interrupt_enable
	CAN_REG->CAN_IER.FOVIE1=FIFO1_overrun_interrupt_enable;
	//Last_error_code_interrupt_enable
	CAN_REG->CAN_IER.LECIE=Last_error_code_interrupt_enable;
	//Sleep_interrupt_enable
	CAN_REG->CAN_IER.SLKIE=Sleep_interrupt_enable;
	//Transmit_mailbox_empty_interrupt_enable
	CAN_REG->CAN_IER.TMEIE=Transmit_mailbox_empty_interrupt_enable;
	//Wakeup_interrupt_enable
	CAN_REG->CAN_IER.WKUIE=Wakeup_interrupt_enable;
	CAN_REG->CAN_MCR.INRQ=CLR;
	while(CAN_REG->CAN_MSR.INAK==SET);
	return ErrorStatus;//return error status value 
}


/*
 *Function Name : CAN_enuTransmit
 *Description   : Function to Transmit Data
 *Parameters    : Trans_Ptr -> Pointer to CAN_Transmit Transmit struct 
 *Return Type   : Error_status->Error Status Enum
 */
Error_status CAN_enuTransmit(const CAN_Transmit* Trans_Ptr)
{
	//Error Status Variable
	u8 ErrorStatus=CAN_enuOK;
	//if the Trans_Ptr in Null 
	if(Trans_Ptr == PTR_NULL)
	{
		//return null pointer error 
		ErrorStatus=CAN_NullPointerError;
	}
	
	if(CAN_REG->CAN_TSR.TME0==SET)
	{
	  if(Trans_Ptr->TEXID==STD_ID)
	  {
			 CAN_REG->Transimit_Mailbox0.ID_Reg.IDE=STD_ID;
		   CAN_REG->Transimit_Mailbox0.ID_Reg.STID= (Trans_Ptr->ID & 0x000007FF);
   	}
		else if(Trans_Ptr->TEXID==EX_ID)
	  {
			 CAN_REG->Transimit_Mailbox0.ID_Reg.IDE=EX_ID;
		   CAN_REG->Transimit_Mailbox0.ID_Reg.STID= (Trans_Ptr->ID & 0x1FFC0000);
			 CAN_REG->Transimit_Mailbox0.ID_Reg.EXID= (Trans_Ptr->ID & 0x0003FFFF);
   	}
		if(Trans_Ptr->RemoteFrame==DataFram)
		{
			CAN_REG->Transimit_Mailbox0.ID_Reg.RTR=DataFram;
			CAN_REG->Transimit_Mailbox0.DLC.DLC=Trans_Ptr->DataLenth;
			switch(Trans_Ptr->DataLenth)
			{
				case _1Byte_Data:
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA0=Trans_Ptr->Data[0];
				break;
				case _2Byte_Data:
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA1=Trans_Ptr->Data[1];

				break;
				case _3Byte_Data:
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA2=Trans_Ptr->Data[2];

				break;
				case _4Byte_Data:
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA2=Trans_Ptr->Data[2];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA3=Trans_Ptr->Data[3];

				break;
				case _5Byte_Data:
            CAN_REG->Transimit_Mailbox0.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA2=Trans_Ptr->Data[2];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA3=Trans_Ptr->Data[3];
						CAN_REG->Transimit_Mailbox0.Data_High.DATA4=Trans_Ptr->Data[4];

				break;
				case _6Byte_Data:
            CAN_REG->Transimit_Mailbox0.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA2=Trans_Ptr->Data[2];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA3=Trans_Ptr->Data[3];
						CAN_REG->Transimit_Mailbox0.Data_High.DATA4=Trans_Ptr->Data[4];
						CAN_REG->Transimit_Mailbox0.Data_High.DATA5=Trans_Ptr->Data[5];

				break;
				case _7Byte_Data:
					  CAN_REG->Transimit_Mailbox0.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA2=Trans_Ptr->Data[2];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA3=Trans_Ptr->Data[3];
						CAN_REG->Transimit_Mailbox0.Data_High.DATA4=Trans_Ptr->Data[4];
						CAN_REG->Transimit_Mailbox0.Data_High.DATA5=Trans_Ptr->Data[5];
						CAN_REG->Transimit_Mailbox0.Data_High.DATA6=Trans_Ptr->Data[6];

					break;
				case _8Byte_Data:
					  CAN_REG->Transimit_Mailbox0.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA2=Trans_Ptr->Data[2];
						CAN_REG->Transimit_Mailbox0.Data_Low.DATA3=Trans_Ptr->Data[3];
						CAN_REG->Transimit_Mailbox0.Data_High.DATA4=Trans_Ptr->Data[4];
						CAN_REG->Transimit_Mailbox0.Data_High.DATA5=Trans_Ptr->Data[5];
						CAN_REG->Transimit_Mailbox0.Data_High.DATA6=Trans_Ptr->Data[6];
						CAN_REG->Transimit_Mailbox0.Data_High.DATA7=Trans_Ptr->Data[7];

					break;		
			 default:
				 ErrorStatus=CAN_WrongParam;
					break;
						
			}
		}
		else if(Trans_Ptr->RemoteFrame==RemoteFram)
		{
			CAN_REG->Transimit_Mailbox0.ID_Reg.RTR=RemoteFram;
		}
		CAN_REG->Transimit_Mailbox0.ID_Reg.TXRQ=SET;
	}
	
	else if(CAN_REG->CAN_TSR.TME1==SET)
	{
		if(Trans_Ptr->TEXID==STD_ID)
	  {
			 CAN_REG->Transimit_Mailbox1.ID_Reg.IDE=STD_ID;
		   CAN_REG->Transimit_Mailbox1.ID_Reg.STID= (Trans_Ptr->ID & 0x000007FF);
   	}
		else if(Trans_Ptr->TEXID==EX_ID)
	  {
			 CAN_REG->Transimit_Mailbox1.ID_Reg.IDE=EX_ID;
		   CAN_REG->Transimit_Mailbox1.ID_Reg.STID= (Trans_Ptr->ID & 0x1FFC0000);
			 CAN_REG->Transimit_Mailbox1.ID_Reg.EXID= (Trans_Ptr->ID & 0x0003FFFF);
   	}
		if(Trans_Ptr->RemoteFrame==DataFram)
		{
			CAN_REG->Transimit_Mailbox1.ID_Reg.RTR=DataFram;
			CAN_REG->Transimit_Mailbox1.DLC.DLC=Trans_Ptr->DataLenth;
			switch(Trans_Ptr->DataLenth)
			{
				case _1Byte_Data:
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA0=Trans_Ptr->Data[0];
				break;
				case _2Byte_Data:
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA1=Trans_Ptr->Data[1];

				break;
				case _3Byte_Data:
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA2=Trans_Ptr->Data[2];

				break;
				case _4Byte_Data:
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA2=Trans_Ptr->Data[2];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA3=Trans_Ptr->Data[3];

				break;
				case _5Byte_Data:
            CAN_REG->Transimit_Mailbox1.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA2=Trans_Ptr->Data[2];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA3=Trans_Ptr->Data[3];
						CAN_REG->Transimit_Mailbox1.Data_High.DATA4=Trans_Ptr->Data[4];

				break;
				case _6Byte_Data:
            CAN_REG->Transimit_Mailbox1.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA2=Trans_Ptr->Data[2];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA3=Trans_Ptr->Data[3];
						CAN_REG->Transimit_Mailbox1.Data_High.DATA4=Trans_Ptr->Data[4];
						CAN_REG->Transimit_Mailbox1.Data_High.DATA5=Trans_Ptr->Data[5];

				break;
				case _7Byte_Data:
					  CAN_REG->Transimit_Mailbox1.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA2=Trans_Ptr->Data[2];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA3=Trans_Ptr->Data[3];
						CAN_REG->Transimit_Mailbox1.Data_High.DATA4=Trans_Ptr->Data[4];
						CAN_REG->Transimit_Mailbox1.Data_High.DATA5=Trans_Ptr->Data[5];
						CAN_REG->Transimit_Mailbox1.Data_High.DATA6=Trans_Ptr->Data[6];

					break;
				case _8Byte_Data:
					  CAN_REG->Transimit_Mailbox1.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA2=Trans_Ptr->Data[2];
						CAN_REG->Transimit_Mailbox1.Data_Low.DATA3=Trans_Ptr->Data[3];
						CAN_REG->Transimit_Mailbox1.Data_High.DATA4=Trans_Ptr->Data[4];
						CAN_REG->Transimit_Mailbox1.Data_High.DATA5=Trans_Ptr->Data[5];
						CAN_REG->Transimit_Mailbox1.Data_High.DATA6=Trans_Ptr->Data[6];
						CAN_REG->Transimit_Mailbox1.Data_High.DATA7=Trans_Ptr->Data[7];

					break;		
			 default:
				 ErrorStatus=CAN_WrongParam;
					break;
						
			}
		}
		else if(Trans_Ptr->RemoteFrame==RemoteFram)
		{
			CAN_REG->Transimit_Mailbox1.ID_Reg.RTR=RemoteFram;
		}
		CAN_REG->Transimit_Mailbox1.ID_Reg.TXRQ=SET;
	}
	
	else if(CAN_REG->CAN_TSR.TME2==SET)
	{
		if(Trans_Ptr->TEXID==STD_ID)
	  {
			 CAN_REG->Transimit_Mailbox2.ID_Reg.IDE=STD_ID;
		   CAN_REG->Transimit_Mailbox2.ID_Reg.STID= (Trans_Ptr->ID & 0x000007FF);
   	}
		else if(Trans_Ptr->TEXID==EX_ID)
	  {
			 CAN_REG->Transimit_Mailbox2.ID_Reg.IDE=EX_ID;
		   CAN_REG->Transimit_Mailbox2.ID_Reg.STID= (Trans_Ptr->ID & 0x1FFC0000);
			 CAN_REG->Transimit_Mailbox2.ID_Reg.EXID= (Trans_Ptr->ID & 0x0003FFFF);
   	}
		if(Trans_Ptr->RemoteFrame==DataFram)
		{
			CAN_REG->Transimit_Mailbox2.ID_Reg.RTR=DataFram;
			CAN_REG->Transimit_Mailbox2.DLC.DLC=Trans_Ptr->DataLenth;
			switch(Trans_Ptr->DataLenth)
			{
				case _1Byte_Data:
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA0=Trans_Ptr->Data[0];
				break;
				case _2Byte_Data:
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA1=Trans_Ptr->Data[1];

				break;
				case _3Byte_Data:
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA2=Trans_Ptr->Data[2];

				break;
				case _4Byte_Data:
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA2=Trans_Ptr->Data[2];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA3=Trans_Ptr->Data[3];

				break;
				case _5Byte_Data:
            CAN_REG->Transimit_Mailbox2.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA2=Trans_Ptr->Data[2];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA3=Trans_Ptr->Data[3];
						CAN_REG->Transimit_Mailbox2.Data_High.DATA4=Trans_Ptr->Data[4];

				break;
				case _6Byte_Data:
            CAN_REG->Transimit_Mailbox2.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA2=Trans_Ptr->Data[2];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA3=Trans_Ptr->Data[3];
						CAN_REG->Transimit_Mailbox2.Data_High.DATA4=Trans_Ptr->Data[4];
						CAN_REG->Transimit_Mailbox2.Data_High.DATA5=Trans_Ptr->Data[5];

				break;
				case _7Byte_Data:
					  CAN_REG->Transimit_Mailbox2.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA2=Trans_Ptr->Data[2];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA3=Trans_Ptr->Data[3];
						CAN_REG->Transimit_Mailbox2.Data_High.DATA4=Trans_Ptr->Data[4];
						CAN_REG->Transimit_Mailbox2.Data_High.DATA5=Trans_Ptr->Data[5];
						CAN_REG->Transimit_Mailbox2.Data_High.DATA6=Trans_Ptr->Data[6];

					break;
				case _8Byte_Data:
					  CAN_REG->Transimit_Mailbox2.Data_Low.DATA0=Trans_Ptr->Data[0];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA1=Trans_Ptr->Data[1];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA2=Trans_Ptr->Data[2];
						CAN_REG->Transimit_Mailbox2.Data_Low.DATA3=Trans_Ptr->Data[3];
						CAN_REG->Transimit_Mailbox2.Data_High.DATA4=Trans_Ptr->Data[4];
						CAN_REG->Transimit_Mailbox2.Data_High.DATA5=Trans_Ptr->Data[5];
						CAN_REG->Transimit_Mailbox2.Data_High.DATA6=Trans_Ptr->Data[6];
						CAN_REG->Transimit_Mailbox2.Data_High.DATA7=Trans_Ptr->Data[7];

					break;		
			 default:
				 ErrorStatus=CAN_WrongParam;
					break;
						
			}
		}
		else if(Trans_Ptr->RemoteFrame==RemoteFram)
		{
			CAN_REG->Transimit_Mailbox2.ID_Reg.RTR=RemoteFram;
		}
		CAN_REG->Transimit_Mailbox2.ID_Reg.TXRQ=SET;
	}
	return ErrorStatus;//return error status value 
}




/*
 *Function Name : CAN_enuCreateFilter
 *Description   : Function to create Filter 
 *Parameters    : FilterCFG_Ptr -> Pointer to FilterConfig Filter Configuration struct 
 *Return Type   : Error_status->Error Status Enum
 */
Error_status CAN_enuCreateFilter(const FilterConfig* FilterCFG_Ptr)
{
	//Error Status Variable
	u8 ErrorStatus=CAN_enuOK;
	//if the Trans_Ptr in Null 
	if(FilterCFG_Ptr == PTR_NULL)
	{
		//return null pointer error 
		ErrorStatus=CAN_NullPointerError;
	}
	
	CAN_REG->CAN_FMR.FINIT=SET;
	switch(FilterCFG_Ptr->FilterNumber)
	{
		case FilterNumber0:
			
		
		if(FilterCFG_Ptr->Mask==MaskMode)
			{
				CAN_REG->CAN_FM1R.FBM0=MaskMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC0=Dual;
					CAN_REG->CAN_FFA1R.FFA0=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F0R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F0R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F0R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F0R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F0R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F0R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F0R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F0R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC0=Single;
						CAN_REG->CAN_FFA1R.FFA0=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F0R1= FilterCFG_Ptr->FilterID;
						CAN_REG->CAN_Filter_Banks.CAN_F0R2=FilterCFG_Ptr->FilterMask;
					  
				}
			}
			else if(FilterCFG_Ptr->Mask==ListMode)
			{
				CAN_REG->CAN_FS1R.FSC0=ListMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC0=Dual;
					CAN_REG->CAN_FFA1R.FFA0=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F0R1=(CAN_REG->CAN_Filter_Banks.CAN_F0R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F0R2=(CAN_REG->CAN_Filter_Banks.CAN_F0R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC0=Single;
						CAN_REG->CAN_FFA1R.FFA0=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F0R1= ((FilterCFG_Ptr->FilterID)<<21);					  
				}
				
			}
				CAN_REG->CAN_FMR.FINIT=CLR;
		CAN_REG->CAN_FA1R.FACT0=SET;
			break;
		case FilterNumber1:
		
     if(FilterCFG_Ptr->Mask==MaskMode)
			{
				CAN_REG->CAN_FM1R.FBM1=MaskMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC1=Dual;
					CAN_REG->CAN_FFA1R.FFA1=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F1R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F1R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F1R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F1R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F1R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F1R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F1R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F1R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC1=Single;
						CAN_REG->CAN_FFA1R.FFA1=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F1R1= FilterCFG_Ptr->FilterID;
						CAN_REG->CAN_Filter_Banks.CAN_F1R2=FilterCFG_Ptr->FilterMask;
					  
				}
			}
			else if(FilterCFG_Ptr->Mask==ListMode)
			{
				CAN_REG->CAN_FS1R.FSC1=ListMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC1=Dual;
					CAN_REG->CAN_FFA1R.FFA1=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F1R1=(CAN_REG->CAN_Filter_Banks.CAN_F1R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F1R2=(CAN_REG->CAN_Filter_Banks.CAN_F1R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC1=Single;
						CAN_REG->CAN_FFA1R.FFA1=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F1R1= FilterCFG_Ptr->FilterID;					  
				}
				
			}
							CAN_REG->CAN_FMR.FINIT=CLR;

		CAN_REG->CAN_FA1R.FACT1=SET;
			
		break;
		case FilterNumber2:
			
		if(FilterCFG_Ptr->Mask==MaskMode)
			{
				CAN_REG->CAN_FM1R.FBM2=MaskMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC2=Dual;
					CAN_REG->CAN_FFA1R.FFA2=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F2R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F2R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F2R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F2R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F2R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F2R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F2R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F2R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC2=Single;
						CAN_REG->CAN_FFA1R.FFA2=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F2R1= FilterCFG_Ptr->FilterID;
						CAN_REG->CAN_Filter_Banks.CAN_F2R2=FilterCFG_Ptr->FilterMask;
					  
				}
			}
			else if(FilterCFG_Ptr->Mask==ListMode)
			{
				CAN_REG->CAN_FS1R.FSC2=ListMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC2=Dual;
					CAN_REG->CAN_FFA1R.FFA2=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F2R1=(CAN_REG->CAN_Filter_Banks.CAN_F2R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F2R2=(CAN_REG->CAN_Filter_Banks.CAN_F2R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC2=Single;
						CAN_REG->CAN_FFA1R.FFA2=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F2R1= FilterCFG_Ptr->FilterID;					  
				}
				
			}
							CAN_REG->CAN_FMR.FINIT=CLR;

				CAN_REG->CAN_FA1R.FACT2=SET;

		break;
		case FilterNumber3:
			
		if(FilterCFG_Ptr->Mask==MaskMode)
			{
				CAN_REG->CAN_FM1R.FBM3=MaskMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC3=Dual;
					CAN_REG->CAN_FFA1R.FFA3=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F3R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F3R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F3R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F3R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F3R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F3R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F3R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F3R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC3=Single;
						CAN_REG->CAN_FFA1R.FFA3=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F3R1= FilterCFG_Ptr->FilterID;
						CAN_REG->CAN_Filter_Banks.CAN_F3R2=FilterCFG_Ptr->FilterMask;
					  
				}
			}
			else if(FilterCFG_Ptr->Mask==ListMode)
			{
				CAN_REG->CAN_FS1R.FSC3=ListMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC3=Dual;
					CAN_REG->CAN_FFA1R.FFA3=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F3R1=(CAN_REG->CAN_Filter_Banks.CAN_F3R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F3R2=(CAN_REG->CAN_Filter_Banks.CAN_F3R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC3=Single;
						CAN_REG->CAN_FFA1R.FFA3=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F3R1= FilterCFG_Ptr->FilterID;					  
				}
				
			}
						CAN_REG->CAN_FMR.FINIT=CLR;
	
				CAN_REG->CAN_FA1R.FACT3=SET;

		break;
		case FilterNumber4:
		
    if(FilterCFG_Ptr->Mask==MaskMode)
			{
				CAN_REG->CAN_FM1R.FBM4=MaskMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC4=Dual;
					CAN_REG->CAN_FFA1R.FFA4=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F4R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F4R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F4R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F4R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F4R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F4R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F4R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F4R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC4=Single;
						CAN_REG->CAN_FFA1R.FFA4=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F4R1= FilterCFG_Ptr->FilterID;
						CAN_REG->CAN_Filter_Banks.CAN_F4R2=FilterCFG_Ptr->FilterMask;
					  
				}
			}
			else if(FilterCFG_Ptr->Mask==ListMode)
			{
				CAN_REG->CAN_FS1R.FSC4=ListMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC4=Dual;
					CAN_REG->CAN_FFA1R.FFA4=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F4R1=(CAN_REG->CAN_Filter_Banks.CAN_F4R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F4R2=(CAN_REG->CAN_Filter_Banks.CAN_F4R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC4=Single;
						CAN_REG->CAN_FFA1R.FFA4=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F4R1= FilterCFG_Ptr->FilterID;					  
				}
				
			}
							CAN_REG->CAN_FMR.FINIT=CLR;

					CAN_REG->CAN_FA1R.FACT4=SET;

			break;
		case FilterNumber5:
		
			if(FilterCFG_Ptr->Mask==MaskMode)
			{
				CAN_REG->CAN_FM1R.FBM5=MaskMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC5=Dual;
					CAN_REG->CAN_FFA1R.FFA5=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F5R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F5R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F5R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F5R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F5R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F5R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F5R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F5R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC5=Single;
						CAN_REG->CAN_FFA1R.FFA5=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F5R1= FilterCFG_Ptr->FilterID;
						CAN_REG->CAN_Filter_Banks.CAN_F5R2=FilterCFG_Ptr->FilterMask;
					  
				}
			}
			else if(FilterCFG_Ptr->Mask==ListMode)
			{
				CAN_REG->CAN_FS1R.FSC5=ListMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC5=Dual;
					CAN_REG->CAN_FFA1R.FFA5=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F5R1=(CAN_REG->CAN_Filter_Banks.CAN_F5R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F5R2=(CAN_REG->CAN_Filter_Banks.CAN_F5R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC5=Single;
						CAN_REG->CAN_FFA1R.FFA5=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F5R1= FilterCFG_Ptr->FilterID;					  
				}
				
			}
							CAN_REG->CAN_FMR.FINIT=CLR;

					CAN_REG->CAN_FA1R.FACT5=SET;

		break;
		case FilterNumber6:
		
		if(FilterCFG_Ptr->Mask==MaskMode)
			{
				CAN_REG->CAN_FM1R.FBM6=MaskMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC6=Dual;
					CAN_REG->CAN_FFA1R.FFA6=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F6R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F6R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F6R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F6R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F6R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F6R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F6R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F6R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC6=Single;
						CAN_REG->CAN_FFA1R.FFA6=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F6R1= FilterCFG_Ptr->FilterID;
						CAN_REG->CAN_Filter_Banks.CAN_F6R2=FilterCFG_Ptr->FilterMask;
					  
				}
			}
			else if(FilterCFG_Ptr->Mask==ListMode)
			{
				CAN_REG->CAN_FS1R.FSC6=ListMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC6=Dual;
					CAN_REG->CAN_FFA1R.FFA6=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F6R1=(CAN_REG->CAN_Filter_Banks.CAN_F6R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F6R2=(CAN_REG->CAN_Filter_Banks.CAN_F6R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC6=Single;
						CAN_REG->CAN_FFA1R.FFA6=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F6R1= FilterCFG_Ptr->FilterID;					  
				}
				
			}
							CAN_REG->CAN_FMR.FINIT=CLR;

					CAN_REG->CAN_FA1R.FACT6=SET;

		break;
		case FilterNumber7:
		
			if(FilterCFG_Ptr->Mask==MaskMode)
			{
				CAN_REG->CAN_FM1R.FBM7=MaskMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC7=Dual;
					CAN_REG->CAN_FFA1R.FFA7=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F7R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F7R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F7R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F7R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F7R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F7R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F7R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F7R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC7=Single;
						CAN_REG->CAN_FFA1R.FFA7=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F7R1= FilterCFG_Ptr->FilterID;
						CAN_REG->CAN_Filter_Banks.CAN_F7R2=FilterCFG_Ptr->FilterMask;
					  
				}
			}
			else if(FilterCFG_Ptr->Mask==ListMode)
			{
				CAN_REG->CAN_FS1R.FSC7=ListMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC7=Dual;
					CAN_REG->CAN_FFA1R.FFA7=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F7R1=(CAN_REG->CAN_Filter_Banks.CAN_F7R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F7R2=(CAN_REG->CAN_Filter_Banks.CAN_F7R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC7=Single;
						CAN_REG->CAN_FFA1R.FFA7=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F7R1= FilterCFG_Ptr->FilterID;					  
				}
				
			}
							CAN_REG->CAN_FMR.FINIT=CLR;

		CAN_REG->CAN_FA1R.FACT7=SET;

		break;
		case FilterNumber8:
			
		if(FilterCFG_Ptr->Mask==MaskMode)
			{
				CAN_REG->CAN_FM1R.FBM8=MaskMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC8=Dual;
					CAN_REG->CAN_FFA1R.FFA8=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F8R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F8R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F8R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F8R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F8R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F8R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F8R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F8R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC8=Single;
						CAN_REG->CAN_FFA1R.FFA8=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F8R1= FilterCFG_Ptr->FilterID;
						CAN_REG->CAN_Filter_Banks.CAN_F8R2=FilterCFG_Ptr->FilterMask;
					  
				}
			}
			else if(FilterCFG_Ptr->Mask==ListMode)
			{
				CAN_REG->CAN_FS1R.FSC8=ListMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC8=Dual;
					CAN_REG->CAN_FFA1R.FFA8=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F8R1=(CAN_REG->CAN_Filter_Banks.CAN_F8R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F8R2=(CAN_REG->CAN_Filter_Banks.CAN_F8R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC8=Single;
						CAN_REG->CAN_FFA1R.FFA8=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F8R1= FilterCFG_Ptr->FilterID;					  
				}
				
			}
							CAN_REG->CAN_FMR.FINIT=CLR;

					CAN_REG->CAN_FA1R.FACT8=SET;

			break;
		case FilterNumber9:
			
		if(FilterCFG_Ptr->Mask==MaskMode)
			{
				CAN_REG->CAN_FM1R.FBM9=MaskMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC9=Dual;
					CAN_REG->CAN_FFA1R.FFA9=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F9R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F9R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F9R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F9R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F9R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F9R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F9R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F9R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC9=Single;
						CAN_REG->CAN_FFA1R.FFA9=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F9R1= FilterCFG_Ptr->FilterID;
						CAN_REG->CAN_Filter_Banks.CAN_F9R2=FilterCFG_Ptr->FilterMask;
					  
				}
			}
			else if(FilterCFG_Ptr->Mask==ListMode)
			{
				CAN_REG->CAN_FS1R.FSC9=ListMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC9=Dual;
					CAN_REG->CAN_FFA1R.FFA9=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F9R1=(CAN_REG->CAN_Filter_Banks.CAN_F9R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F9R2=(CAN_REG->CAN_Filter_Banks.CAN_F9R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC9=Single;
						CAN_REG->CAN_FFA1R.FFA9=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F9R1= FilterCFG_Ptr->FilterID;					  
				}
				
			}
							CAN_REG->CAN_FMR.FINIT=CLR;

					CAN_REG->CAN_FA1R.FACT9=SET;

			break;
		case FilterNumber10:
			
		if(FilterCFG_Ptr->Mask==MaskMode)
			{
				CAN_REG->CAN_FM1R.FBM10=MaskMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC10=Dual;
					CAN_REG->CAN_FFA1R.FFA10=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F10R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F10R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F10R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F10R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F10R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F10R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F10R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F10R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC10=Single;
						CAN_REG->CAN_FFA1R.FFA10=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F10R1= FilterCFG_Ptr->FilterID;
						CAN_REG->CAN_Filter_Banks.CAN_F10R2=FilterCFG_Ptr->FilterMask;
					  
				}
			}
			else if(FilterCFG_Ptr->Mask==ListMode)
			{
				CAN_REG->CAN_FS1R.FSC10=ListMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC10=Dual;
					CAN_REG->CAN_FFA1R.FFA10=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F10R1=(CAN_REG->CAN_Filter_Banks.CAN_F10R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F10R2=(CAN_REG->CAN_Filter_Banks.CAN_F10R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC10=Single;
						CAN_REG->CAN_FFA1R.FFA10=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F10R1= FilterCFG_Ptr->FilterID;					  
				}
				
			}
							CAN_REG->CAN_FMR.FINIT=CLR;

					CAN_REG->CAN_FA1R.FACT10=SET;

			break;
		case FilterNumber11:
			
		if(FilterCFG_Ptr->Mask==MaskMode)
			{
				CAN_REG->CAN_FM1R.FBM11=MaskMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC11=Dual;
					CAN_REG->CAN_FFA1R.FFA11=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F11R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F11R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F11R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F11R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F11R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F11R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F11R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F11R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC11=Single;
						CAN_REG->CAN_FFA1R.FFA11=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F11R1= FilterCFG_Ptr->FilterID;
						CAN_REG->CAN_Filter_Banks.CAN_F11R2=FilterCFG_Ptr->FilterMask;
					  
				}
			}
			else if(FilterCFG_Ptr->Mask==ListMode)
			{
				CAN_REG->CAN_FS1R.FSC11=ListMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC11=Dual;
					CAN_REG->CAN_FFA1R.FFA11=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F11R1=(CAN_REG->CAN_Filter_Banks.CAN_F11R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F11R2=(CAN_REG->CAN_Filter_Banks.CAN_F11R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC11=Single;
						CAN_REG->CAN_FFA1R.FFA11=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F11R1= FilterCFG_Ptr->FilterID;					  
				}
				
			}
							CAN_REG->CAN_FMR.FINIT=CLR;

					CAN_REG->CAN_FA1R.FACT11=SET;

			break;
		case FilterNumber12:
		
		if(FilterCFG_Ptr->Mask==MaskMode)
			{
				CAN_REG->CAN_FM1R.FBM12=MaskMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC12=Dual;
					CAN_REG->CAN_FFA1R.FFA12=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F12R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F12R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F12R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F12R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F12R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F12R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F12R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F12R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC12=Single;
						CAN_REG->CAN_FFA1R.FFA12=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F12R1= FilterCFG_Ptr->FilterID;
						CAN_REG->CAN_Filter_Banks.CAN_F12R2=FilterCFG_Ptr->FilterMask;
					  
				}
			}
			else if(FilterCFG_Ptr->Mask==ListMode)
			{
				CAN_REG->CAN_FS1R.FSC12=ListMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC12=Dual;
					CAN_REG->CAN_FFA1R.FFA12=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F12R1 =(CAN_REG->CAN_Filter_Banks.CAN_F12R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F12R2 =(CAN_REG->CAN_Filter_Banks.CAN_F12R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC12=Single;
						CAN_REG->CAN_FFA1R.FFA12=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F12R1= FilterCFG_Ptr->FilterID;					  
				}
				
			}
							CAN_REG->CAN_FMR.FINIT=CLR;

				CAN_REG->CAN_FA1R.FACT12=SET;

			break;
		case FilterNumber13:

		if(FilterCFG_Ptr->Mask==MaskMode)
			{
				CAN_REG->CAN_FM1R.FBM13=MaskMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC13=Dual;
					CAN_REG->CAN_FFA1R.FFA13=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F13R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F13R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F13R1 |=(CAN_REG->CAN_Filter_Banks.CAN_F13R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F13R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F13R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					CAN_REG->CAN_Filter_Banks.CAN_F13R2 |=(CAN_REG->CAN_Filter_Banks.CAN_F13R1 & 0xFFFF0000) | (FilterCFG_Ptr->FilterMask<<16);
					}
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC13=Single;
						CAN_REG->CAN_FFA1R.FFA13=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F13R1= FilterCFG_Ptr->FilterID;
						CAN_REG->CAN_Filter_Banks.CAN_F13R2=FilterCFG_Ptr->FilterMask;
					  
				}
			}
			else if(FilterCFG_Ptr->Mask==ListMode)
			{
				CAN_REG->CAN_FS1R.FSC13=ListMode;
				if(FilterCFG_Ptr->Scale==Dual)
				{
					CAN_REG->CAN_FS1R.FSC13=Dual;
					CAN_REG->CAN_FFA1R.FFA13=FilterCFG_Ptr->FIFO_Asign;
					if(FilterCFG_Ptr->RegNumber==_1R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F13R1=(CAN_REG->CAN_Filter_Banks.CAN_F13R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					else if(FilterCFG_Ptr->RegNumber==_2R)
					{
					CAN_REG->CAN_Filter_Banks.CAN_F13R2=(CAN_REG->CAN_Filter_Banks.CAN_F13R1 & 0x0000FFFF) | FilterCFG_Ptr->FilterID;
					}
					
				}
				else if(FilterCFG_Ptr->Scale==Single)
				{
					  CAN_REG->CAN_FS1R.FSC13=Single;
						CAN_REG->CAN_FFA1R.FFA13=FilterCFG_Ptr->FIFO_Asign;
					  CAN_REG->CAN_Filter_Banks.CAN_F13R1= FilterCFG_Ptr->FilterID;					  
				}
				
			}
							CAN_REG->CAN_FMR.FINIT=CLR;

				CAN_REG->CAN_FA1R.FACT13=SET;

		break;
		default :
			ErrorStatus=CAN_WrongParam;
			break;
	}
	return ErrorStatus;//return error status value 
}







/*
 *Function Name : CAN_enuRecieve
 *Description   : Function to Recieve Data 
 *Parameters    : ADD_u8DataIndex -> Pointer to u8 variable that take the data index in ARR_Recieved_Data array
 *Return Type   : Error_status->Error Status Enum
 */
Error_status CAN_enuRecieve(u8* ADD_u8DataIndex)
{
	u8 ErrorStatus=CAN_enuOK;
	if(ADD_u8DataIndex == PTR_NULL)
	{
		ErrorStatus=CAN_NullPointerError;
	}
	if(CAN_REG->CAN_RF0R.FMP0==CLR && CAN_REG->CAN_RF1R.FMP1==CLR)
	{
		ErrorStatus=CAN_NORecievedData;
	}
	else
	{
		*ADD_u8DataIndex=CAN_REG->Recieve_Mailbox0.DLC.FMI;
		while(CAN_REG->CAN_RF0R.FMP0 !=CLR)
		{
			switch(CAN_REG->Recieve_Mailbox0.DLC.DLC)
			{
			case _1Byte_Data :
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA0;
				break;
			case _2Byte_Data :
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA0;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_1Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA1;

				break;
			case _3Byte_Data :
        ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA0;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_1Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA1;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_2Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA2;
				
			break;
			case _4Byte_Data :
			  ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA0;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_1Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA1;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_2Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA2;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_3Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA3;

			break;
			case _5Byte_Data :
			  ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA0;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_1Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA1;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_2Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA2;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_3Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA3;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_4Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_High.DATA4;

			
				break;
			case _6Byte_Data :
  			ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA0;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_1Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA1;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_2Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA2;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_3Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA3;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_4Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_High.DATA4;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_5Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_High.DATA5;

			break;
			case _7Byte_Data :
  			ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA0;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_1Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA1;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_2Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA2;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_3Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA3;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_4Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_High.DATA4;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_5Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_High.DATA5;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_6Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_High.DATA6;

			break;
			case _8Byte_Data :
      	ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA0;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_1Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA1;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_2Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA2;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_3Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_Low.DATA3;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_4Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_High.DATA4;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_5Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_High.DATA5;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_6Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_High.DATA6;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox0.DLC.FMI][_7Byte_Data]=CAN_REG->Recieve_Mailbox0.Data_High.DATA7;

			break;
			
			}
			CAN_REG->CAN_RF0R.RFOM0=SET;
		}
		
		while(CAN_REG->CAN_RF1R.FMP1 !=CLR)
		{
			switch(CAN_REG->Recieve_Mailbox1.DLC.DLC)
			{
			case _1Byte_Data :
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA0;
				break;
			case _2Byte_Data :
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA0;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_1Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA1;

				break;
			case _3Byte_Data :
        ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA0;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_1Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA1;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_2Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA2;
				
			break;
			case _4Byte_Data :
			  ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA0;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_1Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA1;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_2Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA2;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_3Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA3;

			break;
			case _5Byte_Data :
			  ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA0;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_1Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA1;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_2Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA2;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_3Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA3;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_4Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_High.DATA4;

			
				break;
			case _6Byte_Data :
  			ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA0;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_1Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA1;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_2Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA2;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_3Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA3;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_4Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_High.DATA4;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_5Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_High.DATA5;

			break;
			case _7Byte_Data :
  			ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA0;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_1Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA1;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_2Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA2;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_3Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA3;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_4Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_High.DATA4;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_5Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_High.DATA5;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_6Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_High.DATA6;

			break;
			case _8Byte_Data :
      	ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_0Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA0;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_1Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA1;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_2Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA2;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_3Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_Low.DATA3;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_4Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_High.DATA4;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_5Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_High.DATA5;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_6Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_High.DATA6;
				ARR_Recieved_Data[CAN_REG->Recieve_Mailbox1.DLC.FMI][_7Byte_Data]=CAN_REG->Recieve_Mailbox1.Data_High.DATA7;

			break;
			
			}
			CAN_REG->CAN_RF1R.RFOM1=SET;
		}
		
	}
	return ErrorStatus;//return error status value
}


	


/*
 *Function Name : CAN_enuChangeMode
 *Description   : Function to change Can Mode
 *Parameters    : Mode -> CAN_Modes Enum type 
 *Return Type   : Error_status->Error Status Enum
 */
Error_status CAN_enuChangeMode(CAN_Modes Mode)
{
	u8 ErrorStatus=CAN_enuOK;
	switch(Mode)
	{
		case SLEEP_Mode:
		CAN_REG->CAN_MCR.INRQ=CLR;
		CAN_REG->CAN_MCR.SLEEP=SET;
		while(CAN_REG->CAN_MSR.INAK==SET);
		while(CAN_REG->CAN_MSR.SLAK==CLR);
		break;
    case INIT_Mode:
			CAN_REG->CAN_MCR.INRQ=SET;
		CAN_REG->CAN_MCR.SLEEP=CLR;
		while(CAN_REG->CAN_MSR.INAK==CLR);
		while(CAN_REG->CAN_MSR.SLAK==SET);
			break;
    case NORMAL_Mode:
			CAN_REG->CAN_MCR.INRQ=CLR;
		CAN_REG->CAN_MCR.SLEEP=CLR;
		while(CAN_REG->CAN_MSR.INAK==SET);
		while(CAN_REG->CAN_MSR.SLAK==SET);
			break;
		default :
		ErrorStatus=CAN_WrongParam;
		break;
	}
	
		return ErrorStatus;//return error status value
}



/*
 *Function Name : CAN_enuAbort
 *Description   : Function to Abort Messages
 *Parameters    : mailBox -> mailBox Enum type 
 *Return Type   : Error_status->Error Status Enum
 */
Error_status CAN_enuAbort(AbortMessage mailBox)
{
	u8 ErrorStatus=CAN_enuOK;
	switch(mailBox)
	{
		case MailBox0:
			CAN_REG->CAN_TSR.ABRQ0=SET;
			break;
		case MailBox1:
			CAN_REG->CAN_TSR.ABRQ1=SET;
			break;
		case MailBox2:
			CAN_REG->CAN_TSR.ABRQ2=SET;

			break;
		default:
			ErrorStatus=CAN_WrongParam;
			break;
	}
	return ErrorStatus;//return error status value
}






/*
 *Function Name : CAN_enuGoTestMode
 *Description   : Function to Go to Test Mode
 *Parameters    : TMode -> TestModes Enum type 
 *Return Type   : Error_status->Error Status Enum
 */
Error_status CAN_enuGoTestMode(TestModes TMode)
{
	u8 ErrorStatus=CAN_enuOK;
	CAN_REG->CAN_MCR.INRQ=SET;
	while(CAN_REG->CAN_MSR.INAK==CLR);
	switch(TMode)
	{
		case SilentMode:
			CAN_REG->CAN_BTR.SILM |=SET;
			CAN_REG->CAN_BTR.LBKM |=CLR;
			break;
		case LoopBackMode:
			CAN_REG->CAN_BTR.SILM |=CLR;
			CAN_REG->CAN_BTR.LBKM |=SET;
			break;
		case CombinedLoopBackMode:
			CAN_REG->CAN_BTR.SILM |=SET;
			CAN_REG->CAN_BTR.LBKM |=SET;
			break;
		default:
			ErrorStatus=CAN_WrongParam;
			break;
	}
		CAN_REG->CAN_MCR.INRQ=CLR;
	while(CAN_REG->CAN_MSR.INAK==SET);

		return ErrorStatus;//return error status value
}