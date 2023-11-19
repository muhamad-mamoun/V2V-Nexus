






#ifndef PWM_PRV_H
#define PWM_PRV_H


#define TIM4_BASE          0x40000800  
#define TIM3_BASE          0x40000400 
#define TIM2_BASE          0x40000000  
									         
									         
#define TIMx_CR1           0x00
#define TIMx_CR2           0x04
#define TIMx_SMCR          0x08
#define TIMx_DIER          0x0C
#define TIMx_SR            0x10
#define TIMx_EGR           0x14
#define TIMx_CCMR1         0x18
#define TIMx_CCMR2         0x1C
#define TIMx_CCER          0x20
#define TIMx_CNT           0x24
#define TIMx_PSC           0x28
#define TIMx_ARR           0x2C
#define TIMx_CCR1          0x34
#define TIMx_CCR2          0x38
#define TIMx_CCR3          0x3C
#define TIMx_CCR4          0x40
#define TIMx_DCR           0x48
#define TIMx_DMAR          0x4C

#define REG(TIM,OFFSET)    (*(vu32*)(TIM+OFFSET))


//////////////////////////////

#define UIFREMAP  11
#define CKD0      8 
#define CKD1      9 
#define ARPE      7
#define CMS0      5
#define CMS6      6
#define DIR       4
#define OPM       3
#define URS       2
#define UDIS      1
#define CEN       0



#define TI1S     7
#define MMS0     4
#define MMS1     5
#define MMS2     6
#define CCDS     3




#define SMS3       16
#define ETP        15
#define ECE        14
#define ETPS0      12
#define ETPS1      13
#define ETF0       8
#define ETF1       9
#define ETF2       10
#define ETF3       11
#define MSM        7
#define TS0        4
#define TS1        5
#define TS2        6
#define OCCS       3
#define SMS0       0
#define SMS1       1
#define SMS2       2



#define TDE       14
#define COMDE     13
#define CC4DE     12
#define CC3DE     11
#define CC2DE     10
#define CC1DE     9
#define UDE       8
#define TIE       6
#define CC4IE     4
#define CC3IE     3
#define CC2IE     2
#define CC1IE     1
#define UIE       0


#define CC4OF      12
#define CC3OF      11
#define CC2OF      10
#define CC1OF      9
#define TIF        6
#define CC4IF      4
#define CC3IF      3
#define CC2IF      2
#define CC1IF      1
#define UIF        0


#define CC4NP    15
#define CC4P     13
#define CC4E     12
#define CC3NP    11
#define CC3P     9
#define CC3E     8
#define CC2NP    7
#define CC2P     5
#define CC2E     4
#define CC1NP    3
#define CC1P     1
#define CC1E     0




#define OC1PE  3
#define OC2PE  11
#define OC3PE  3
#define OC4PE  11
#define OC1M   4
#define OC2M   12
#define OC3M   4
#define OC4M   12
#define UG     0
#define CMS1   6
#define CMS0   5

#define PWM_MODE_1          110
#define PWM_MODE_2          111
#define MASK_MODE           7  


#define PWM_CENTER_ALIGNED   0
#define PWM_EDGE_ALIGNED     1

#define DUTY_MAX             100

#endif


