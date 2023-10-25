#include <stdio.h>
#include <stdint.h>

int main() {
    double doubleValue = 3.141592653589793; // Replace this with the double value you want to convert
    double doubleValue2 = -3.141592653589793;
    // Create a union to hold the double value and its 64-bit hexadecimal representation
    union {
        double doubleValue;
        uint64_t hexValue;
    } converter;

    converter.doubleValue = doubleValue;

    // Print the double value and its 64-bit hexadecimal representation
    printf("Double Value: %f\n", converter.doubleValue);
    printf("64-bit Hexadecimal Representation: 0x%llx\n", (unsigned long long)converter.hexValue);


    converter.doubleValue = doubleValue2;

    // Print the double value and its 64-bit hexadecimal representation
    printf("Double Value: %f\n", converter.doubleValue);
    printf("64-bit Hexadecimal Representation: 0x%llx\n", (unsigned long long)converter.hexValue);


    return 0;
}
