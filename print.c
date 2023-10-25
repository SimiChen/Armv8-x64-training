#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate a random number between 0 and RAND_MAX
    int randomNum = rand();

    // Print the random number
    printf("Random Number: %d\n", randomNum);


    int c = 0x00123111;

    int d = ~c >> 4;

    printf("c: %08x,  d: %08x, %d\n", c, d, d);


    return 0;
}

