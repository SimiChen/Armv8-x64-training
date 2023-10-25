#include "typedef.h"
#include <stdio.h>
#include <sys/time.h> 
#include <time.h> 
#include <unistd.h>  
#include <stdlib.h>
#include <string.h>



#define MAX31	(int)0x3fffffff
#define MIN31	(int)0xc0000000

extern Word32 __ConvAdd(Word16* p1, Word16* p2, Word16 size, Word32 acc);

Word32 __ConvAdd_c(Word16* p1, Word16* p2, Word16 size, Word32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
    acc+=(Word32)p1[j]*(Word32)p2[j];
  return acc<<1;
}

extern Word32 __ConvSub(Word16* p1, Word16* p2, Word16 size, Word32 acc);

Word32 __ConvSub_c(Word16* p1, Word16* p2, Word16 size, Word32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
    acc-=(Word32)p1[j]*(Word32)p2[j];
  return acc<<1;
}

extern Word32 __ConvAdds(Word16* p1, Word16* p2, Word16 size, Word32 acc);

Word32 __ConvAdds_c(Word16* p1, Word16* p2, Word16 size, Word32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
  {
    acc+=(Word32)p1[j]*(Word32)p2[j];
    printf("acc=%lx\n, j=%d\n",acc,j);
    if (acc>MAX31) acc=MAX31;
    else if (acc<MIN31) acc=MIN31;
    printf("acc=%lx\n, j=%d\n",acc,j);
  }
  return acc<<1;
}

extern Word32 __ConvSubs(Word16* p1, Word16* p2, Word16 size, Word32 acc);

Word32 __ConvSubs_c(Word16* p1, Word16* p2, Word16 size, Word32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
  {
    acc-=(Word32)p1[j]*(Word32)p2[j];
    if (acc>MAX31) acc=MAX31;
    else if (acc<MIN31) acc=MIN31;
  }
  return acc<<1;
}

extern Word32 __ConvAddh(Word16* p1, Word16* p2, Word16 size, Word32 acc);

Word32 __ConvAddh_c(Word16* p1, Word16* p2, Word16 size, Word32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
    acc+=(Word32)p1[j]*(Word32)p2[j];
  return acc;
}

extern Word32 __ConvSubh(Word16* p1, Word16* p2, Word16 size, Word32 acc);

Word32 __ConvSubh_c(Word16* p1, Word16* p2, Word16 size, Word32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
    acc-=(Word32)p1[j]*(Word32)p2[j];
  return acc;
}

extern Word32 __ConvAddhs(Word16* p1, Word16* p2, Word16 size, Word32 acc);

Word32 __ConvAddhs_c(Word16* p1, Word16* p2, Word16 size, Word32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
  {
    acc+=(Word32)p1[j]*(Word32)p2[j];
    if (acc>MAX31) acc=MAX31;
    else if (acc<MIN31) acc=MIN31;
  }
  return acc;
}

extern Word32 __ConvSubhs(Word16* p1, Word16* p2, Word16 size, Word32 acc);

Word32 __ConvSubhs_c(Word16* p1, Word16* p2, Word16 size, Word32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
  {
    acc-=(Word32)p1[j]*(Word32)p2[j];
    if (acc>MAX31) acc=MAX31;
    else if (acc<MIN31) acc=MIN31;
  }
  return acc;
}

extern Word32 __ConvAddhS(Word16* p1, Word16* p2, Word16 size, Word32 acc);

Word32 __ConvAddhS_c(Word16* p1, Word16* p2, Word16 size, Word32 acc)
{
  int j;
  Word32 m;

  acc>>=1;
  for (j=0; j<size; j++)
  {
    m=(Word32)p1[j]*(Word32)p2[j];
    if (((acc^m)&(int)0x80000000)==0L)
    {
      acc+=m;
      if ((acc^m)&(int)0x80000000)
        acc = m<0L? (int)0x80000000:(int)0x7fffffff;
    }
    else acc+=m;
  }
  return acc;
}

extern void __vMulr(Word16* v1, Word16* v2, Word16 size);

void __vMulr_c(Word16* v1, Word16* v2, Word16 size)
{
  int j;
  for (j=0; j<size; j++)
    v1[j]=(Word16)(((Word32)v1[j]*(Word32)v2[j]+(Word32)0x00004000)>>15);
}

