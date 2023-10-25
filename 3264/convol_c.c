#include "typedef.h"
#include <stdio.h>
#include <sys/time.h> 
#include <time.h> 
#include <unistd.h>  
#include <stdlib.h>
#include <string.h>



#define MAX31	(int)0x3fffffff
#define MIN31	(int)0xc0000000

extern int32_t __ConvAdd(int16_t* p1, int16_t* p2, int16_t size, int32_t acc);

int32_t __ConvAdd_c(int16_t* p1, int16_t* p2, int16_t size, int32_t acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
    acc+=(int32_t)p1[j]*(int32_t)p2[j];
  return acc<<1;
}

extern int32_t __ConvSub(int16_t* p1, int16_t* p2, int16_t size, int32_t acc);

int32_t __ConvSub_c(int16_t* p1, int16_t* p2, int16_t size, int32_t acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
    acc-=(int32_t)p1[j]*(int32_t)p2[j];
  return acc<<1;
}

extern int32_t __ConvAdds(int16_t* p1, int16_t* p2, int16_t size, int32_t acc);

int32_t __ConvAdds_c(int16_t* p1, int16_t* p2, int16_t size, int32_t acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
  {
    acc+=(int32_t)p1[j]*(int32_t)p2[j];
    printf("acc=%x\n, j=%d\n",acc,j);
    if (acc>MAX31) acc=MAX31;
    else if (acc<MIN31) acc=MIN31;
    printf("acc=%x\n, j=%d\n",acc,j);
  }
  return acc<<1;
}

extern int32_t __ConvSubs(int16_t* p1, int16_t* p2, int16_t size, int32_t acc);

int32_t __ConvSubs_c(int16_t* p1, int16_t* p2, int16_t size, int32_t acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
  {
    acc-=(int32_t)p1[j]*(int32_t)p2[j];
    if (acc>MAX31) acc=MAX31;
    else if (acc<MIN31) acc=MIN31;
  }
  return acc<<1;
}

extern int32_t __ConvAddh(int16_t* p1, int16_t* p2, int16_t size, int32_t acc);

int32_t __ConvAddh_c(int16_t* p1, int16_t* p2, int16_t size, int32_t acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
    acc+=(int32_t)p1[j]*(int32_t)p2[j];
  return acc;
}

extern int32_t __ConvSubh(int16_t* p1, int16_t* p2, int16_t size, int32_t acc);

int32_t __ConvSubh_c(int16_t* p1, int16_t* p2, int16_t size, int32_t acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
    acc-=(int32_t)p1[j]*(int32_t)p2[j];
  return acc;
}

extern int32_t __ConvAddhs(int16_t* p1, int16_t* p2, int16_t size, int32_t acc);

int32_t __ConvAddhs_c(int16_t* p1, int16_t* p2, int16_t size, int32_t acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
  {
    acc+=(int32_t)p1[j]*(int32_t)p2[j];
    if (acc>MAX31) acc=MAX31;
    else if (acc<MIN31) acc=MIN31;
  }
  return acc;
}

extern int32_t __ConvSubhs(int16_t* p1, int16_t* p2, int16_t size, int32_t acc);

int32_t __ConvSubhs_c(int16_t* p1, int16_t* p2, int16_t size, int32_t acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
  {
    acc-=(int32_t)p1[j]*(int32_t)p2[j];
    if (acc>MAX31) acc=MAX31;
    else if (acc<MIN31) acc=MIN31;
  }
  return acc;
}

extern int32_t __ConvAddhS(int16_t* p1, int16_t* p2, int16_t size, int32_t acc);

