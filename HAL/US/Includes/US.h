#ifndef US_H_
#define US_H_

#include "std_types.h"
#include "common_macros.h"

void US_voidInit(void);
void US_voidGetUSSensorDistance(u16 *Ptr_u16DistanceCM);
void US_voidSetICUTime(void);
void US_voidGetTimeStatus(u8* Ptr_u8Flag);
void US_voidGetICU_Distance(u16 *Ptr_u16DistanceCM);
void US_voidGetUSSensorDistanceAsync(u16 *Ptr_u16DistanceCM);


#endif