extern void __vAdd(Word16* v1, Word16* v2, Word16 size);

void __vAdd_c(Word16* v1, Word16* v2, Word16 size)
{
  int j;
  for (j=0; j<size; j++) v1[j]+=v2[j];
}

extern void __vSub(Word16* v1, Word16* v2, Word16 size);

void __vSub_c(Word16* v1, Word16* v2, Word16 size)
{
  int j;
  for (j=0; j<size; j++) v1[j]-=v2[j];
}

extern void __cMulr(Word16* v, Word16 coef, Word16 size);

void __cMulr_c(Word16* v, Word16 coef, Word16 size)
{
  int j;
  for (j=0; j<size; j++)
    v[j]=(Word16)(((Word32)v[j]*(Word32)coef+(Word32)0x00004000)>>15);
}

extern void __cAdd(Word16* v, Word16 a, Word16 size);

void __cAdd_c(Word16* v, Word16 a, Word16 size)
{
  int j;
  for (j=0; j<size; j++) v[j]+=a;
}

extern void __cSub(Word16* v, Word16 a, Word16 size);

void __cSub_c(Word16* v, Word16 a, Word16 size)
{
  int j;
  for (j=0; j<size; j++) v[j]-=a;
}

extern void __Circ(Word32* dst, Word16* s1, Word16* s2, Word16 len);

void __Circ_c(Word32* dst, Word16* s1, Word16* s2, Word16 len)
{
  int i,j;
  Word32 acc;

  for (i=0; i<len; i++)
  {
    acc=0;
    for (j=i; j<len; j++) acc+=s1[j]*s2[j-i];
    dst[i]=acc<<1;
  }
}

Word16 random_16() {
    return (Word16)rand()%65535 - 32767;
}

Word32 random_32() {
    Word32 random_number = ((Word32)rand() << 16) | rand();
    return (Word32)random_number%4294967295 - 2147483647;
}

int main (){
    srand((unsigned)time( NULL ) );
    Word16 p1[16], p2[16];
    Word32 acc;
    //Word16 p1[6] = {0x1233,0x123,0x3321,0x123,0x123,-0x3321};
    //Word16 p2[6] = {0x1123,0x112,0xabc,0x1123,-0x112,0xabc};
    //Word32 acc = 0x7ff31233;
    Word16 size = 16;
    Word32 res, res_c;
    Word32 ret[16], ret_c[16];
    
    for (int i = 0; i < size; i++) {
        p1[i] = random_16();
        p2[i] = random_16();
    }
    acc = random_32();

    /*
    Word16 p1[] = {0x7e87, 0xde1f, 0xae4d, 0x53a5, 0x8c40, 0x89c4, 0xa02d, 0x2f2e, 0xc3d8, 0xa511, 0xb81e, 0x40df, 0x749f, 0x980f, 0x2a46, 0xa6da};
    Word16 p2[] = {0x8a1a, 0x2b8c, 0x756e, 0xc2d0, 0x349e, 0xbc2b, 0x2726, 0xf24d, 0xa485, 0x509a, 0x407d, 0xbf6e, 0xfdc8, 0x726c, 0xce14, 0x28cc};
    Word32 acc = -117597357;*/


    for (int i = 0; i < size; i++) {
        printf("0x%x, ", p1[i]);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("0x%x, ", p2[i]);
    }
    printf("\n");
    printf("acc = 0x%lx\n", acc);
    /*
    res = __ConvAddhS(p1,p2,size,acc);
    res_c = __ConvAddhS_c(p1,p2,size,acc);
    
    printf("res_c = %lx\n",res_c);
    printf("res = %lx\n",res);
    */
    Word16 p1_c[16];
    memcpy(p1_c, p1, sizeof(Word16)*size);
    __cSub(p1, p2[0], size);
    __cSub_c(p1_c, p2[0], size);
    for (int i = 0; i < size; i++) {
        printf("0x%x, ", p1[i]);
        printf("0x%x, ", p1_c[i]);
        printf("\n");
        if (p1[i] != p1_c[i]) {
            printf("Error\n");
            return -1;
        }
    }
}
