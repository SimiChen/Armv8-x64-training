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

extern void __Circs(int32_t* dst, int16_t* s1, int16_t* s2, int16_t len);

void __Circs_c(int32_t* dst, int16_t* s1, int16_t* s2, int16_t len)
{
  int i,j;
  int32_t acc;

  for (i=0; i<len; i++)
  {
    acc=0;
    for (j=i; j<len; j++)
    {
      acc+=s1[j]*s2[j-i];
      if (acc<MIN31) acc=MIN31;
      if (acc>MAX31) acc=MAX31;
    }
    dst[i]=acc<<1;
  }
}

extern void __InvCirc(int32_t* dst, int16_t* s1, int16_t* s2, int16_t len);

void __InvCirc_c(int32_t* dst, int16_t* s1, int16_t* s2, int16_t len)
{
  int i,j;
  int32_t acc;
  for (i=0; i<len; i++)
  {
    acc=0;
    for (j=0; j<=i; j++) acc+=s1[j]*s2[i-j];
    dst[i]=acc<<1;
  }
}

extern void __InvCircs(int32_t* dst, int16_t* s1, int16_t* s2, int16_t len);

void __InvCircs_c(int32_t* dst, int16_t* s1, int16_t* s2, int16_t len)
{
  int i,j;
  int32_t acc;
  for (i=0; i<len; i++)
  {
    acc=0;
    for (j=0; j<=i; j++)
    {
      acc+=s1[j]*s2[i-j];
      if (acc<MIN31) acc=MIN31;
      if (acc>MAX31) acc=MAX31;
    }
    dst[i]=acc<<1;
  }
}

extern void __vShlw(int16_t* v1, int16_t* v2, int16_t nsh, int16_t size);

void __vShlw_c(int16_t* v1, int16_t* v2, int16_t nsh, int16_t size)
{
  int16_t i;
  if (nsh>=0)
    for (i=0; i<size; i++) v1[i]=v2[i]<<nsh;
  else
    for (i=0; i<size; i++) v1[i]=v2[i]>>(-nsh);
}

extern void __vShrw(int16_t* v1, int16_t* v2, int16_t nsh, int16_t size);

void __vShrw_c(int16_t* v1, int16_t* v2, int16_t nsh, int16_t size)
{
  int16_t i;
  if (nsh>=0)
    for (i=0; i<size; i++) v1[i]=v2[i]>>nsh;
  else
    for (i=0; i<size; i++) v1[i]=v2[i]<<(-nsh);
}

extern void __vShldw(int32_t* v1, int32_t* v2, int16_t nsh, int16_t size);

void __vShldw_c(int32_t* v1, int32_t* v2, int16_t nsh, int16_t size)
{
  int16_t i;
  if (nsh>=0)
    for (i=0; i<size; i++) v1[i]=v2[i]<<nsh;
  else
    for (i=0; i<size; i++) v1[i]=v2[i]>>(-nsh);
}

extern void __vShrdw(int32_t* v1, int32_t* v2, int16_t nsh, int16_t size);

void __vShrdw_c(int32_t* v1, int32_t* v2, int16_t nsh, int16_t size)
{
  int16_t i;
  if (nsh>=0)
    for (i=0; i<size; i++) v1[i]=v2[i]>>nsh;
  else
    for (i=0; i<size; i++) v1[i]=v2[i]<<(-nsh);
}

extern void __vRound(int16_t* v1, int32_t* v2, int16_t size);

void __vRound_c(int16_t* v1, int32_t* v2, int16_t size)
{
  int i;
  for (i=0; i<size; i++)
    v1[i]=(int16_t)((v2[i]+(int32_t)0x00008000)>>16);
}

extern int32_t __ConvFirIir(int16_t* v1, int16_t* v2, int32_t acc);

int32_t __ConvFirIir_c(int16_t* v1, int16_t* v2, int32_t acc)
{
  int i;
  for (i=0; i<10; i++)
    acc+=((int32_t)v1[i]*(int32_t)v2[i])<<1;
  for (i=10; i<20; i++)
    acc-=((int32_t)v1[i]*(int32_t)v2[i])<<1;
  return acc;
}

extern void __vMovw(int16_t* v1, int16_t* v2, int16_t size);

extern void __vMovdw(int32_t* v1, int32_t* v2, int16_t size);

extern void __vSetw(int16_t* v1, int16_t c, int16_t size);

extern void __vSetdw(int32_t* v1, int32_t c, int16_t size);

void __vMovw_c(int16_t* v1, int16_t* v2, int16_t size)
{
  int i;
  for (i=0; i<size; i++) v1[i]=v2[i];
}

void __vMovdw_c(int32_t* v1, int32_t* v2, int16_t size)
{
  int i;
  for (i=0; i<size; i++) v1[i]=v2[i];
}

void __vSetw_c(int16_t* v1, int16_t c, int16_t size)
{
  int i;
  for (i=0; i<size; i++) v1[i]=c;
}

void __vSetdw_c(int32_t* v1, int32_t c, int16_t size)
{
  int i;
  for (i=0; i<size; i++) v1[i]=c;
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
    int16_t size = 20;
    int16_t p1[size], p2[size];
    int32_t acc, p3[size];
    int32_t res, res_c;
    int32_t ret_32[size], ret_32_c[size];
    int16_t ret_16[size], ret_16_c[size];
    
    for (int i = 0; i < size; i++) {
        p1[i] = random_16();
        p2[i] = random_16();
        p3[i] = random_32();
    }
    acc = random_32();


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
    res = __ConvFirIir(p1,p2,acc);
    res_c = __ConvFirIir_c(p1,p2,acc);
    
    printf("res_c = %x\n",res_c);
    printf("res = %x\n",res);
    */
    
    int16_t p1_c[size];
    //int16_t nsh = rand()%32 - 16;
    //printf("nsh = %d\n", nsh);
    memcpy(p1_c, p1, sizeof(int16_t)*size);
    __vSetdw(ret_32, p3[0], size);
    __vSetdw_c(ret_32_c, p3[0], size);
    for (int i = 0; i < size; i++) {
        printf("0x%x, ", ret_32[i]);
        printf("0x%x, ", ret_32_c[i]);
        printf("\n");
        if (ret_32[i] != ret_32_c[i]) {
            printf("Error\n");
            return -1;
        }
    }
    
}
