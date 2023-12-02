/***********************************************

Description : Private FILE FOR Can DRIVER 

Date        : 24-11-2023

Author      : Mohamed Khaled

***********************************************/

#ifndef CAN_PRV_H
#define CAN_PRV_H
#include "std_types.h"


#define SET           1
#define CLR           0


//CAN_MCR
typedef volatile struct 
{
	u32 INRQ  :1;
	u32 SLEEP :1;
	u32 TXFP  :1;
	u32 RFLM  :1;
	u32 NART  :1;
	u32 AWUM  :1;
	u32 ABOM  :1;
	u32 TTCM  :1;
	u32 RES   :7;
	u32 RESET :1;
	u32 DBF   :1;
	u32 RES1  :15;
}MCR;

//CAN_MSR       
typedef volatile struct 
{
	u32 INAK :1;
	u32 SLAK :1;
	u32 ERRI :1;
	u32 WKUI :1;
	u32 SLAKI:1;
	u32 RES  :3;
	u32 TXM  :1;
  u32 RXM  :1;
	u32 SAMP :1;
	u32 RX   :1;
	u32 RES1  :20;
}MSR;

//CAN_TSR
typedef volatile struct 
{
	u32 RQCP0 :1;
	u32 TXOK0 :1;
	u32 ALST0 :1;
	u32 TERR0 :1;
	u32 RES   :3;
	u32 ABRQ0 :1;
	u32 RQCP1 :1;
  u32 TXOK1 :1;
	u32 ALST1 :1;
	u32 TERR1 :1;
	u32 RES1  :3;
	u32 ABRQ1 :1;
	u32 RQCP2 :1;
  u32 TXOK2 :1;
	u32 ALST2 :1;
	u32 TERR2 :1;
	u32 RES2 :3;
	u32 ABRQ2 :1;
	u32 CODE :2;
	u32 TME0 :1;
	u32 TME1 :1;
	u32 TME2 :1;
	u32 LOW0 :1;
	u32 LOW1 :1;
	u32 LOW2 :1;
}TSR;

//CAN_RF0R  
typedef volatile struct 
{
	u32 FMP0 :2;
	u32 Res  :1;
	u32 FULL0 :1;
	u32 FOVR0 :1;
	u32 RFOM0 :1;
	u32 Res1 :26;
}RF0R;

//CAN_RF1R    
typedef volatile struct 
{
	u32 FMP1 :2;
	u32 Res  :1;
	u32 FULL1 :1;
	u32 FOVR1 :1;
	u32 RFOM1 :1;
	u32 Res1 :26;
}RF1R;

//CAN_IER
typedef volatile struct 
{
	u32 TMEIE:1;
	u32 FMPIE0:1;
	u32 FFIE0 :1;
	u32 FOVIE0 :1;
	u32 FMPIE1 :1;
	u32 FFIE1:1;
	u32 FOVIE1:1;
	u32 Res:1;
	u32 EWGIE:1;
	u32 EPVIE:1;
	u32 BOFIE:1;
	u32 LECIE:1;
	u32 Res1:3;
	u32 ERRIE:1;
	u32 WKUIE:1;
	u32 SLKIE:1;
	u32 Res2:14;

}IER;

//CAN_ESR   
typedef volatile struct 
{
	u32 EWGF:1;
	u32 EPVF:1;
	u32 BOFF :1;
	u32 Res :1;
	u32 LEC :3;
	u32 Res1:9;
	u32 TEC:8;
	u32 REC:8;

}ESR;
 

//CAN_BTR
typedef volatile struct 
{
	u32 BRP :30;
	u32 LBKM:1;
	u32 SILM:1;
}BTR;

// First Transimmit Mailbox   
//CAN_TI0R
typedef volatile struct 
{
	u32 TXRQ  :1;
	u32 RTR   :1;
	u32 IDE   :1;
	u32 EXID  :18;
	u32 STID  :11;
}TI0R;

//CAN_TDT0R
typedef volatile struct 
{
	u32 DLC  :4;
	u32 Res   :12;
	u32 TIME   :16;
}TDT0R;

//CAN_TDL0R
typedef volatile struct 
{
	u32  DATA0   :8;
	u32  DATA1   :8;
	u32  DATA2   :8;
	u32  DATA3   :8;
}TDL0R;

