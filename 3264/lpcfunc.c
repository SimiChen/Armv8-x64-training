
#include "ld8a.h"
#include "tab_ld8a.h"
#include "basic_op.h"

static void Get_lsp_pol(short *lsp, int *f);

void g729ab_Lsp_Az(
  short lsp[],    /* (i) Q15 : line spectral frequencies            */
  short a[]       /* (o) Q12 : predictor coefficients (order = 10)  */
)
{
  register short i, j;
  int f1[6], f2[6];
  int t0;

  Get_lsp_pol(&lsp[0],f1);
  Get_lsp_pol(&lsp[1],f2);

  for (i = 5; i > 0; i--)
  {
	f1[i] += f1[i-1]; 
	f2[i] -= f2[i-1];
  }

  a[0] = 4096;
  for (i = 1, j = 10; i <= 5; i++, j--)
  {
	t0 = f1[i] + f2[i];
    a[i] = (short)( t0 >> 13 );        /* from Q24 to Q12 and * 0.5 */
	if((t0 & 0x00001000) != 0) a[i]++;

	t0 = f1[i] - f2[i];
    a[j] = (short)( t0 >> 13 );        /* from Q24 to Q12 and * 0.5 */
	if((t0 & 0x00001000) != 0) a[j]++;

  }

  return;
}

/*-----------------------------------------------------------*
 * procedure Get_lsp_pol:                                    *
 *           ~~~~~~~~~~~                                     *
 *   Find the polynomial F1(z) or F2(z) from the LSPs        *
 *-----------------------------------------------------------*
 *                                                           *
 * Parameters:                                               *
 *  lsp[]   : line spectral freq. (cosine domain)    in Q15  *
 *  f[]     : the coefficients of F1 or F2           in Q24  *
 *-----------------------------------------------------------*/

static void Get_lsp_pol(short *lsp, int *f) //x0, x1
{

  short hi, lo, hi1, lo1;
  int t0, t01;

   /* All computation in Q24 */
   //f  8pcs f[i] = [x0, 4*i]
   //x2 = #1
   //str #0x1000000L, [x1]
   f[0] = 0x1000000L;             /* f[0] = 1.0;             in Q24  */
   //ldrh w3, [x0]
   //
   f[1] = - ((int)lsp[0] << 10); 

//i = 2
//x8 = i 
//x9 = x8
//fun f
   f[2] = f[0]; //f[i] = f[i-2]
    //inner loop 24d23456
   hi  = (short)(f[1] >> 16);
   lo  = (short)((f[1] >> 1) - ((int)hi<<15) );  
   t0 = (int)hi * (int)lsp[2];
   t0 += (int)lo * (int)lsp[2] >> 15;
   t0 <<= 2;

   //t0 = f[1] * lsp[2] >> 16
   f[2] += f[0];
   f[2] -= t0;
   
   //if x9 > 2: x9 -= 1, call f
   //f[1] -= (int)lsp[x8*2-2] << 10;
   f[1] -= (int)lsp[2] << 10;

//	i = 3 and i = 2
   f[3] = f[1];

   hi  = (short)(f[2] >> 16);                        //f[2] high bit
   hi1  = (short)(f[1] >> 16);                       
   lo  = (short)((f[2] >> 1) - ((int)hi<<15) );     //f[2] & #65535 >> 1; 
   lo1  = (short)((f[1] >> 1) - ((int)hi1<<15) );   
   t0 = (int)hi * (int)lsp[4];
   t01 = (int)hi1 * (int)lsp[4];
   t0 += (int)lo * (int)lsp[4] >> 15;
   t01 += (int)lo1* (int)lsp[4] >> 15;
   t0 <<= 2;
   t01 <<= 2;
   f[3] += f[1];
   f[2] += f[0];
   f[3] -= t0;
   f[2] -= t01;

   f[1] -= (int)lsp[4] << 10;

//	i = 4 i=3 i=2
   f[4] = f[2];

   hi  = (short)(f[3] >> 16);
   hi1  = (short)(f[2] >> 16);
   lo  = (short)((f[3] >> 1) - ((int)hi<<15) );  
   lo1  = (short)((f[2] >> 1) - ((int)hi1<<15) );  
   t0 = (int)hi * (int)lsp[6];
   t01 = (int)hi1 * (int)lsp[6];
   t0 += (int)lo * (int)lsp[6] >> 15;
   t01 += (int)lo1 * (int)lsp[6] >> 15;
   t0 <<= 2;
   t01 <<= 2;
   f[4] += f[2];
   f[4] -= t0;
   f[3] += f[1];
   f[3] -= t01;

   hi  = (short)(f[1] >> 16);
   lo  = (short)((f[1] >> 1) - ((int)hi<<15) );  
   t0 = (int)hi * (int)lsp[6];
   t0 += (int)lo * (int)lsp[6] >> 15;
   t0 <<= 2;
   f[2] += f[0];
   f[2] -= t0;

   f[1] -= (int)lsp[6] << 10;

//	i = 5432
   f[5] = f[3];

   hi  = (short)(f[4] >> 16);
   hi1  = (short)(f[3] >> 16);
   lo  = (short)((f[4] >> 1) - ((int)hi<<15) );  
   lo1  = (short)((f[3] >> 1) - ((int)hi1<<15) );  
   t0 = (int)hi * (int)lsp[8];
   t01 = (int)hi1 * (int)lsp[8];
   t0 += (int)lo * (int)lsp[8] >> 15;
   t01 += (int)lo1 * (int)lsp[8] >> 15;
   t0 <<= 2;
   t01 <<= 2;
   f[5] += f[3];
   f[5] -= t0;
   f[4] += f[2];
   f[4] -= t01;



   hi  = (short)(f[2] >> 16);
   hi1  = (short)(f[1] >> 16);
   lo  = (short)((f[2] >> 1) - ((int)hi<<15) );  
   lo1  = (short)((f[1] >> 1) - ((int)hi1<<15) );  
   t0 = (int)hi * (int)lsp[8];
   t01 = (int)hi1 * (int)lsp[8];
   t0 += (int)lo * (int)lsp[8] >> 15;
   t01 += (int)lo1 * (int)lsp[8] >> 15;
   t0 <<= 2;
   t01 <<= 2;
   f[3] += f[1];
   f[3] -= t0;
   f[2] += f[0];
   f[2] -= t01;

   f[1] -= (int)lsp[8] << 10;

   return;
}

