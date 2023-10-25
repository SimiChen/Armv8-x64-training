#include <sys/time.h> 
#include <time.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h> 
#include "typedef.h"

// Prototype for the modified assembly function
//extern Word16 madd_t(Word32 L_var1, Word16 var_in1, Word16 var_in2);
//extern Word16 madd_add(Word32 *L_var1, Word16 *var_in1, Word16 *var_in2);

Word16 random_16() {
    return (Word16)rand()%65535 - 32767;
}

int random_32() {
    int random_number = ((int)rand() << 16) | rand();
    return (int)random_number%4294967295 - 2147483647;
}

int main() {
    Word16 input1 = 5;
    Word16 input2 = 2;
    Word32 output;

    // Call the modified assembly function and capture the return value
    //output = shl(input1, input2);
    //output = random_16();
    //Word32 output_32 = (Word32)output;
    //Word32 output_32_add;

    //output_32 = madd_t(output_32, input1, input2);
    //output_32 = madd_add(&output_32, &input1, &input2);
    Word64 f, f2;
    Word16 hi, lo, lsp;
    Word32 f1, t0;
    srand((unsigned)time( NULL ) );
    lsp = abs((Word16)random_16());
    f1 = abs((Word32)random_32());
    //lsp = 0x1111;
    //f1 = 0x24d23456;
    printf("lsp = %hx, f1 = %lx\n", lsp, f1);
    hi  = (short)(f1 >> 16);
    lo  = (short)((f1 >> 1) - ((int)hi<<15) );  
    t0 = (int)hi * (int)lsp;
    t0 += (int)lo * (int)lsp >> 15;
    t0 <<= 2;

    f = (Word64)f1 * (Word64)lsp;
    
    f2 = f >> 16;
    f2 <<= 2;
    f <<= 2;
    printf("result: t0 = %lx, f = %llx, f2 = %llx\n", t0, f, f2);
    //lsp = c568, f1 = ffffffffe7fe986a
    //result: t0 = 15fa4934, f = 15fa4935f440

    // Output the result
    //printf("Result: %hx , %lx\n", output, output_32);
    //add a pause
    scanf("%ld", &output);
    return 0;
}