//CAN_TDH0R
typedef volatile struct 
{
	u32  DATA4   :8;
	u32  DATA5   :8;
	u32  DATA6   :8;
	u32  DATA7   :8;
}TDH0R;

//MailBox 0
typedef volatile struct 
{
	TI0R ID_Reg;
	TDT0R DLC;
	TDL0R  Data_Low;
	TDH0R  Data_High;
}T_mailbox0;

//mailbox 1 transimmit

typedef volatile struct 
{
	u32 TXRQ  :1;
	u32 RTR   :1;
	u32 IDE   :1;
	u32 EXID  :18;
	u32 STID  :11;
}TI1R;

typedef volatile struct 
{
	u32 DLC  :4;
	u32 Res   :12;
	u32 TIME   :16;
}TDT1R;


typedef volatile struct 
{
	u32  DATA0   :8;
	u32  DATA1   :8;
	u32  DATA2   :8;
	u32  DATA3   :8;
}TDL1R;

typedef volatile struct 
{
	u32  DATA4   :8;
	u32  DATA5   :8;
	u32  DATA6   :8;
	u32  DATA7   :8;
}TDH1R;

typedef volatile struct 
{
	TI1R ID_Reg;
	TDT1R DLC;
	TDL1R  Data_Low;
	TDH1R  Data_High;
}T_mailbox1;

//mailbox 2 transimit
typedef volatile struct 
{
	u32 TXRQ  :1;
	u32 RTR   :1;
	u32 IDE   :1;
	u32 EXID  :18;
	u32 STID  :11;
}TI2R;

typedef volatile struct 
{
	u32 DLC  :4;
	u32 Res   :12;
	u32 TIME   :16;
}TDT2R;


typedef volatile struct 
{
	u32  DATA0   :8;
	u32  DATA1   :8;
	u32  DATA2   :8;
	u32  DATA3   :8;
}TDL2R;

typedef volatile struct 
{
	u32  DATA4   :8;
	u32  DATA5   :8;
	u32  DATA6   :8;
	u32  DATA7   :8;
}TDH2R;

typedef volatile struct 
{
	TI2R ID_Reg;
	TDT2R DLC;
	TDL2R  Data_Low;
	TDH2R  Data_High;
}T_mailbox2;


//Recieve Mailbox1
typedef volatile struct 
{
	u32 Res   :1;
	u32 RTR   :1;
	u32 IDE   :1;
	u32 EXID  :18;
	u32 STID  :11;
}RI0R;

typedef volatile struct 
{
	u32 DLC   :4;
	u32 Res   :4;
	u32 FMI   :8;
	u32 TIME  :16;
}RDT0R;


typedef volatile struct 
{
	u32  DATA0   :8;
	u32  DATA1   :8;
	u32  DATA2   :8;
	u32  DATA3   :8;
}RDL0R;

typedef volatile struct 
{
	u32  DATA4   :8;
	u32  DATA5   :8;
	u32  DATA6   :8;
	u32  DATA7   :8;
}RDH0R;

typedef volatile struct 
{
	RI0R ID_Reg;
	RDT0R DLC;
	RDL0R  Data_Low;
	RDH0R  Data_High;
}R_mailbox0;


typedef volatile struct 
{
	u32 Res   :1;
	u32 RTR   :1;
	u32 IDE   :1;
	u32 EXID  :18;
	u32 STID  :11;
}RI1R;

typedef volatile struct 
{
	u32 DLC   :4;
	u32 Res   :4;
	u32 FMI   :8;
	u32 TIME  :16;
}RDT1R;


typedef volatile struct 
{
	u32  DATA0   :8;
	u32  DATA1   :8;
	u32  DATA2   :8;
	u32  DATA3   :8;
}RDL1R;

typedef volatile struct 
{
	u32  DATA4   :8;
	u32  DATA5   :8;
	u32  DATA6   :8;
	u32  DATA7   :8;
}RDH1R;

typedef volatile struct 
{
	RI0R ID_Reg;
	RDT0R DLC;
	RDL0R  Data_Low;
	RDH0R  Data_High;
}R_mailbox1;


typedef volatile struct 
{
	u32  FINIT   :1;
	u32  Res     :31;
}FMR;

