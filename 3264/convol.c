#include "convol.h"

#define MAX31	(WORD32)0x3fffffff
#define MIN31	(WORD32)0xc0000000


WORD32 __ConvAdd(WORD16* p1, WORD16* p2, WORD16 size, WORD32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
    acc+=(WORD32)p1[j]*(WORD32)p2[j];
  return acc<<1;
}

WORD32 __ConvSub(WORD16* p1, WORD16* p2, WORD16 size, WORD32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
    acc-=(WORD32)p1[j]*(WORD32)p2[j];
  return acc<<1;
}

WORD32 __ConvAdds(WORD16* p1, WORD16* p2, WORD16 size, WORD32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
  {
    acc+=(WORD32)p1[j]*(WORD32)p2[j];
    if (acc>MAX31) acc=MAX31;
    else if (acc<MIN31) acc=MIN31;
  }
  return acc<<1;
}

WORD32 __ConvSubs(WORD16* p1, WORD16* p2, WORD16 size, WORD32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
  {
    acc-=(WORD32)p1[j]*(WORD32)p2[j];
    if (acc>MAX31) acc=MAX31;
    else if (acc<MIN31) acc=MIN31;
  }
  return acc<<1;
}

WORD32 __ConvAddh(WORD16* p1, WORD16* p2, WORD16 size, WORD32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
    acc+=(WORD32)p1[j]*(WORD32)p2[j];
  return acc;
}

WORD32 __ConvSubh(WORD16* p1, WORD16* p2, WORD16 size, WORD32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
    acc-=(WORD32)p1[j]*(WORD32)p2[j];
  return acc;
}

WORD32 __ConvAddhs(WORD16* p1, WORD16* p2, WORD16 size, WORD32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
  {
    acc+=(WORD32)p1[j]*(WORD32)p2[j];
    if (acc>MAX31) acc=MAX31;
    else if (acc<MIN31) acc=MIN31;
  }
  return acc;
}

WORD32 __ConvSubhs(WORD16* p1, WORD16* p2, WORD16 size, WORD32 acc)
{
  int j;

  acc>>=1;
  for (j=0; j<size; j++)
  {
    acc-=(WORD32)p1[j]*(WORD32)p2[j];
    if (acc>MAX31) acc=MAX31;
    else if (acc<MIN31) acc=MIN31;
  }
  return acc;
}

WORD32 __ConvAddhS(WORD16* p1, WORD16* p2, WORD16 size, WORD32 acc)
{
  int j;
  WORD32 m;

  acc>>=1;
  for (j=0; j<size; j++)
  {
    m=(WORD32)p1[j]*(WORD32)p2[j];
    if (((acc^m)&(WORD32)0x80000000)==0L)
    {
      acc+=m;
      if ((acc^m)&(WORD32)0x80000000)
        acc = m<0L? (WORD32)0x80000000:(WORD32)0x7fffffff;
    }
    else acc+=m;
  }
  return acc;
}

void   __vMulr(WORD16* v1, WORD16* v2, WORD16 size)
{
  int j;
  for (j=0; j<size; j++)
    v1[j]=(WORD16)(((WORD32)v1[j]*(WORD32)v2[j]+(WORD32)0x00004000)>>15);
}

void __vAdd(WORD16* v1, WORD16* v2, WORD16 size)
{
  int j;
  for (j=0; j<size; j++) v1[j]+=v2[j];
}

void __vSub(WORD16* v1, WORD16* v2, WORD16 size)
{
  int j;
  for (j=0; j<size; j++) v1[j]-=v2[j];
}

void __cMulr(WORD16* v, WORD16 coef, WORD16 size)
{
  int j;
  for (j=0; j<size; j++)
    v[j]=(WORD16)(((WORD32)v[j]*(WORD32)coef+(WORD32)0x00004000)>>15);
}

void __cAdd(WORD16* v, WORD16 a, WORD16 size)
{
  int j;
  for (j=0; j<size; j++) v[j]+=a;
}

void __cSub(WORD16* v, WORD16 a, WORD16 size)
{
  int j;
  for (j=0; j<size; j++) v[j]-=a;
}

void __Circ(WORD32* dst, WORD16* s1, WORD16* s2, WORD16 len)
{
  int i,j;
  WORD32 acc;

  for (i=0; i<len; i++)
  {
    acc=0;
    for (j=i; j<len; j++) acc+=s1[j]*s2[j-i];
    dst[i]=acc<<1;
  }
}

void __Circs(WORD32* dst, WORD16* s1, WORD16* s2, WORD16 len)
{
  int i,j;
  WORD32 acc;

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

void __InvCirc(WORD32* dst, WORD16* s1, WORD16* s2, WORD16 len)
{
  int i,j;
  WORD32 acc;
  for (i=0; i<len; i++)
  {
    acc=0;
    for (j=0; j<=i; j++) acc+=s1[j]*s2[i-j];
    dst[i]=acc<<1;
  }
}

void __InvCircs(WORD32* dst, WORD16* s1, WORD16* s2, WORD16 len)
{
  int i,j;
  WORD32 acc;
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


void __vShlw(WORD16* v1, WORD16* v2, WORD16 nsh, WORD16 size)
{
  WORD16 i;
  if (nsh>=0)
    for (i=0; i<size; i++) v1[i]=v2[i]<<nsh;
  else
    for (i=0; i<size; i++) v1[i]=v2[i]>>(-nsh);
}

void __vShrw(WORD16* v1, WORD16* v2, WORD16 nsh, WORD16 size)
{
  WORD16 i;
  if (nsh>=0)
    for (i=0; i<size; i++) v1[i]=v2[i]>>nsh;
  else
    for (i=0; i<size; i++) v1[i]=v2[i]<<(-nsh);
}

void __vShldw(WORD32* v1, WORD32* v2, WORD16 nsh, WORD16 size)
{
  WORD16 i;
  if (nsh>=0)
    for (i=0; i<size; i++) v1[i]=v2[i]<<nsh;
  else
    for (i=0; i<size; i++) v1[i]=v2[i]>>(-nsh);
}

void __vShrdw(WORD32* v1, WORD32* v2, WORD16 nsh, WORD16 size)
{
  WORD16 i;
  if (nsh>=0)
    for (i=0; i<size; i++) v1[i]=v2[i]>>nsh;
  else
    for (i=0; i<size; i++) v1[i]=v2[i]<<(-nsh);
}

void __vRound(WORD16* v1, WORD32* v2, WORD16 size)
{
  int i;
  for (i=0; i<size; i++)
    v1[i]=(WORD16)((v2[i]+(WORD32)0x00008000)>>16);
}


WORD32 __ConvFirIir(WORD16* v1, WORD16* v2, WORD32 acc)
{
  int i;
  for (i=0; i<10; i++)
    acc+=((WORD32)v1[i]*(WORD32)v2[i])<<1;
  for (i=10; i<20; i++)
    acc-=((WORD32)v1[i]*(WORD32)v2[i])<<1;
  return acc;
}

void __vMovw(WORD16* v1, WORD16* v2, WORD16 size)
{
  int i;
  for (i=0; i<size; i++) v1[i]=v2[i];
}

void __vMovdw(WORD32* v1, WORD32* v2, WORD16 size)
{
  int i;
  for (i=0; i<size; i++) v1[i]=v2[i];
}

void __vSetw(WORD16* v1, WORD16 c, WORD16 size)
{
  int i;
  for (i=0; i<size; i++) v1[i]=c;
}

void __vSetdw(WORD32* v1, WORD32 c, WORD16 size)
{
  int i;
  for (i=0; i<size; i++) v1[i]=c;
}