int32_t __ConvAddhS_c(int16_t* p1, int16_t* p2, int16_t size, int32_t acc)
{
  int j;
  int32_t m;

  acc>>=1;
  for (j=0; j<size; j++)
  {
    m=(int32_t)p1[j]*(int32_t)p2[j];
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

extern void __vMulr(int16_t* v1, int16_t* v2, int16_t size);

void __vMulr_c(int16_t* v1, int16_t* v2, int16_t size)
{
  int j;
  for (j=0; j<size; j++)
    v1[j]=(int16_t)(((int32_t)v1[j]*(int32_t)v2[j]+(int32_t)0x00004000)>>15);
}

extern void __vAdd(int16_t* v1, int16_t* v2, int16_t size);

void __vAdd_c(int16_t* v1, int16_t* v2, int16_t size)
{
  int j;
  for (j=0; j<size; j++) v1[j]+=v2[j];
}

extern void __vSub(int16_t* v1, int16_t* v2, int16_t size);

void __vSub_c(int16_t* v1, int16_t* v2, int16_t size)
{
  int j;
  for (j=0; j<size; j++) v1[j]-=v2[j];
}

extern void __cMulr(int16_t* v, int16_t coef, int16_t size);

void __cMulr_c(int16_t* v, int16_t coef, int16_t size)
{
  int j;
  for (j=0; j<size; j++)
    v[j]=(int16_t)(((int32_t)v[j]*(int32_t)coef+(int32_t)0x00004000)>>15);
}

extern void __cAdd(int16_t* v, int16_t a, int16_t size);

void __cAdd_c(int16_t* v, int16_t a, int16_t size)
{
  int j;
  for (j=0; j<size; j++) v[j]+=a;
}

extern void __cSub(int16_t* v, int16_t a, int16_t size);

void __cSub_c(int16_t* v, int16_t a, int16_t size)
{
  int j;
  for (j=0; j<size; j++) v[j]-=a;
}

extern void __Circ(int32_t* dst, int16_t* s1, int16_t* s2, int16_t len);

void __Circ_c(int32_t* dst, int16_t* s1, int16_t* s2, int16_t len)
{
  int i,j;
  int32_t acc;

  for (i=0; i<len; i++)
  {
    acc=0;
    for (j=i; j<len; j++) acc+=s1[j]*s2[j-i];
    dst[i]=acc<<1;
  }
}

int16_t random_16() {
    return (int16_t)rand()%65535 - 32767;
}

int32_t random_32() {
    int32_t random_number = ((int32_t)rand() << 16) | rand();
    return (int32_t)random_number%4294967295 - 2147483647;
}

int main (){
    srand((unsigned)time( NULL ) );
    int16_t p1[16], p2[16];
    int32_t acc;
    //int16_t p1[6] = {0x1233,0x123,0x3321,0x123,0x123,-0x3321};
    //int16_t p2[6] = {0x1123,0x112,0xabc,0x1123,-0x112,0xabc};
    //int32_t acc = 0x7ff31233;
    int16_t size = 16;
    int32_t res, res_c;
    int ret[16], ret_c[16];
    
    for (int i = 0; i < size; i++) {
        p1[i] = random_16();
        p2[i] = random_16();
    }
    acc = random_32();

    /*
    int16_t p1[] = {0x7e87, 0xde1f, 0xae4d, 0x53a5, 0x8c40, 0x89c4, 0xa02d, 0x2f2e, 0xc3d8, 0xa511, 0xb81e, 0x40df, 0x749f, 0x980f, 0x2a46, 0xa6da};
    int16_t p2[] = {0x8a1a, 0x2b8c, 0x756e, 0xc2d0, 0x349e, 0xbc2b, 0x2726, 0xf24d, 0xa485, 0x509a, 0x407d, 0xbf6e, 0xfdc8, 0x726c, 0xce14, 0x28cc};
    int32_t acc = -117597357;*/


    for (int i = 0; i < size; i++) {
        printf("0x%x, ", p1[i]);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("0x%x, ", p2[i]);
    }
    printf("\n");
    printf("acc = 0x%x\n", acc);
    /*
    res = __ConvAddhS(p1,p2,size,acc);
    res_c = __ConvAddhS_c(p1,p2,size,acc);
    
    printf("res_c = %x\n",res_c);
    printf("res = %x\n",res);
    */
    int16_t p1_c[16];
    memcpy(p1_c, p1, sizeof(int16_t)*size);
    __Circ(ret, p1, p2, size);
    __Circ_c(ret_c, p1_c, p2, size);
    for (int i = 0; i < size; i++) {
        printf("0x%x, ", ret[i]);
        printf("0x%x, ", ret_c[i]);
        printf("\n");
        if (ret[i] != ret_c[i]) {
            printf("Error\n");
            return -1;
        }
    }
}
