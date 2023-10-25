#include "typedef.h"   // Include typedef.h header file for data type definitions
#include <stdio.h>     // Include standard I/O header file
#include <stdint.h>

// Function prototypes
Word16 shl_c(Word16 var_in1, Word16 var_in2);
Word16 shr_c(Word16 var_in1, Word16 var_in2);
extern Word16 shl(Word16 *var_in1, Word16 *var_in2, Word32 *var_out);
extern Word16 shr(Word16 *var_in1, Word16 *var_in2, Word32 *var_out);
extern Word16 sature(Word32 *L_var1, Word16 *var_out);

Word16 sature_c(Word32 L_var1) {
    Word16 min_val = INT16_MIN;
    Word16 max_val = INT16_MAX;

    if (L_var1 > max_val) {
        return max_val;  // Return the maximum value for a 32-bit signed integer
    } else if (L_var1 < min_val) {
        return min_val;  // Return the minimum value for a 32-bit signed integer
    } else {
        return (Word16)L_var1;  // Return L_var1 if it falls within the range
    }
}

Word16 shr_c(Word16 var_in1, Word16 var_in2) {
    Word16 temp = var_in1;
    if (var_in2 < 0){
        return shl_c(temp, -var_in2);
    } else {
        if (var_in2 >= 15) {
            temp = (var_in1 < 0) ? (Word16)(-1) : (Word16)(0);
        } else {
            temp >>= var_in2;
        }
    } 
    return sature_c(temp);
}

Word16 shl_c(Word16 var_in1, Word16 var_in2) {
    Word16 temp = var_in1;
    if (var_in2 < 0){
        return shr_c(temp, -var_in2);
    } else {
        Word32 resultat = (Word32) var_in1 * ((Word32) 1 << var_in2);
        if ((var_in2 >= 15 && var_in1 != 0) || (resultat >= MAX_16 || resultat <= MIN_16)) {
            temp = (var_in1 < 0) ? (Word16)(MIN_16) : (Word16)(MAX_16);
        } else {
            temp <<= var_in2;
        }
    }
    return sature_c(temp);
}

int main() {

    Word16 var_1;
    Word16 var_2;
    printf("Enter two 16-bit integers\n");
    if (scanf("%hx %hx", &var_1, &var_2) != 2){
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }
   
    Word32 var_out_temp;
    Word16 var_out;
    Word16 var_out_c;
    var_out_c = shl_c(var_1, var_2);
    Word16 test_output = shl(&var_1, &var_2, &var_out_temp);
    //sature(&var_out_temp, &var_out);

    printf("test_output: 0x%hx\n", test_output);
    printf("var_out: 0x%hx\n", (Word16)var_out_temp);
    printf("var_out_c: 0x%hx\n", var_out_c);

    var_out_c = shr_c(var_1, var_2);
    shr(&var_1, &var_2, &var_out_temp);
    //sature(&var_out_temp, &var_out);
    printf("var_out: 0x%hx\n", (Word16)var_out_temp);
    printf("var_out_c: 0x%hx\n", var_out_c);

    getchar();
    return 0;
}
