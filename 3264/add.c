#include <stdio.h>

int main() {
    long long L_var_out;
    long var1 = 123, var2 = 456;

    __asm__ __volatile__ (
        "ADD x0, x1, x1\n"
        : "+r" (L_var_out)
        : "r" (var1)
    );

    // Print var1 and var2 in hexadecimal
    printf("var1 = %lx, var2 = %lx\n", var1, var2);

    return 0;
}
