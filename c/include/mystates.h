#ifndef _MYSTATES_H_
#define _MYSTATES_H_

#include "mytypes.h"

typedef u32                 STATE;

#define                     STATE_OK            0x00000000
#define                     STATE_WRONG_ANSWER  0x00000001
#define                     STATE_NOT_AVALIABLE 0x00000002
#define                     STATE_TYPE_MISMATCH 0x00000004

void decode_state(STATE state);

#endif /* _MYSTATES_H_ */
