#include "typedef.h"   // Include typedef.h header file for data type definitions
#include <stdio.h>     // Include standard I/O header file
#include <stdint.h>

int Overflow;

Word32 L_sub(Word32 L_var1, Word32 L_var2)
  {
   Word32 L_var_out;

   L_var_out = L_var1 - L_var2;
    Word32 temps;
        temps = L_var1 ^ L_var2;
        printf("temps=%lx\n", temps);
        temps = temps & MIN_32;
        printf("temps=%lx\n", temps);
        temps = L_var_out ^ L_var1;
        printf("temps=%lx\n", temps);
   if (((L_var1 ^ L_var2) & MIN_32) != 0)
     {
      if ((L_var_out ^ L_var1) & MIN_32)
        {
         L_var_out = (L_var1 < 0L) ? MIN_32 : MAX_32;
         Overflow = 1;
        }
     }
   return(L_var_out);
  }

int main()
{   

    Word32 var_1;
    Word32 var_2;
    printf("Enter two 32-bit integers in hex form\n");
    if (scanf("%lx %lx", &var_1, &var_2) != 2) {
        printf("Invalid input.\n");  
        return 1;                 
    };

    Word32 result = L_sub(var_1, var_2);
    printf("Result: %lx\n", result);

    return 0;
}
