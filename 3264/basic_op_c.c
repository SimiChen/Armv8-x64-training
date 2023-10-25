#include "typedef.h"   // Include typedef.h header file for data type definitions
#include <stdio.h>     // Include standard I/O header file
#include <stdint.h>

extern Word16 sature(Word32 L_var1);  // Declare the external sature function

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

int test_sature() {
    Word16 var_out = 1;  // Initialize var_out to 1
    Word16 var_out_c = 1;  // Initialize var_out_c to 1
    // Prompt the user to enter a 64-bit decimal number
    printf("Enter a 32-bit integer number: ");

    Word32 L_var1;  // Declare a variable to store the user's input

    // Read the input as a 32-bit hexadecimal value and store it in L_var1
    if (scanf("%lx", &L_var1) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    // Call the sature function with the addresses of L_var1 and var_out
    var_out = sature(L_var1);
    var_out_c = sature_c(L_var1);

    // Print the value of var_out in hexadecimal format
    printf("Output_arm: 0x%hx\n", var_out);
    printf("Output_c: 0x%hx\n", var_out_c);

    return 0;  // Exit the program with a success code
}

extern Word32 add(Word16 L_var1, Word16 L_var2); 

Word16 add_c(Word16 L_var1, Word16 L_var2) {
    return sature_c((Word32)(L_var1 + L_var2));
}

int test_add() {
    Word16 var_out = 1;
    Word16 var_out_c = 1;  // Initialize var_out_c to 1

    printf("Enter two 64-bit integer numbers\n");
    
    Word16 L_var1, L_var2;  // Declare two variables to store the user's input
    printf("Please enter the first one:");
    if (scanf("%hx", &L_var1) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    printf("Please enter the second one:");
    if (scanf("%hx", &L_var2) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    // Call the add function with the addresses of L_var1, L_var2, and var_out
    var_out = sature(add(L_var1, L_var2));
    var_out_c = add_c(L_var1, L_var2);

    printf("Output_arm: 0x%hx\n", var_out);
    printf("Output_c: 0x%hx\n", var_out_c);
    return 0;  // Exit the program with a success code
}

extern Word32 sub(Word16 L_var1, Word16 L_var2);

Word16 sub_c(Word16 L_var1, Word16 L_var2) {
    return sature_c((Word32)(L_var1 - L_var2));
}

int test_sub() {
    Word32 var_out_temp = 1;  // Initialize var_out to 1
    Word16 var_out = 1;
    Word16 var_out_c = 1;  // Initialize var_out_c to 1

    printf("Enter two 64-bit integer numbers\n");
    
    Word16 L_var1, L_var2;  // Declare two variables to store the user's input
    printf("Please enter the first one:");
    if (scanf("%hx", &L_var1) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    printf("Please enter the second one:");
    if (scanf("%hx", &L_var2) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    // Call the sub function with the addresses of L_var1, L_var2, and var_out
    var_out = sature_c(sub(L_var1, L_var2));
    var_out_c = sub_c(L_var1, L_var2);

    printf("Output_arm: 0x%hx\n", var_out);
    printf("Output_c: 0x%hx\n", var_out_c);
    return 0;  // Exit the program with a success code
}

extern Word16 abss(Word16 L_var);

Word16 abs_c(Word16 L_var) {
    Word16 min_val = INT16_MIN;
    Word16 max_val = INT16_MAX;

    if (L_var == min_val) { 
        return max_val;
    }else if (L_var < 0) {
        return -L_var;
    }else {
        return L_var;
    }
}

int test_abs() {
    Word16 var_out = 1;  // Initialize var_out to 1
    Word16 var_out_c = 1;  // Initialize var_out_c to 1
    // Prompt the user to enter a 64-bit decimal number
    printf("Enter a 16-bit integer number: ");

    Word16 L_var1;  // Declare a variable to store the user's input

    // Read the input as a 64-bit hexadecimal value and store it in L_var1
    if (scanf("%hx", &L_var1) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    var_out = abss(L_var1);
    var_out_c = abs_c(L_var1);

    // Print the value of var_out in hexadecimal format
    printf("Output_arm: 0x%hx\n", var_out);
    printf("Output_c: 0x%hx\n", var_out_c);

    return 0;  // Exit the program with a success code
}

extern Word32 msu(Word32 L_var1, Word16 L_var2, Word16 L_var3);

Word16 msu_c(Word32 L_var1, Word16 L_var2, Word16 L_var3) {
    return sature_c(L_var1 - (L_var2 * L_var3) * 2);
}

int test_msu() {
    Word32 var_out_temp = 1;  // Initialize var_out to 1
    Word16 var_out = 1;
    Word16 var_out_c = 1;  // Initialize var_out_c to 1

    printf("Enter one 64-bit integers and two 32-bit integers\n");

    Word32 L_var1;
    Word16 L_var2, L_var3;
    printf("Please enter the first 64-bit integer:");
    if (scanf("%lx", &L_var1) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    printf("Please enter the first 32-bit integer:");
    if (scanf("%hx", &L_var2) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    printf("Please enter the second 32-bit integer:");
    if (scanf("%hx", &L_var3) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }


    var_out = sature(msu(L_var1, L_var2, L_var3));
    var_out_c = msu_c(L_var1, L_var2, L_var3);

    printf("Output_arm: 0x%hx\n", var_out);
    printf("Output_c: 0x%hx\n", var_out_c);

    return 0;  // Exit the program with a success code
}

Word16 shl_c(Word16 var_in1, Word16 var_in2);
Word16 shr_c(Word16 var_in1, Word16 var_in2);

extern Word16 shl(Word16 var_in1, Word16 var_in2);
extern Word16 shr(Word16 var_in1, Word16 var_in2);

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
    return temp;
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
    return temp;
}

int test_shl_shr() {
    printf("Enter two 16-bit integers\n");

    Word16 var_in1, var_in2;
    printf("Please enter the first one:");
    if (scanf("%hx", &var_in1) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }
    printf("Please enter the second one:");
    if (scanf("%hx", &var_in2) != 1) {
        printf("Invalid input.\n");  // Print an error message if input is invalid
        return 1;                   // Exit the program with an error code
    }

    Word16 var_out_shl;
    Word16 var_out_shr;
    Word16 var_out_c_shl;
    Word16 var_out_c_shr;


    var_out_shl = shl(var_in1, var_in2);
    var_out_shr = shr(var_in1, var_in2);
    var_out_c_shl = shl_c(var_in1, var_in2);
    var_out_c_shr = shr_c(var_in1, var_in2);

    printf("Output_arm_shl: 0x%hx\n", var_out_shl);
    printf("Output_c_shl: 0x%hx\n", var_out_c_shl);
    printf("Output_arm_shr: 0x%hx\n", var_out_shr);
    printf("Output_c_shr: 0x%hx\n", var_out_c_shr);

    return 0;
}

int main() {
    /*
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
    
    */

    //test_sature();  // Call the test_sature function

    //test_add();  // Call the test_add function

    //test_sub();  // Call the test_sub function
    
    //test_abs();

    //test_msu(); 

    test_shl_shr();  // Call the test_shl_shr function (shl and shr)

    return 0;
}
