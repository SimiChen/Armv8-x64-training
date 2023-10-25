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
    printf("Enter a 64-bit integer number: ");

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

    printf("Enter two 64-bit integer numbers\n");
    
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

    printf("Enter two 64-bit integer numbers\n");
    
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

extern Word64 abss(Word64 *L_var, Word32 *var_out);

Word64 abs_c(Word64 L_var) {
    Word32 min_val = INT32_MIN;
    Word32 max_val = INT32_MAX;

    if (L_var == (Word64)min_val) { 
        return (Word64)max_val;
    }else if (L_var < 0) {
        return -L_var;
    }else {
        return L_var;
    }
}

int test_abs() {
    Word32 var_out = 1;  // Initialize var_out to 1
    Word32 var_out_c = 1;  // Initialize var_out_c to 1
    // Prompt the user to enter a 64-bit decimal number
    printf("Enter a 64-bit integer number: ");

    Word64 L_var1;  // Declare a variable to store the user's input

    // Read the input as a 64-bit hexadecimal value and store it in L_var1
    if (scanf("%llx", &L_var1) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    abss(&L_var1, &var_out);
    var_out_c = abs_c(L_var1);

    // Print the value of var_out in hexadecimal format
    printf("Output_arm: 0x%lx\n", var_out);
    printf("Output_c: 0x%lx\n", var_out_c);

    return 0;  // Exit the program with a success code
}

extern Word64 msu(Word64 *L_var1, Word32 *L_var2, Word32 *L_var3, Word64 *var_out);

Word32 msu_c(Word64 L_var1, Word32 L_var2, Word32 L_var3) {
    return sature_c(L_var1 - (L_var2 * L_var3) * 2);
}

int test_msu() {
    Word64 var_out_temp = 1;  // Initialize var_out to 1
    Word32 var_out = 1;
    Word32 var_out_c = 1;  // Initialize var_out_c to 1

    printf("Enter one 64-bit integers and two 32-bit integers\n");

    Word64 L_var1;
    Word32 L_var2, L_var3;
    printf("Please enter the first 64-bit integer:");
    if (scanf("%llx", &L_var1) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    printf("Please enter the first 32-bit integer:");
    if (scanf("%lx", &L_var2) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    printf("Please enter the second 32-bit integer:");
    if (scanf("%lx", &L_var3) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    msu(&L_var1, &L_var2, &L_var3, &var_out_temp);
    sature(&var_out_temp, &var_out);
    var_out_c = msu_c(L_var1, L_var2, L_var3);

    printf("Output_arm: 0x%lx\n", var_out);
    printf("Output_c: 0x%lx\n", var_out_c);

    return 0;  // Exit the program with a success code
}

int main() {
    printf("welcome to the test program\n");
    printf("please enter a number to select the test function\n");

    const char* instructions[] = {"saturate", "add", "sub", "abs", "msu", "Quit"};
    for (int i = 0; i < 6; i++) {
        printf("%d.%s \n", i + 1, instructions[i]);
    }

    int test_num = 0;
    while (test_num != 6) {
        printf("\n please enter a number to choose one: ");
        if (scanf("%d", &test_num) != 1) {
            printf("Invalid input.\n");  
            return 1;
        }else if(test_num < 1 || test_num > 6){
            printf("Invalid input.\n");  
            return 1;
        }else{
            printf(" you choose the %s\n", instructions[test_num - 1]);
            switch (test_num)
            {
                case 1:
                    test_sature();
                    break;
                case 2:
                    test_add();
                    break;
                case 3:
                    test_sub();
                    break;
                case 4:
                    test_abs();
                    break;
                case 5:
                    test_msu();
                    break;
                case 6:
                    printf("bye!");
            }
        }
    }
    
            



    //test_sature();  // Call the test_sature function

    //test_add();  // Call the test_add function

    //test_sub();  // Call the test_sub function
    
    //test_abs();

    //test_msu(); 

    return 0;
}
