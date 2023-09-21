// Example no. 1.: Generating scramble by the mode
// Compile command (using GCC): gcc -g main.c -I../../src

#include <stdio.h>

#define SCRAMBLER_IMPLEMENTATION
#include "scrambler.h"

int main(void) {
    char* scramble = scrambleGenerateAsStringByMode(MODE_3X3);

    printf("Scramble generated by: \"Mode\": %s", scramble);

    free(scramble);

    return 0;
}