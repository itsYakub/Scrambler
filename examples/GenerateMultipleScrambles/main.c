// Example no. 3.: Generating multiple scrambles
// Compile command (using GCC): gcc -g main.c -I../../src

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCRAMBLER_IMPLEMENTATION
#include "scrambler.h"

int main(void) {
    scrambleInitRandomNumberGenerator(time(NULL));
    char* scramble = scrambleGenerateAsStringByMode(MODE_3X3);

    for(int i = 0; i < 8; i++) {
        printf("%i. %s\n", i + 1, scramble);

        scramble = scrambleGenerateAsStringByMode(MODE_3X3);
    }
    
    free(scramble);

    return 0;
}