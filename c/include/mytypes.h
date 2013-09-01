#include "stdint.h"

#ifndef _MYTYPES_H_
#define _MYTYPES_H_

#include "myconfig.h"

typedef unsigned char       u8;
typedef unsigned short      u16;

typedef char                s8;
typedef short               s16;

typedef unsigned char       boolean;

/*******************************************************************************
 *
 * Independent types
 *
 ******************************************************************************/

/* Logical defines and NULL */

#ifdef FALSE
#undef FALSE
#endif
#define FALSE               (1 == 0)

#ifdef TRUE
#undef TRUE
#endif
#define TRUE                (1 == 1)

#ifndef NULL
#define NULL                (void *) 0
#endif

/* STDINT will be my first choice */

#ifdef _STDINT_H

typedef uint32_t            u32;
typedef uint64_t            u64;

typedef int32_t             s32;
typedef int64_t             s64;
#else

/*
 * As shown in the table below, unsigned 32 bits integer is not very easy to
 * get. I still don't find a way guarantee my program use a real 32-bits u32,
 * I will just use unsigned int instead here, except stdint.h is avalible.
 *
 * Datatype  LP64 ILP64 LLP64 ILP32 LP32 16bit                                                                                                           
 * char      8    8     8     8     8    8                                                                                                               
 * short     16   16    16    16    16   16                                                                                                              
 * _int32         32                                                                                                                                     
 * int       32   64    32    32    16   16                                                                                                              
 * long      64   64    32    32    32   32                                                                                                              
 * long long            64    64                                                                                                                         
 * pointer   64   64    64    32    32   32 
 *
 * Well, mostly, 64 bits unix like system will use LP64, and 64 bits windows
 * prefer LLP64, unsigned int will be both 32 bits. And stdint.h is avalible
 * only in C99.
 */

typedef unsigned int        u32;
typedef int                 s32;

/* u64 is defined in the same way in linux, see asm/types.h*/

typedef unsigned long long  u64;
typedef long long           s64;

#endif /* _STDINT_H */

#endif /* _MYTYPES_H_*/
