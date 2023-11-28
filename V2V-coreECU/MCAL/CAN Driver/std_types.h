


#ifndef SERVIES_STD_TYPES_H_
#define SERVIES_STD_TYPES_H_


typedef signed char  					          	s8;
typedef unsigned char 				         		u8;


typedef signed short int 			        		s16;
typedef unsigned short int 					      u16;
typedef signed long 							        s32;
typedef unsigned long 						        u32;
typedef signed long long int  				    s64;
typedef unsigned long long int  			    u64;



typedef volatile signed char  				    vs8;
typedef volatile unsigned char 				    vu8;
typedef volatile signed short int 		    vs16;
typedef volatile unsigned short int 	    vu16;
typedef volatile signed long int 			    vs32;
typedef volatile unsigned long int 	      vu32;
typedef volatile signed long long int  	  vs64;
typedef volatile unsigned  long long int  vu64;


typedef float								              f32;
typedef double								            f62;
typedef long double 						          f92;

typedef unsigned char                     boolean;


typedef unsigned char*                    pu8;
typedef unsigned long*                    pu32;





#ifndef   TRUE
#define   TRUE                    1
#endif


#ifndef   FALSE
#define   FALSE                  	0
#endif


#ifndef	  STR_NULL
#define   STR_NULL	            '\0'
#endif

#ifndef	  PTR_NULL
#define   PTR_NULL	            ((void*)0)
#endif

#endif /* SERVIES_STD_TYPES_H_ */
