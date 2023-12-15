#ifndef SERVIES_BIT_MATH_H_
#define SERVIES_BIT_MATH_H_



#define SET_BIT(Reg,Bit)					(Reg|=(1<<Bit))
#define CLR_BIT(Reg,Bit)					(Reg&=(~(1<<Bit)))
#define GET_BIT(Reg,Bit)					((Reg>>Bit)&1)
#define TGL_BIT(Reg,Bit)					(Reg^=(1<<Bit))
#define RSHFT_REG(Reg,No)					(Reg>>=No)
#define LSHFT_REG(Reg,No)					(Reg<<=No)
#define CRSHFT_REG(Reg,No)					(Reg=(Reg>>No)|(Reg<<(sizeof(Reg)*8-No)))
#define CLSHFT_REG(Reg,No)					(Reg=(Reg<<No)|(Reg>>(sizeof(Reg)*8-No)))
#define ASSIGN_REG(Reg,Value)				(Reg=Value)
#define SET_REG(Reg)						(Reg=~0)
#define CLR_REG(Reg)						(Reg&=0)
#define TGL_REG(Reg)						(Reg=~Reg)
#define TGL_NO_ASSIGN(Reg,Bit)              ((Reg^(1<<Bit)))

#define WRITE_BIT(reg,bit,value) (reg=reg&~(1<<bit)|(value<<bit))


#define FLASH_BASE_ADDRESS           0x00000000
#define SRAM_BASE_ADDRESS            0x20000000
#define PERIPHERAL_BASE_ADDRESS      0x40000000
#define SRAM_BBR_BASE_ADDRESS        0x20000000
#define SRAM_BBA_BASE_ADDRESS        0x22000000
#define PERIPHERAL_BBR_BASE_ADDRESS  0x40000000
#define PERIPHERAL_BBA_BASE_ADDRESS  0x42000000

#define BIT_BAND(reg,bit)            *((vu32*)(PERIPHERAL_BBA_BASE_ADDRESS+(((vu32)reg-PERIPHERAL_BASE_ADDRESS)*32+(bit*4))))


#define SET_BIT_BAND(reg,bit)         BIT_BAND(reg,bit) = 1
#define CLR_BIT_BAND(reg,bit)         BIT_BAND(reg,bit) = 0

#define CONC(B7,B6,B5,B4,B3,B2,B1,B0)        CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)
#define CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)   (0b##B7##B6##B5##B4##B3##B2##B1##B0)

#endif /* SERVIES_BIT_MATH_H_ */
