#include <sys/time.h> 
#include <time.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h> 
#include "typedef.h"

#define BUFFER_SIZE_T 160

extern "C" {
    //extern Word32 L_mac(Word32, Word16, Word16);
    extern Word32 L_mac(Word32, Word32, Word32);
    extern Word16 sature(Word32);
    extern Word16 extract_h(Word32);
    extern Word16 extract_l(Word32);
    //extern Word16 add(Word16, Word16);
    extern Word16 add(Word32, Word32);
    //extern Word16 sub(Word16, Word16);
    extern Word16 sub(Word32, Word32);
    //extern Word32 L_mult(Word16, Word16);
    extern Word32 L_mult(Word32, Word32);
    extern Word32 L_add(Word32, Word32);
    extern Word32 L_sub(Word32, Word32);
    extern Word32 L_abs(Word32);

}

short Overflow;

static inline Word32 L_add_c(Word32 L_var1, Word32 L_var2) {
    Word32 L_var_out;

    L_var_out = L_var1 + L_var2;
    
    if (((L_var1 ^ L_var2) & MIN_32) == 0) {
        if ((L_var_out ^ L_var1) & MIN_32) {
            L_var_out = (L_var1 < 0) ? MIN_32 : MAX_32;
            Overflow = 1;
        }
    }

    return L_var_out;
}

static inline Word32 L_mult_c(Word16 var1, Word16 var2) {
    Word32 L_var_out;
    int tmp = (int)var1 * (int)var2;

    if (tmp != 0x40000000L) {
        L_var_out = tmp * 2;
    } else {
        Overflow = 1;
        L_var_out = MAX_32;
        printf("mult overflow here!\n");
        getchar();
    }

    return L_var_out;
}

static inline Word32 L_mac_c(Word32 L_var3, Word16 var1, Word16 var2) {
    return L_add_c(L_var3, L_mult_c(var1, var2));
}

static inline Word16 extract_h_c(Word32 L_var) {
    return (Word16)(L_var >> 16);
}

static inline Word16 extract_l_c(Word32 L_var) {
    return (Word16)L_var;
}

static inline Word16 sature_c(Word32 L_var) {
    if (L_var > MAX_16) {
        Overflow = 1;
        return MAX_16;
    } else if (L_var < MIN_16) {
        Overflow = 1;
        return MIN_16;
    } else {
        return (Word16)L_var;
    }
}

static inline Word16 add_c(Word16 var1, Word16 var2) {
    return sature_c((Word32)var1 + (Word32)var2);
}

static inline Word16 sub_c(Word16 var1, Word16 var2) {
    return sature_c((Word32)var1 - (Word32)var2);
}

static inline Word32 L_sub_c(Word32 L_var1, Word32 L_var2) {
    Word32 L_var_out = L_var1 - L_var2;
    
    if (((L_var1 ^ L_var2) & MIN_32) != 0) {
        if ((L_var_out ^ L_var1) & MIN_32) {
            L_var_out = (L_var1 < 0) ? MIN_32 : MAX_32;
            Overflow = 1;
        }
    }

    return L_var_out;
}

static inline Word32 L_abs_c(Word32 L_var) {
    Word32 L_var_out;
    
    if (L_var == MIN_32) {
        L_var_out = MAX_32;
    } else if (L_var < 0) {
        L_var_out = -L_var;
    } else {
        L_var_out = L_var;
    }

    return L_var_out;
}

Word16 random_16() {
    return (Word16)rand()%65535 - 32767;
}

Word32 random_32() {
    Word32 random_number = ((Word32)rand() << 16) | rand();
    return (Word32)random_number%4294967295 - 2147483647;
}

int test_sature(Word32 L_var1) {
    Word16 var_out, var_out_c;  // Declare two variables to store the output

    // Call the sature function with the addresses of L_var1 and var_out
    var_out = sature(L_var1);
    var_out_c = sature_c(L_var1);

    //compair the value of two output, return 1 if different
    if (var_out != var_out_c) {
        printf("different in sature 0x%lx=> (0x%hx, 0x%hx)\n", L_var1, var_out, var_out_c);
        return 1;
    }
    return 0;  // Exit the program with a success code
}

int test_L_add(Word32 L_var1, Word32 L_var2) {
    Word32 L_var_out, L_var_out_c;  // Declare two variables to store the output
    
    L_var_out = L_add(L_var1, L_var2);
    L_var_out_c = L_add_c(L_var1, L_var2);

    if (L_var_out != L_var_out_c) {
        printf("different in L_add 0x%lx + 0x%lx=> (0x%lx, 0x%lx)\n", L_var1, L_var2, L_var_out, L_var_out_c);
        return 1;
    }
    return 0;
}

int test_L_mult(Word16 var1, Word16 var2) {
    Word32 L_var_out, L_var_out_c;
    L_var_out = L_mult((Word32)var1, (Word32)var2);
    L_var_out_c = L_mult_c(var1, var2);
    if (L_var_out != L_var_out_c) {
        printf("different in L_mult 0x%hx * 0x%hx=> (0x%lx, 0x%lx)\n", var1, var2, L_var_out, L_var_out_c);
        return 1;
    }
    return 0;
}

