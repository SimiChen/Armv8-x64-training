#include <stdio.h>
#include <string.h>
#include <sys/time.h> 
#include <time.h> 
#include <stdlib.h>
extern void Get_lsp_pol(short *lsp, int *f);
extern void g729ab_Lsp_Az(short *lsp, short *a);
static void Get_lsp_pol_c(short *lsp, int *f);

void g729ab_Lsp_Az_c(
  short lsp[],    /* (i) Q15 : line spectral frequencies       2     */
  short a[]       /* (o) Q12 : predictor coefficients (order = 10)  2 */
)
{   

    //lsp x0 a x1
    register short i, j;
    //x2 = x1 + #20   f1
    //x3 = x2 + #24   f2
    int f1[6], f2[6];
    int t0;

    Get_lsp_pol_c(&lsp[0],f1);
    Get_lsp_pol_c(&lsp[1],f2);

    for (i = 5; i > 0; i--)
    {
        f1[i] += f1[i-1]; 
        f2[i] -= f2[i-1];
    }

    a[0] = 4096;
    for (i = 1, j = 10; i <= 5; i++, j--)
    {   
        t0 = f1[i] + f2[i];
        a[i] = (short)( t0 >> 13 );        /* from Q24 to Q12 and * 0.5 */
        if((t0 & 0x00001000) != 0) a[i]++;

        t0 = f1[i] - f2[i];
        a[j] = (short)( t0 >> 13 );        /* from Q24 to Q12 and * 0.5 */
        if((t0 & 0x00001000) != 0) a[j]++;

    }

    return;
}
static void Get_lsp_pol_c(short *lsp, int *f) {

    short hi, lo, hi1, lo1;
    int t0, t01;
    /* All computation in Q24 */
    //f  8pcs f[i] = [x0, 4*i]
    //x2 = #1
    //str #0x1000000L, [x1]
    f[0] = 0x1000000L;             /* f[0] = 1.0;             in Q24  */
    //ldrh w3, [x0]
    //
    f[1] = - ((int)lsp[0] << 10); 

    //i = 2
    //x8 = i 
    //x9 = x8
    //fun f
    f[2] = f[0]; //f[i] = f[i-2]
        //inner loop
    hi  = (short)(f[1] >> 16);
    lo  = (short)((f[1] >> 1) - ((int)hi<<15) );  

    t0 = (int)hi * (int)lsp[2];
    t0 += (int)lo * (int)lsp[2] >> 15;
    t0 <<= 2;


    f[2] += f[0];
    f[2] -= t0;

    //if x9 > 2: x9 -= 1, call f
    //f[1] -= (int)lsp[x8*2-2] << 10;
    f[1] -= (int)lsp[2] << 10;

    //	i = 3 and i = 2
    f[3] = f[1];

    hi  = (short)(f[2] >> 16);                        //f[2] high bit
    hi1  = (short)(f[1] >> 16);                       
    lo  = (short)((f[2] >> 1) - ((int)hi<<15) );     //f[2] & #65535 >> 1; 
    lo1  = (short)((f[1] >> 1) - ((int)hi1<<15) );   
    t0 = (int)hi * (int)lsp[4];
    t01 = (int)hi1 * (int)lsp[4];
    t0 += (int)lo * (int)lsp[4] >> 15;
    t01 += (int)lo1* (int)lsp[4] >> 15;
    t0 <<= 2;
    t01 <<= 2;
    f[3] += f[1];
    f[2] += f[0];
    f[3] -= t0;
    f[2] -= t01;

    f[1] -= (int)lsp[4] << 10;


    //	i = 4 i=3 i=2
    f[4] = f[2];

    hi  = (short)(f[3] >> 16);
    hi1  = (short)(f[2] >> 16);
    lo  = (short)((f[3] >> 1) - ((int)hi<<15) );  
    lo1  = (short)((f[2] >> 1) - ((int)hi1<<15) );  
    t0 = (int)hi * (int)lsp[6];
    t01 = (int)hi1 * (int)lsp[6];
    t0 += (int)lo * (int)lsp[6] >> 15;
    t01 += (int)lo1 * (int)lsp[6] >> 15;
    t0 <<= 2;
    t01 <<= 2;
    f[4] += f[2];
    f[4] -= t0;
    f[3] += f[1];
    f[3] -= t01;

    hi  = (short)(f[1] >> 16);
    lo  = (short)((f[1] >> 1) - ((int)hi<<15) );  
    t0 = (int)hi * (int)lsp[6];
    t0 += (int)lo * (int)lsp[6] >> 15;
    t0 <<= 2;
    f[2] += f[0];
    f[2] -= t0;


    f[1] -= (int)lsp[6] << 10;

    //	i = 5432
    f[5] = f[3];

    hi  = (short)(f[4] >> 16);
    hi1  = (short)(f[3] >> 16);
    lo  = (short)((f[4] >> 1) - ((int)hi<<15) );  
    lo1  = (short)((f[3] >> 1) - ((int)hi1<<15) );  
    t0 = (int)hi * (int)lsp[8];
    t01 = (int)hi1 * (int)lsp[8];
    t0 += (int)lo * (int)lsp[8] >> 15;
    t01 += (int)lo1 * (int)lsp[8] >> 15;
    t0 <<= 2;
    t01 <<= 2;
    f[5] += f[3];
    f[5] -= t0;
    f[4] += f[2];
    f[4] -= t01;

    hi  = (short)(f[2] >> 16);
    hi1  = (short)(f[1] >> 16);
    lo  = (short)((f[2] >> 1) - ((int)hi<<15) );  
    lo1  = (short)((f[1] >> 1) - ((int)hi1<<15) );  
    t0 = (int)hi * (int)lsp[8];
    t01 = (int)hi1 * (int)lsp[8];
    t0 += (int)lo * (int)lsp[8] >> 15;
    t01 += (int)lo1 * (int)lsp[8] >> 15;
    t0 <<= 2;
    t01 <<= 2;
    f[3] += f[1];
    f[3] -= t0;
    f[2] += f[0];
    f[2] -= t01;

    f[1] -= (int)lsp[8] << 10;
    return;
}

