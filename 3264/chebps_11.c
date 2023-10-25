#include <sys/time.h> 
#include <time.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h> 
#include "typedef.h"
#include <string.h>



short Chebps_11_c(short x, short f[], short n)
{
  short i, cheb;
  short b0_h, b0_l, b1_h, b1_l, b2_h, b2_l;
  int t0;

  b2_h = 256;           //w3      
  b2_l = 0;             //w4
  //b2 = b2_h >> 15 + b2_l

  t0 = (int)x;       //x5         

  t0 += (int)f[1] << 3;           

  b1_h  = (short)(t0>>6);         //w6
  b1_l  = (short)((t0<<9) - ((int)b1_h<<15) );   //w7
    //print t0, b1_h, b1_l as x5, x6, x7
    //printf("29: x5 = 0x%x, x6 = 0x%x, x7 = 0x%x\n", t0, b1_h, b1_l);

    //i      w8
  for (i = 2; i<n; i++)
  {
    t0 = b1_h * x;
	  t0 += (int)b1_l * (int)x >> 15;

    //printf("37: x5 = 0x%x, %d\n", t0, t0);
    // x5 += (w7 * w0) >> 15
    t0 <<= 2;
    t0 -= b2_h<<16; 
	  t0 -= (int)b2_l << 1;
    t0 += f[i]<<13;    
    //printf("43: x5 = 0x%x, %d, x3 = 0x%x, x4 = 0x%x, x10 = 0x%x\n", t0, t0, b2_h, b2_l, f[i]);
    //f[i] = [x1, w8, LSL #1]

     //b0 = b0_h >> 15 + b0_l
    b0_h  = (short)(t0>>16);    //w11 = (short)(x5>>16)
    b0_l  = (short)((t0>>1) - ((int)b0_h<<15) );  //w12
    
    //printf("50: x11 = 0x%x, x12  = 0x%x\n", b0_h, b0_l);


    b2_l = b1_l;              
    b2_h = b1_h;
    b1_l = b0_l;                
    b1_h = b0_h;
    //printf("\n");
  }

  t0 = b1_h * x;
  t0 += (int)b1_l * (int)x >> 15;
    //printf("62: x5 = 0x%x\n", t0);
  t0 -= b2_h<<15; 
  t0 -= (int)b2_l;
  t0 += f[i]<<11;          
  t0 >>= 9;             
  //printf("67: x5 = 0x%x\n", t0);   
  if(t0 > 32767L) {t0 = 32767L;}
  if(t0 < -32768L) {t0 = -32768L;}
  cheb = (short)t0;

  return(cheb);
}

extern short Chebps_11(short x, short f[], short n);

Word16 random_16() {
    return (Word16)rand()%65535 - 32767;
}

Word32 random_32() {
    Word32 random_number = ((Word32)rand() << 16) | rand();
    return (Word32)random_number%4294967295 - 2147483647;
}

int main() {
    srand((unsigned)time( NULL ) );
    short x = random_16();
    //short x = 0x7ae1;
    short f[10];
    //short f2[10] = {-15172,0x5f13,0x70c6,0x5a,0x48e1,0x7557,0x7521,-6421,0x4063,0x4865};
    short n = 10;
    short trial = 50;
    short output_c, output; 
    short dismatch_x, dismatch_f[10], dismatch_trial = -1;
    struct timeval tv1, tv2, tv3, tv4;
    long us;
    gettimeofday(&tv1, 0);
    for (int j = 0; j < trial; j ++) {
      for (int i = 0; i < 10; i++) {
          f[i] = random_16();
          //f[i] = f2[i];
      }

      //print x, f
      printf("x = 0x%x\n", x);
      for (int i = 0; i < 10; i++) {
          printf("f[%d] = 0x%x\n", i, f[i]);
      } 
      output = Chebps_11(x, f, n);
      output_c = Chebps_11_c(x, f, n);

      if (output != output_c) {
        memcpy(dismatch_f, f, sizeof(f));
        dismatch_trial = j;
        dismatch_x = x;
      }

      //print output
      printf("output=0x%x\n", output);
      printf("output_c=0x%x\n\n", output_c);
    }
    gettimeofday(&tv2, 0);
    us = (tv2.tv_sec - tv1.tv_sec)* 1000000 + (tv2.tv_usec - tv1.tv_usec);
    printf("time_with_%d_trial= %ld\n", trial, us);

    if (dismatch_trial != -1) {
      printf("dismatch_x = 0x%x\n", dismatch_x);
      for (int i = 0; i < 10; i++) {
        printf("dismatch_f[%d] = 0x%x\n", i, dismatch_f[i]);
      }
      printf("dismatch_trial = %d\n", dismatch_trial);
    }

    return 0;
}