/*___________________________________________________________________________
 |                                                                           |
 |   Functions : Lsp_lsf and Lsf_lsp                                         |
 |                                                                           |
 |      Lsp_lsf   Transformation lsp to lsf                                  |
 |      Lsf_lsp   Transformation lsf to lsp                                  |
 |---------------------------------------------------------------------------|
 |  Algorithm:                                                               |
 |                                                                           |
 |   The transformation from lsp[i] to lsf[i] and lsf[i] to lsp[i] are       |
 |   approximated by a look-up table and interpolation.                      |
 |___________________________________________________________________________|
*/


void Lsf_lsp(
  short lsf[],    /* (i) Q15 : lsf[m] normalized (range: 0.0<=val<=0.5) */
  short lsp[],    /* (o) Q15 : lsp[m] (range: -1<=val<1)                */
  short m         /* (i)     : LPC order                                */
)
{
  register short i;
  short ind, offset;
  int L_tmp;

  for(i=0; i<m; i++)
  {
    ind    = lsf[i] >> 8;               /* ind    = b8-b15 of lsf[i] */
    offset = lsf[i] & (short)0x00ff;      /* offset = b0-b7  of lsf[i] */

    /* lsp[i] = table[ind]+ ((table[ind+1]-table[ind])*offset) / 256 */

    L_tmp   = (table[ind+1] - table[ind]) * offset;
    lsp[i] = table[ind] + (short)(L_tmp >> 8);
  }
  return;
}


void Lsp_lsf(
  short lsp[],    /* (i) Q15 : lsp[m] (range: -1<=val<1)                */
  short lsf[],    /* (o) Q15 : lsf[m] normalized (range: 0.0<=val<=0.5) */
  short m         /* (i)     : LPC order                                */
)
{
  register short i;
  short ind, tmp;
  int L_tmp;

  ind = 63;    /* begin at end of table -1 */

  for(i= m-1; i >= 0; i--)
  {
    /* find value in table that is just greater than lsp[i] */
    while( table[ind] < lsp[i] ) ind--;

    /* acos(lsp[i])= ind*256 + ( ( lsp[i]-table[ind] ) * slope[ind] )/4096 */

    L_tmp  = (lsp[i] - table[ind]) * slope[ind];
	L_tmp += 0x00000800;
    tmp = (short)(L_tmp>>12);     /*(lsp[i]-table[ind])*slope[ind])>>12*/
    lsf[i] = tmp + (ind << 8);
  }
  return;
}

