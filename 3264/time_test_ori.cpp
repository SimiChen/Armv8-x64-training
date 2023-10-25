#include <sys/time.h> 
#include <time.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h> 

#define BUFFER_SIZE_T 160
#define MAX_32 (int)0x7fffffffL
#define MIN_32 (int)0x80000000L

short Overflow;

static __inline int L_add(int L_var1, int L_var2)
  {
   int L_var_out;
#if   1
   L_var_out = L_var1 + L_var2;

   if (((L_var1 ^ L_var2) & MIN_32) == 0)
     {
      if ((L_var_out ^ L_var1) & MIN_32)
        {
         L_var_out = (L_var1 < 0) ? MIN_32 : MAX_32;
         Overflow = 1;
//		 printf("add overflow here! L_var_out=0x%x\n",L_var_out);
        }
     }
#else
   __asm__ __volatile__ ("QADD %0, %1,  %2\n"
  :"=r" (L_var_out):"r"(L_var1),"r"(L_var2));
#endif
   return(L_var_out);
  }
  
static __inline int L_mult(short var1,short var2)
  {
   int L_var_out;
#if     1
   L_var_out = (int)var1 * (int)var2;
   if (L_var_out != (int)0x40000000L)
     {
      L_var_out *= 2;
     }
   else
     {
      Overflow = 1;
      L_var_out = MAX_32;
	  printf("mult overflow here!\n");
	  getchar();
     }
#else
     __asm__ __volatile__ ("SMULBB %0, %1, %2\n"
    "QADD   %0, %0,%0\n"
 :"+r" (L_var_out):"r"(var1),"r"(var2));
#endif
   return(L_var_out);
  }
  
static __inline int L_mac(int L_var3, short var1, short var2)
  {
   long long L_var_out=0x12345678, tmp=2;
#if	0
   int L_produit;
   L_produit = L_mult(var1,var2);
   L_var_out = L_add(L_var3,L_produit);
#else
	printf("\n");
	printf("L_var_out b4 L_mac= %#llx\n",L_var_out);
    __asm__ __volatile__ (
		"SMULL x0, w2, w3\n"
		"MADD  x0, x4, x0, x1\n"
  		:"+r" (L_var_out):"r"((long long)L_var3),"r"((int)var1),"r"((int)var2),"r"((int)tmp));
  if(L_var_out>MAX_32) L_var_out = MAX_32;
  if(L_var_out<MIN_32) L_var_out = MIN_32;
  printf("L_var_out after L_mac= %#llx\n",L_var_out);
  
#endif
	

   return(L_var_out);
  }

  
void AddExample() {
short src1[BUFFER_SIZE_T] = {0};
short src2[BUFFER_SIZE_T] = {0};
int dst[BUFFER_SIZE_T];
long long result,result_c,tmp=0, cmp_flag=0;
int i;

/* Test */

//		printf("src1:\n");
		for(i=0; i<BUFFER_SIZE_T; i++)
		{
			src1[i] = rand()%60001-30000; //data rang -30000 to 30000
//			printf("src1[%d]=%d,    ",i,src1[i]);
		}

		printf("\n");
//		printf("src2:\n");
		srand((unsigned)time( NULL ) );
		for(i=0; i<BUFFER_SIZE_T; i++)
		{
			src2[i] = rand()%60001-30000; //data rang -30000 to 30000
//			printf("src2[%d]=%d,    ",i,src2[i]);
		}
		printf("\n");

	result = rand()%60001-30000;; //0*1;
	result_c = result; //0*1;
	for(i=0;i<BUFFER_SIZE_T;i++)
	{
// c output
		tmp = L_mult(src1[i],src2[i]);
		result_c = L_add(result_c,tmp);

// asm output
		result = L_mac(result, src1[i], src2[i]);
	
		if(result != result_c)
		{
			printf("result[%d] = %#llx result_c[%d] = %#llx\n",i, result,i,result_c);
			cmp_flag = 1;
		}
	}
/* Test */

	printf("\n");
	printf("\n");
	if(cmp_flag)
	{
		printf("Test Done ERROR!!!\n");
	}
	else{
		printf("Test Done PASS!!!\n");
	}
	printf("\n");

 return;
}


int main(void){
	
	double ms_total = 0.0;
	struct timeval tv1, tv2;
	long max_us = 0;
	long us;
	
	int i=10;
	
	while(i)
	{
		gettimeofday(&tv1, 0);
		AddExample();
		gettimeofday(&tv2, 0);
		us = (tv2.tv_sec - tv1.tv_sec)* 1000000 + (tv2.tv_usec - tv1.tv_usec);
		i--;
		ms_total += (float)us/1000;
	}
	
	printf("total proc time = %2f ms\n",ms_total);
	printf("\n");
	
return 0;
}