typedef volatile struct 
{
	u32  FBM0     :1;
	u32  FBM1     :1;
	u32  FBM2     :1;
	u32  FBM3     :1;
	u32  FBM4     :1;
	u32  FBM5     :1;
	u32  FBM6     :1;
	u32  FBM7     :1;
	u32  FBM8     :1;
	u32  FBM9     :1;
	u32  FBM10    :1;
	u32  FBM11    :1;
	u32  FBM12    :1;
	u32  FBM13    :1;
	u32  Res       :18;
}FM1R;


typedef volatile struct 
{
	u32  FSC0     :1;
	u32  FSC1     :1;
	u32  FSC2     :1;
	u32  FSC3     :1;
	u32  FSC4     :1;
	u32  FSC5     :1;
	u32  FSC6     :1;
	u32  FSC7     :1;
	u32  FSC8     :1;
	u32  FSC9     :1;
	u32  FSC10    :1;
	u32  FSC11    :1;
	u32  FSC12    :1;
	u32  FSC13    :1;
	u32  Res     :18;
} FS1R;

typedef volatile struct 
{
	u32  FFA0     :1;
	u32  FFA1     :1;
	u32  FFA2     :1;
	u32  FFA3     :1;
	u32  FFA4     :1;
	u32  FFA5     :1;
	u32  FFA6     :1;
	u32  FFA7     :1;
	u32  FFA8     :1;
	u32  FFA9     :1;
	u32  FFA10    :1;
	u32  FFA11    :1;
	u32  FFA12    :1;
	u32  FFA13    :1;
	u32  Res     :18;
} FFA1R;

typedef volatile struct 
{
	u32  FACT0     :1;
	u32  FACT1     :1;
	u32  FACT2     :1;
	u32  FACT3     :1;
	u32  FACT4     :1;
	u32  FACT5     :1;
	u32  FACT6     :1;
	u32  FACT7     :1;
	u32  FACT8     :1;
	u32  FACT9     :1;
	u32  FACT10    :1;
	u32  FACT11    :1;
	u32  FACT12    :1;
	u32  FACT13    :1;
	u32  Res     :18;
} FA1R;

typedef volatile struct 
{
	u32 CAN_F0R1;
	u32 CAN_F0R2;
	u32 CAN_F1R1;
	u32 CAN_F1R2;
	u32 CAN_F2R1;
	u32 CAN_F2R2;
	u32 CAN_F3R1;
	u32 CAN_F3R2;
	u32 CAN_F4R1;
	u32 CAN_F4R2;
	u32 CAN_F5R1;
	u32 CAN_F5R2;
	u32 CAN_F6R1;
	u32 CAN_F6R2;
	u32 CAN_F7R1;
	u32 CAN_F7R2;
	u32 CAN_F8R1;
	u32 CAN_F8R2;
	u32 CAN_F9R1;
	u32 CAN_F9R2;
	u32 CAN_F10R1;
	u32 CAN_F10R2;
	u32 CAN_F11R1;
	u32 CAN_F11R2;
	u32 CAN_F12R1;
	u32 CAN_F12R2;
	u32 CAN_F13R1;
	u32 CAN_F13R2;

} Filter_Banks;


typedef volatile struct 
{
	MCR CAN_MCR;
	MSR CAN_MSR;
	TSR CAN_TSR;
	RF0R CAN_RF0R;
	RF1R CAN_RF1R;
	IER  CAN_IER;
	ESR  CAN_ESR;
	BTR  CAN_BTR;
	u32  REServed[88];
	T_mailbox0 Transimit_Mailbox0;
	T_mailbox1 Transimit_Mailbox1;
	T_mailbox2 Transimit_Mailbox2;
	R_mailbox0 Recieve_Mailbox0  ;
	R_mailbox1 Recieve_Mailbox1  ;
	u32  REServed1[12];
	FMR CAN_FMR                  ;
	FM1R CAN_FM1R                ;
	u32  RES1;
	FS1R CAN_FS1R;
	u32  RES2;
	FFA1R CAN_FFA1R;
		u32  RES3;
	FA1R  CAN_FA1R;
	u32  RES4[8];
	Filter_Banks CAN_Filter_Banks;
}CAN_REGx;

#define CAN_REG    ((volatile CAN_REGx* )0x40006400)





#endif
