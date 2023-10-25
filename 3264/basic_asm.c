
/*___________________________________________________________________________
 |                                                                           |
 |   Constants and Globals                                                   |
 |___________________________________________________________________________|
*/

/*___________________________________________________________________________
 |                                                                           |
 |   Operators prototypes                                                    |
 |___________________________________________________________________________|
*/
#include "typedef.h"



static __inline short sature(Word32 L_var1)
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
     __asm__ __volatile__ ("SSAT %0, 16, %1\n"
  :"=r" (var_out):"r"(L_var1));
#endif
   return((short)var_out);
}


/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : add                                                     |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |    Performs the addition (var1+var2) with overflow control and saturation;|
 |    the 16 bit result is set at +32767 when overflow occurs or at -32768   |
 |    when underflow occurs.                                                 |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (short) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (short) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (short) whose value falls in the |
 |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
 |___________________________________________________________________________|
*/

static __inline short add(short var1,short var2)
  {
   
#if    0
  short var_out;
   Word32 L_somme;

   L_somme = (Word32) var1 + var2;
   var_out = sature(L_somme);
#else
  Word32 var_out;
   __asm__ __volatile__ ("QADD16 %0, %1, %2\n"
 :"=r" (var_out):"r"((int)var1),"r"((int)var2));
#endif
   return((short)var_out);
  }

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : sub                                                     |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |    Performs the subtraction (var1+var2) with overflow control and satu-   |
 |    ration; the 16 bit result is set at +32767 when overflow occurs or at  |
 |    -32768 when underflow occurs.                                          |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (short) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (short) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (short) whose value falls in the |
 |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
 |___________________________________________________________________________|
*/

static __inline short sub(short var1,short var2)
  {

#if    0
   short var_out;
   Word32 L_diff;

   L_diff = (Word32) var1 - var2;
   var_out = sature(L_diff);
#else
  Word32 var_out;
   __asm__ __volatile__ ("QSUB16 %0,%1,%2\n"
 :"=r" (var_out):"r"((int)var1),"r"((int)var2));
#endif
   return((short)var_out);
  }

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : abs_s                                                   |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |    Absolute value of var1; abs_s(-32768) = 32767.                         |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (short) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (short) whose value falls in the |
 |             range : 0x0000 0000 <= var_out <= 0x0000 7fff.                |
 |___________________________________________________________________________|
*/

static __inline short abs_s(short var1)
  {
   
#if    0
	short var_out;
   if (var1 == (short)0X8000 )
     {
      var_out = MAX_16;
     }
   else
     {
      if (var1 < 0)
        {
         var_out = -var1;
        }
      else
        {
         var_out = var1;
        }
      }
#else
	Word32 var_out;
    __asm__ __volatile__ ("MOV   %0, %1, LSL#16\n"
	"SUB   %0, %0, %0, LSR#31\n"
	"EOR   %0, %0, %0, ASR#31\n"
	"MOV   %0, %0, ASR#16\n"
 :"+r" (var_out):"r"((int)var1));
#endif
    return((short)var_out);
  }




/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : L_mac                                                   |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Multiply var1 by var2 and shift the result left by 1. Add the 32 bit    |
 |   result to L_var3 with saturation, return a 32 bit result:               |
 |        L_mac(L_var3,var1,var2) = L_add(L_var3,(L_mult(var1,var2)).        |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    L_var3   32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (short) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (short) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    L_var_out                                                              |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
 |___________________________________________________________________________|
*/

static __inline Word32 L_mac(Word32 L_var3, short var1, short var2)
  {
   Word32 L_var_out;
#if	0
   Word32 L_produit;
   L_produit = L_mult(var1,var2);
   L_var_out = L_add(L_var3,L_produit);
#else
       __asm__ __volatile__ ("SMULBB %0, %2, %3\n"
	"QDADD  %0, %1,%0\n"
  :"+r" (L_var_out):"r"(L_var3),"r"(var1),"r"(var2));
#endif
   return(L_var_out);
  }

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : L_sub                                                   |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   32 bits subtraction of the two 32 bits variables (L_var1-L_var2) with   |
 |   overflow control and saturation; the result is set at +214783647 when   |
 |   overflow occurs or at -214783648 when underflow occurs.                 |
 |                                                                           |
 |   Complexity weight : 2                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    L_var1   32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
 |                                                                           |
 |    L_var2   32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    L_var_out                                                              |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
 |___________________________________________________________________________|
*/

static __inline Word32 L_sub(Word32 L_var1, Word32 L_var2)
  {
   Word32 L_var_out;
#if    0
   L_var_out = L_var1 - L_var2;

   if (((L_var1 ^ L_var2) & MIN_32) != 0)
     {
      if ((L_var_out ^ L_var1) & MIN_32)
        {
         L_var_out = (L_var1 < 0L) ? MIN_32 : MAX_32;
         Overflow = 1;
        }
     }
#else
   __asm__ __volatile__ ("QSUB %0 , %1, %2\n"
  :"=r" (L_var_out):"r"(L_var1),"r"(L_var2));
#endif
   return(L_var_out);
  }


/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : L_msu                                                   |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Multiply var1 by var2 and shift the result left by 1. Subtract the 32   |
 |   bit result to L_var3 with saturation, return a 32 bit result:           |
 |        L_msu(L_var3,var1,var2) = L_sub(L_var3,(L_mult(var1,var2)).        |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    L_var3   32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (short) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (short) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    L_var_out                                                              |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
 |___________________________________________________________________________|
*/

static __inline Word32 L_msu(Word32 L_var3, short var1, short var2)
  {
   Word32 L_var_out;
#if    0
   Word32 L_produit;

   L_produit = L_mult(var1,var2);
   L_var_out = L_sub(L_var3,L_produit);
#else
    __asm__ __volatile__ ("SMULBB %0, %2, %3\n"
  "QDSUB  %0, %1,%0\n"
  :"+r" (L_var_out):"r"(L_var3),"r"(var1),"r"(var2));
#endif
   return(L_var_out);
  }



/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : L_abs                                                   |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |    Absolute value of L_var1; Saturate in case where the input is          |
 |                                                               -214783648  |
 |                                                                           |
 |   Complexity weight : 3                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    L_var1                                                                 |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= var1 <= 0x7fff ffff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    L_var_out                                                              |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x0000 0000 <= var_out <= 0x7fff ffff.                |
 |___________________________________________________________________________|
*/

static __inline Word32 L_abs(Word32 L_var1)
  {
   Word32 L_var_out;
#if   0
   if (L_var1 == MIN_32)
     {
      L_var_out = MAX_32;
     }
   else
     {
      if (L_var1 < 0)
        {
         L_var_out = -L_var1;
        }
      else
        {
         L_var_out = L_var1;
        }
     }
#else
    __asm__ __volatile__ ("SUB   %0, %1, %1, LSR#31\n"
	"EOR   %0, %0, %0, ASR#31\n"
  :"+r" (L_var_out):"r"(L_var1));
#endif
   return(L_var_out);
  }
