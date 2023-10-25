#include <sys/time.h> 
#include <time.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h> 
#include "typedef.h"
#include <string.h>
#define  L_SUBFR      40

extern void filt_plt(short *, short *, short *, short);

void filt_plt_c(
 short *s_in,       /* input : input signal with past   x0*/
 short *s_ltp,      /* input : filtered signal with gain 1   x1*/
 short *s_out,      /* output: output signal    x2*/
 short gain_plt     /* input : filter gain    x3*/
)
{

    /* Local variables */
    int n;       //x4
    int L_acc;       //x5
    short gain_plt_1;        //x6

    gain_plt_1 = 32767 - gain_plt;    //SUB x6, #32767, x3
    if(gain_plt != 0) gain_plt_1++;       //COM x3, #0

    for(n=0;  n<L_SUBFR; n++) {
        /* s_out(n) = gain_plt x s_in(n) + gain_plt_1 x s_ltp(n)        */
        //x9 -> n
        //x7 = (int)s_in[n]
        //x8 = (int)s_ltp[n]
        //x7 = x7 * (int)gain_plt
        //x8 = x8 * (int)gain_plt_1
        //x7 = x7 + x8
        L_acc    = (int)gain_plt * (int)s_in[n] + (int)gain_plt_1 * (int)s_ltp[n];  /* no overflow     x7*/
        printf("gain_plt = %x, s_in[%d] = %x, gain_plt_1 = %x, s_ltp[%d] = %x\n", gain_plt, n, s_in[n], gain_plt_1, n, s_ltp[n]);
        L_acc += 0x00004000;   //x7 += 0x00004000
        printf("L_acc = 0x%x\n", L_acc);
        //x8 = x7 >> 15
        //s_out[n] = x8
		s_out[n] = (short)(L_acc>>15);
        printf("s_out[%d] = 0x%x, %d\n\n", n, s_out[n], s_out[n]);

    }

    return;
}

Word16 random_16() {
    return (Word16)rand()%65535 - 32767;
}

int main() {

    srand((unsigned)time( NULL ) );
    //short s_in[L_SUBFR] = {-30736, -5878, -21631, 1330, 8250, -24294, -31794, 29842, 3548, -30245, -25028, -8720, -8928, -30829, -30296, 27141, -15829, 24693, 26570, -14576, -7038, -14244, -246, -22862, 32372, 18700, -20008, 30324, -5210, -24570, 10085, 1765, -8936, -10439, 19711, 19685, -31120, 6607, -11732, 4701};
    //short s_ltp[L_SUBFR] = {6348, 20190, 5309, 22886, 32476, 16473, -26910, 15971, 16776, 15400, -32435, 22982, -15189, 4367, 10591, -28264, -11506, -4693, -6745, 2052, -6103, -6065, -17171, -29467, -20340, -25425, -22788, 3832, 32262, -2738, -30197, 27023, -6311, -15134, 7752, -20095, -27328, 1401, 16512, -12129};
    //short s_out[L_SUBFR], s_out_c[L_SUBFR], s_diff=0;
    short s_in[L_SUBFR], s_ltp[L_SUBFR], s_out[L_SUBFR], s_out_c[L_SUBFR], s_diff=0;
    short gain_plt = random_16();
    //short gain_plt = -9993;
    int n;
    printf("gain_plt = %d\n", gain_plt);
    for (n=0; n<L_SUBFR; n++) {
        s_in[n] = random_16();
        s_ltp[n] = random_16();
    }
    
    for (n=0; n<L_SUBFR; n++) {
        printf("%d, ", s_in[n]);
    }
    printf("\n");
    for (n=0; n<L_SUBFR; n++) {
        printf("%d, ", s_ltp[n]);
    }
    printf("\n\n");
    filt_plt(s_in, s_ltp, s_out, gain_plt);
    filt_plt_c(s_in, s_ltp, s_out_c, gain_plt);
    for (n=0; n<L_SUBFR; n++) {
        printf("%d, ", s_out[n]);
    }
    printf("\n");

    
    for (n=0; n<L_SUBFR; n++) {
        printf("%d, ", s_out_c[n]);
        if (s_out[n] != s_out_c[n]) {
            s_diff = n;
        }
    }
    printf("\n");
    printf("finish!!\n");
    if (s_diff != 0) {
        printf("Error!!! at %d, where %d != %d\n", s_diff, s_out[s_diff], s_out_c[s_diff]);
        return 1;
    }
    printf("OK!!!\n");
    return 0;
}
