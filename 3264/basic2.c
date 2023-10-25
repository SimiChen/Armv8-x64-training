#include "typedef.h"   // Include typedef.h header file for data type definitions
#include <stdio.h>     // Include standard I/O header file

extern Word32 sature(Word64 *L_var1, Word32 *var_out);  // Declare the external sature function

int main() {
    Word32 var_out = 1;  // Initialize var_out to 1

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

    // Print the value of var_out in hexadecimal format
    printf("Output: 0x%lx\n", var_out);

    return 0;  // Exit the program with a success code
}
