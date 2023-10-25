#include "typedef.h"   // Include typedef.h header file for data type definitions
#include <stdio.h>     // Include standard I/O header file
#include <stdint.h>

extern Word32 sature(Word64 *L_var1, Word32 *var_out);  // Declare the external sature function

Word32 sature_c(Word64 L_var1) {
    Word32 min_val = INT32_MIN;
    Word32 max_val = INT32_MAX;

    if (L_var1 > (Word64)max_val) {
        return max_val;  // Return the maximum value for a 32-bit signed integer
    } else if (L_var1 < (Word64)min_val) {
        return min_val;  // Return the minimum value for a 32-bit signed integer
    } else {
        return (Word32)L_var1;  // Return L_var1 if it falls within the range
    }
}

int test_sature() {
    Word32 var_out = 1;  // Initialize var_out to 1
    Word32 var_out_c = 1;  // Initialize var_out_c to 1
    // Prompt the user to enter a 64-bit decimal number
    printf("Enter a 64-bit decimal number: ");

    Word64 L_var1;  // Declare a variable to store the user's input

    // Read the input as a 64-bit hexadecimal value and store it in L_var1
    if (scanf("%llx", &L_var1) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    // Call the sature function with the addresses of L_var1 and var_out
    sature(&L_var1, &var_out);
    var_out_c = sature_c(L_var1);

    // Print the value of var_out in hexadecimal format
    printf("Output_arm: 0x%lx\n", var_out);
    printf("Output_c: 0x%lx\n", var_out_c);

    return 0;  // Exit the program with a success code
}

extern Word64 add(Word64 *L_var1, Word64 *L_var2, Word64 *var_out); 

Word32 add_c(Word64 L_var1, Word64 L_var2) {
    return sature_c(L_var1 + L_var2);
}

int test_add() {
    Word64 var_out_temp = 1;  // Initialize var_out to 1
    Word32 var_out = 1;
    Word32 var_out_c = 1;  // Initialize var_out_c to 1

    printf("Enter two 64-bit decimal numbers\n");
    
    Word64 L_var1, L_var2;  // Declare two variables to store the user's input
    printf("Please enter the first one:");
    if (scanf("%llx", &L_var1) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    printf("Please enter the second one:");
    if (scanf("%llx", &L_var2) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    // Call the add function with the addresses of L_var1, L_var2, and var_out
    add(&L_var1, &L_var2, &var_out_temp);
    sature(&var_out_temp, &var_out);
    var_out_c = add_c(L_var1, L_var2);

    printf("Output_arm: 0x%lx\n", var_out);
    printf("Output_c: 0x%lx\n", var_out_c);
    return 0;  // Exit the program with a success code
}

extern Word64 sub(Word64 *L_var1, Word64 *L_var2, Word64 *var_out);

Word32 sub_c(Word64 L_var1, Word64 L_var2) {
    return sature_c(L_var1 - L_var2);
}

int test_sub() {
    Word64 var_out_temp = 1;  // Initialize var_out to 1
    Word32 var_out = 1;
    Word32 var_out_c = 1;  // Initialize var_out_c to 1

    printf("Enter two 64-bit decimal numbers\n");
    
    Word64 L_var1, L_var2;  // Declare two variables to store the user's input
    printf("Please enter the first one:");
    if (scanf("%llx", &L_var1) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    printf("Please enter the second one:");
    if (scanf("%llx", &L_var2) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    // Call the sub function with the addresses of L_var1, L_var2, and var_out
    sub(&L_var1, &L_var2, &var_out_temp);
    sature(&var_out_temp, &var_out);
    var_out_c = sub_c(L_var1, L_var2);

    printf("Output_arm: 0x%lx\n", var_out);
    printf("Output_c: 0x%lx\n", var_out_c);
    return 0;  // Exit the program with a success code
}

int main() {
    //test_sature();  // Call the test_sature function

    //test_add();  // Call the test_add function

    test_sub();  // Call the test_sub function

    return 0;
}
