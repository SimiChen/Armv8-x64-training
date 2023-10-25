#include <stdio.h>

extern void multiply(int *array1, int *array2, int *result);

int main() {
    // Declare an array of four single-precision floating-point numbers
    int array1[] = {4, 23, 12, 4};
    int array2[] = {1, 2, 3, 4};
    int result[4];

    multiply(array1, array2, result);

    printf("Result: %d %d %d %d\n", result[0], result[1], result[2], result[3]);

    return 0;
}