static void Get_lsp_pol_c_s(short *lsp, int *f) {
    short hi, lo, hi1, lo1;
    int t0, t01;

    for (int i = 0; i < 6; i++){
        printf("x8 = 0, f[%d] = %x\n", i, f[i]);
    }
    
    /* All computation in Q24 */
    //f  8pcs f[i] = [x0, 4*i]
    //x2 = #1
    //str #0x1000000L, [x1]
    f[0] = 0x1000000L;             /* f[0] = 1.0;             in Q24  */
    //ldrh w3, [x0]
    //
    f[1] = - ((int)lsp[0] << 10); 

    for (int i = 2; i < 6; i++){
        f[i] = f[i-2];
        for (int j = i; j > 1; j--){
            hi = (short)(f[j-1] >> 16);
            lo = (short)((f[j-1] >> 1) - ((int)hi<<15) );
            t0 = (int)hi * (int)lsp[2*i-2];
            t0 += (int)lo * (int)lsp[2*i-2] >> 15;
            t0 <<= 2;
            f[j] += f[j-2];
            f[j] -= t0;
            printf("hi(x6) = %d, lo(x7) = %d, t0(x14) = %d\n", hi, lo, t0);
        }
        f[1] -= (int)lsp[2*i-2] << 10;
        for (int k = 0; k < 6; k++){
            printf("x8 = %d, f[%d] = %x\n", i, k, f[k]);
        }
    }
    return;
}

short random_16() {
    return (short)rand()%65535 - 32767;
}

int random_32() {
    int random_number = ((int)rand() << 16) | rand();
    return (int)random_number%4294967295 - 2147483647;
}

int main(){

    int f[6];
    short lsp[10];
    //int f[6] = {0x12341234, 0x12341233, 0x12341232, 0x12341231, 0x12341230, 0x12341230};
    //short lsp[10] = {0x123, 0x124, 0x134, 0x234, 0x123, 0x124, 0x134, 0x234, 0x134, 0x237};
    short a[10], a_c[10];
    int f_c[6], f_c_s[6];
    short lsp_c[9], lsp_c_s[9];
    srand((unsigned)time( NULL ) );
    for (int i = 0; i < 6; i++){
        f[i] = random_32();
    }
    for (int i = 0; i < 10; i++){
        lsp[i] = random_16();
    }
    

    memcpy(f_c, f, sizeof(f));
    memcpy(lsp_c, lsp, sizeof(lsp));
    memcpy(f_c_s, f, sizeof(f));
    memcpy(lsp_c_s, lsp, sizeof(lsp));
    g729ab_Lsp_Az_c(lsp, a_c);
    g729ab_Lsp_Az(lsp, a);
    //Get_lsp_pol_c(lsp_c, f_c);
    //Get_lsp_pol_c_s(lsp_c_s, f_c_s);
    //Get_lsp_pol(lsp, f);
    

    for (int i = 0; i <=9; i++){
        //printf("f[%d] = %x - %x - %x\n", i, f[i], f_c[i], f_c_s[i]);
        printf("f[%d] = %x - %x\n", i, a[i], a_c[i]);
    }
    return 0;
}