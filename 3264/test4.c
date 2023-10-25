#include <stdio.h>
#include <sys/time.h>
#include <time.h> 
#include <unistd.h>
#include <stdlib.h>
#include <arm_neon.h>

#define BUFFER_SIZE_T 160
#define MAX_32 (int)0x7fffffffL
#define MIN_32 (int)0x80000000L

short overflow;
int err_flag = 0;               //是否执行内嵌汇编标志位，避免通过打印消耗时间
int err_count = 0;              //错误执行次数
                               //
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
                        overflow = 1;
                }
        }
#else

#endif
        return(L_var_out);
}
static __inline int L_mult(short var1,short var2)
{
        int L_var_out;
#if 1
        L_var_out = (int)var1 * (int)var2;
        if (L_var_out != (int)0x40000000L)
        {
                L_var_out *= 2;
        }
        else
        {
                overflow = 1;
                L_var_out = MAX_32;
                printf("mult overflow here!\n");
                getchar();
        }
#else

#endif
        return(L_var_out);
}
static __inline int L_mac(int L_var3, short var1, short var2)
{
        long long L_var_out_t=0x12345678, tmp=2;
        long long L_var_out = 0;
#if     1
         int L_produit;
         L_produit = L_mult(var1,var2);
         L_var_out = L_add(L_var3,L_produit);
#else
        //printf("\n");
        //printf("L_var_out b4 L_mac= %#llx\n",L_var_out);
        __asm__ __volatile__ ("SMULL x0, w2, w3\n"
                                "MADD  x0, x4, x0, x1\n"
                                  :"+r" (L_var_out):"r"((long long)L_var3),"r"((int)var1),"r"((int)tmp),"r"((int)var2));
        if(L_var_out>MAX_32) L_var_out = MAX_32;
          if(L_var_out<MIN_32) L_var_out = MIN_32;
        if(L_var_out_t == L_var_out)
        { 
                err_count++;
                err_flag = 1;
        }
          //printf("L_var_out after L_mac= %#llx\n",L_var_out);
#endif
            return(L_var_out);
}
void AddExample()
{
        short src1[BUFFER_SIZE_T] = {0};
        short src2[BUFFER_SIZE_T] = {0};
        int dst[BUFFER_SIZE_T];
        long long result,result_c,tmp=0, cmp_flag=0;
        int i;
        for(i=0; i<BUFFER_SIZE_T; i++)
        {
                src1[i] = rand()%60001-30000; //data rang -30000 to 30000
        }
        //printf("\n");
        srand((unsigned)time( NULL ) );
        for(i=0; i<BUFFER_SIZE_T; i++)
        {
                src2[i] = rand()%60001-30000; //data rang -30000 to 30000
        }
        //printf("\n");

        result = rand()%60001-30000;; //0*1;
        result_c = result; //0*1;
        for(i=0;i<BUFFER_SIZE_T;i++)
        {
                tmp = L_mult(src1[i],src2[i]);
                result_c = L_add(result_c,tmp);
                result = L_mac(result, src1[i], src2[i]);
                if(result != result_c)
                {
                        printf("result[%d] = %#llx result_c[%d] = %#llx\n",i, result,i,result_c);
                        cmp_flag = 1;
                }
        }
        //printf("\n");
        //printf("\n");
        if(cmp_flag)
        {
                printf("Test Done ERROR!!\n");
        }
        else
        {
                //printf("Test Done PASS!!!\n");
        }
        //printf("\n");

        return;
}
extern "C" long long madd_t(long long a,long long b,long long c,long long d);
extern "C" uint64x2_t add_neon(uint64x2_t  a,uint64x2_t b);
extern void load_data(uint8_t *data);
extern int testRGB(char *inputBuffer,char * outputBuffer,unsigned int testLen);
int main(void)
{
        double ms_total = 0.0;
        struct timeval tv1, tv2;
        long max_us = 0;
        long us;
        uint64x2_t num0 = {10,20};
        uint64x2_t num1 = {10,20};
        long long a = 10;
        long long b = 10;
        long long c = 40;
        long long d = 0;
        int i=10;
        int results_t = 0;
        short value1 = 1234;
        short value2 = 5678;
        uint8_t *sendbuf;
        char *recvbuf;

        sendbuf =(uint8_t *) malloc(48);
        recvbuf = (char *)malloc(48);

        while(i)
        {
                gettimeofday(&tv1, 0);
                AddExample();
                gettimeofday(&tv2, 0);
                us = (tv2.tv_sec - tv1.tv_sec)* 1000000 + (tv2.tv_usec - tv1.tv_usec);
                i--;
                ms_total += (float)us/1000;
        }
        results_t = L_mac(results_t, value1, value2);
        results_t = L_mac(results_t, value1, value2);
        printf("results_t :%d\n",results_t);



        d = madd_t(a,b,c,d);
//      printf("d:%d\n",d);

        for(i = 0;i <  48;i ++)
        {
                sendbuf[i] = i;
                recvbuf[i] = 0;
        }
//      testRGB(sendbuf,recvbuf,48);
        load_data(sendbuf);

        printf("long long:%d\n",sizeof(long long));
        printf("total proc time = %2f ms\n",ms_total);
        printf("errCount: %d errFlag: %d\n",err_count,err_flag);
        printf("\n");

        uint64x2_t results = add_neon(num0,num1);
//      printf("c: %d\n",c);
        printf("The sum of (%llu, %llu) and (%llu, %llu) is (%llu, %llu)\n",
                  num0[0], num0[1], num1[0], num1[1], results[0], results[1]);
        return 0;
}
