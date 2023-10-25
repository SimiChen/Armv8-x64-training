
#ifndef _SP_TYPEDEF_H
#define _SP_TYPEDEF_H




#ifndef NULL
#define NULL 0
#endif

/*
 * Types definitions 
 */
//typedef  short int   Flag  ;
typedef long  int INT64;
typedef long  int INT32;
typedef double    FLOAT64;
typedef short int INT16;
typedef char Word8;
typedef short int Word16;	/* 16 bit "register" (sw*) */
typedef long int Word32;	/* 32 bit "accumulator" (L_*) */
#ifndef	OPT_PREC
typedef long long Word64;
#else
typedef long long Word64;
#endif
typedef char s8;
typedef short s16;
typedef long s32;
#ifndef OPT_PREC
typedef long long  s64;
#else
typedef long long s64;
#endif
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef unsigned char  boolean;
typedef unsigned int bit_field;
typedef unsigned short u16_bit;


//typedef   long long Word64;
typedef double Word40;
//typedef  long    Word32;
//#typedef  short   Word16;
//#typedef  char    Word8;
typedef  short   Flag;

//typedef  unsigned short   U16;
//typedef  unsigned long    U32;

typedef unsigned long long  UINT64;

//#typedef	unsigned int U32;
//#typedef	unsigned short U16;
//#typedef unsigned char U8;

#define MAX_64 (Word64)0x7fffffffffffffffL
#define MIN_64 (Word64)0x8000000000000000L

#define MAX_32 (Word32)0x7fffffffL
#define MIN_32 (Word32)0x80000000L

#define MAX_16 (Word16)0x7fff
#define MIN_16 (Word16)0x8000

#define LW_SIGN (long)0x80000000       /* sign bit */
#define LW_MIN (long)0x80000000
#define LW_MAX (long)0x7fffffff

#define SW_SIGN (short)0x8000          /* sign bit for Word16 type */
#define SW_MIN (short)0x8000           /* smallest Ram */
#define SW_MAX (short)0x7fff           /* largest Ram */


typedef unsigned short UNS_Word16;

#endif