/*___________________________________________________________________________
 |                                                                           |
 |   Functions : Lsp_lsf and Lsf_lsp                                         |
 |                                                                           |
 |      Lsp_lsf   Transformation lsp to lsf                                  |
 |      Lsf_lsp   Transformation lsf to lsp                                  |
 |---------------------------------------------------------------------------|
 |  Algorithm:                                                               |
 |                                                                           |
 |   The transformation from lsp[i] to lsf[i] and lsf[i] to lsp[i] are       |
 |   approximated by a look-up table and interpolation.                      |
 |___________________________________________________________________________|
*/

void Lsf_lsp2(
  short lsf[],    /* (i) Q13 : lsf[m] (range: 0.0<=val<PI) */
  short lsp[],    /* (o) Q15 : lsp[m] (range: -1<=val<1)   */
  short m         /* (i)     : LPC order                   */
)
{
  register short i;
  short ind;
  short offset;   /* in Q8 */
  short freq;     /* normalized frequency in Q15 */
  int L_tmp;

  for(i=0; i<m; i++)
  {
	freq = lsf[i] * 20861 >> 15;
    ind    = freq >> 8;               /* ind    = b8-b15 of freq */
    offset = freq & (short)0x00ff;      /* offset = b0-b7  of freq */

    /* lsp[i] = table2[ind]+ (slope_cos[ind]*offset >> 12) */

    L_tmp   = slope_cos[ind] * offset;   /* L_tmp in Q28 */
    lsp[i] = table2[ind] + (short)(L_tmp >> 12);

  }
  return;
}


void Lsp_lsf2(
  short lsp[],    /* (i) Q15 : lsp[m] (range: -1<=val<1)   */
  short lsf[],    /* (o) Q13 : lsf[m] (range: 0.0<=val<PI) */
  short m         /* (i)     : LPC order                   */
)
{
  register short i;
  short ind;
  short ind1[10];
  short ind2[10];
  short offset;   /* in Q15 */
  short freq;     /* normalized frequency in Q16 */
  int L_tmp;


  for (i=0; i<m; i++) {
	ind = 32;
	if(lsp[i] > table2[ind]) ind -= 16;
	else ind += 16;
	if(lsp[i] > table2[ind]) ind -= 8;
	else ind += 8;
	if(lsp[i] > table2[ind]) ind -= 4;
	else ind += 4;
	if(lsp[i] > table2[ind]) ind -= 2;
	else ind += 2;
	if(lsp[i] > table2[ind]) ind -= 1;
	else ind += 1;

	if(lsp[i] > table2[ind]) ind -= 1;


	ind1[i] = ind;
  }


  i = 9;
  for(ind = 63; ind >=0; ind--)
  {
	  if(table2[ind] >= lsp[i]) {
		  ind1[i] = ind;
		  i--;
		  ind++;
		  if(i < 0) goto done;
	  }

  }

done:
   ind = 63;           /* begin at end of table2 -1 */
 for(i= m-1; i >= 0; i--)
  {
    /* find value in table2 that is just greater than lsp[i] */
    while( table2[ind] < lsp[i] )
  {
      ind--;
      if ( ind <= 0 )
        break;
    }
	ind2[i] = ind;

#ifdef _MSC_VER
	if(ind2[i] != ind1[i]) _asm int 3;
#endif

	ind = ind1[i];

    offset = lsp[i] - table2[ind];

    /* acos(lsp[i])= ind*512 + (slope_acos[ind]*offset >> 11) */

    L_tmp  = slope_acos[ind] * offset;   /* L_tmp in Q28 */
    freq = (ind << 9) + (short)(L_tmp >> 11);
	lsf[i] = freq * 25736 >> 15;

  }
  return;
}


/*----------------------------------------------------------------------*
 * Function Int_qlpc()                                                  *
 * ~~~~~~~~~~~~~~~~~~~                                                  *
 * Interpolation of the LPC parameters.                                 *
 *----------------------------------------------------------------------*/

/* Interpolation of the quantized LSP's */

void Int_qlpc(
 short lsp_old[], /* input : LSP vector of past frame              */
 short lsp_new[], /* input : LSP vector of present frame           */
 short Az[]       /* output: interpolated Az() for the 2 subframes */
)
{
  register short i;
  short lsp[M];

  /*  lsp[i] = lsp_new[i] * 0.5 + lsp_old[i] * 0.5 */

  for (i = 0; i < M; i++) {
    lsp[i] = (lsp_new[i] >> 1) + (lsp_old[i] >> 1);
  }

  g729ab_Lsp_Az(lsp, Az);              /* Subframe 1 */

  g729ab_Lsp_Az(lsp_new, &Az[MP1]);    /* Subframe 2 */

  return;
}


