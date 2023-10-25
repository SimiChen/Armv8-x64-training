#include "typedef.h"
#include <stdio.h>


static __inline short sature(Word64 L_var1)
{
  
#if    0
	 short var_out;
   if (L_var1 > 0X00007fffL)
     {
     Overflow = 1;
      var_out = MAX_16;
     }
   else if (L_var1 < (Word32)0xffff8000L)
     {
      Overflow = 1;
      var_out = MIN_16;
     }
   else
     {
      Overflow = 0;
      var_out = extract_l(L_var1);
     }
#else
	Word32 var_out;
     __asm__ __volatile__ (
        "LDR r0, %[input_val]\n"   // Load L_var1 into x0
        "LDR r1, %[output_val]\n"  // Load the address of var_out into x2
        "LDR r2, [r0]\n"           // Load the value from x1 into x3
        "STR r1, [r2]\n"           // Store the value in x3 into the address in x2
        : [output_val] "=r" (var_out)
        : [input_val] "r" (L_var1)
        );
#endif
   return((short)var_out);
}


void main() {
    short output;
    output = sature((Word64) 0x00231200031L);
    printf("output: %hd", output);
    
}


