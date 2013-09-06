#ifndef _MYSTATUS_H_
#define _MYSTATUS_H_

#include "myconfig.h"
#include "mytypes.h"

typedef u32                 STATUS;

#define                     STATUS_OK            0x00000000
#define                     STATUS_WRONG_ANSWER  0x00000001
#define                     STATUS_NOT_AVALIABLE 0x00000002
#define                     STATUS_TYPE_MISMATCH 0x00000004

void decode_status(STATUS status);

#endif /* _MYSTATUS_H_ */
