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


#define CONC(B7,B6,B5,B4,B3,B2,B1,B0)        CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)
#define CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)   (0b##B7##B6##B5##B4##B3##B2##B1##B0)

#endif /* SERVIES_BIT_MATH_H_ */