int test_L_mac(Word32 L_var3, Word16 var1, Word16 var2) {
    Word32 L_var_out, L_var_out_c;
    L_var_out = L_mac(L_var3, (Word32)var1, (Word32)var2);
    L_var_out_c = L_mac_c(L_var3, var1, var2);
    if (L_var_out != L_var_out_c) {
        printf("different in L_mac 0x%lx + (0x%hx * 0x%hx) * 2=> (0x%lx, 0x%lx)\n", L_var3, var1, var2, L_var_out, L_var_out_c);
        return 1;
    }
    return 0;
}

int test_extract_h(Word32 L_var) {
    Word16 var_out, var_out_c;
    var_out = extract_h(L_var);
    var_out_c = extract_h_c(L_var);
    if (var_out != var_out_c) {
        printf("different in extract_h 0x%lx=> (0x%hx, 0x%hx)\n", L_var, var_out, var_out_c);
        return 1;
    }
    return 0;
}

int test_extract_l(Word32 L_var) {
    Word16 var_out, var_out_c;
    var_out = extract_l(L_var);
    var_out_c = extract_l_c(L_var);
    if (var_out != var_out_c) {
        printf("different in extract_l 0x%lx=> (0x%hx, 0x%hx)\n", L_var, var_out, var_out_c);
        return 1;
    }
    return 0;
}

int test_add(Word16 var1, Word16 var2) {
    Word16 var_out, var_out_c;
    var_out = add((Word32)var1, (Word32)var2);
    var_out_c = add_c(var1, var2);
    if (var_out != var_out_c) {
        printf("different in add 0x%hx + 0x%hx=> (0x%hx, 0x%hx)\n", var1, var2, var_out, var_out_c);
        return 1;
    }
    return 0;
}

int test_sub(Word16 var1, Word16 var2) {
    Word16 var_out, var_out_c;
    var_out = sub(var1, var2);
    var_out_c = sub_c(var1, var2);
    if (var_out != var_out_c) {
        printf("different in sub 0x%hx - 0x%hx=> (0x%hx, 0x%hx)\n", var1, var2, var_out, var_out_c);
        return 1;
    }
    return 0;
}

int test_L_sub(Word32 L_var1, Word32 L_var2) {
    Word32 L_var_out, L_var_out_c;
    L_var_out = L_sub(L_var1, L_var2);
    L_var_out_c = L_sub_c(L_var1, L_var2);
    if (L_var_out != L_var_out_c) {
        printf("different in L_sub 0x%lx - 0x%lx=> (0x%lx, 0x%lx)\n", L_var1, L_var2, L_var_out, L_var_out_c);
        return 1;
    }
    return 0;
}

int test_L_abs(Word32 L_var) {
    Word32 L_var_out, L_var_out_c;
    L_var_out = L_abs(L_var);
    L_var_out_c = L_abs_c(L_var);
    if (L_var_out != L_var_out_c) {
        printf("different in L_abs 0x%lx=> (0x%lx, 0x%lx)\n", L_var, L_var_out, L_var_out_c);
        return 1;
    }
    return 0;
}

void AddExample() {
    short src1[BUFFER_SIZE_T] = {0};
    short src2[BUFFER_SIZE_T] = {0};
    int dst[BUFFER_SIZE_T];
    long long result,result_c,tmp=0, cmp_flag=0;
    int i;
    Word32 L_var1, L_var2;
    Word16 var3, var4;
    srand((unsigned)time( NULL ) );
    i = BUFFER_SIZE_T;
    while (i) {    
        
        L_var1 = random_32();
        L_var2 = random_32();
        var3 = random_16();
        var4 = random_16();
        //print out L_var1, L_var2
        printf("L_var1 = 0x%lx\n", L_var1);
        printf("L_var2 = 0x%lx\n", L_var2);
        printf("var3 = 0x%hx\n", var3);
        printf("var4 = 0x%hx\n\n", var4);

        cmp_flag += test_L_mac(L_var1, var3, var4);
        cmp_flag += test_extract_h(L_var1);
        cmp_flag += test_extract_l(L_var1);
        cmp_flag += test_add(var3, var4);
        cmp_flag += test_sub(var3, var4);
        cmp_flag += test_L_mult(var3, var4);
        cmp_flag += test_L_add(L_var1, L_var2);
        cmp_flag += test_L_sub(L_var1, L_var2);
        cmp_flag += test_L_abs(L_var1);
        i--;
    
    }



    if(cmp_flag)
    {
        printf("Test Done ERROR!!!\n");
    }
    else{
        printf("Test Done PASS!!!\n");
    }
    printf("\n");

    return;
}


int main(void){
	
	double ms_total = 0.0;
	struct timeval tv1, tv2;
	long max_us = 0;
	long us;
	
	int i=1;
	
	while(i)
	{
		gettimeofday(&tv1, 0);
		AddExample();
		gettimeofday(&tv2, 0);
		us = (tv2.tv_sec - tv1.tv_sec)* 1000000 + (tv2.tv_usec - tv1.tv_usec);
		i--;
		ms_total += (float)us/1000;
	}
	
	printf("total proc time = %2f ms\n",ms_total);
	printf("\n");
	
    return 0;
}