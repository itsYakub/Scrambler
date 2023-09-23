#ifndef SCRAMBLER_H
#define SCRAMBLER_H

/*
    Scramble Mode: enum containing the index list of default scrambling configurations:
    - `MODE_2X2`: Mode for scrambling the 2x2 cube (length: 9, moveset: "URF", modifiers: " '2");
    - `MODE_3x3`: Mode for scrambling the 3x3 cube (length: 20, moveset: "UDRLFB", modifiers: " '2");
*/
typedef enum {
    MODE_2X2 = 0,
    MODE_3X3 = 1
} scrambleMode;

/*
    Scramble Move: struct containing the crucial informations about:
    - `move`: the specific move int the scramble;
    - `modifier`: the modifiaction of the current move;
*/
typedef struct {
    char move;
    char modifier;
} scrambleMove;

/*
    Scramble Config: struct that contains the data about:
    - `scrambleLength`: the length of the scramble (i. e. length of 20 for 3x3 cube);
    - `scrambleMoveset`: what moveset does the configuration use;
    - `scrambleModifiers`: what modifiers does the configuration use;
*/
typedef struct{
    unsigned int scrambleLength;
    char* scrambleMoveset;
    char* scrambleModifiers;
} scrambleConfig;

// Initializing the `random number generation` based on the seed
void scrambleInitRandomNumberGenerator(int seed);

// Generating the `scramble` by specifying the `generation's configuration`
scrambleMove* scrambleGenenrate(scrambleConfig config);

// Generating the `scramble string` by specifying the `generation's configuration`
char* scrambleGenerateString(scrambleConfig config);

// Generating the new `scramble config object`
scrambleConfig scrambleGenerateConfigObject(unsigned int len, char* moveset, char* modifiers);
// Retriving the `default configurations` by specifying the desired `mode`
scrambleConfig scrambleGetConfiguration(scrambleMode mode);

// The constant list of all default `configurations`
const scrambleConfig scrambleConfigurations[2] = { 
    { 9, "URF", " '2" },
    { 20, "UDRLFB", " '2" }
};

#ifdef SCRAMBLER_IMPLEMENTATION

#include <stdlib.h>
#include <string.h>

void scrambleInitRandomNumberGenerator(int seed){
    // Initialize the random number generation based on the seed
    srand(seed);
}

scrambleMove* scrambleGenenrate(scrambleConfig config){
    scrambleMove* moves = malloc(config.scrambleLength * sizeof(scrambleMove));

    for (int i = 0; i < (int)config.scrambleLength; i++) {
        do {
            moves[i].move = config.scrambleMoveset[rand() % strlen(config.scrambleMoveset)];
        } while (moves[i].move == moves[i - 1].move || moves[i].move == moves[i - 2].move);

        moves[i].modifier = config.scrambleModifiers[rand() % strlen(config.scrambleModifiers)];
    }

    return moves;
}

char* scrambleGenerateString(scrambleConfig config){
    // Generate the moves needed to build the whole scramble
    scrambleMove* scramble;
    scramble = scrambleGenenrate(config);

    int scrambleTextTotalSize = config.scrambleLength * 3;
    char* scrambleText = malloc(scrambleTextTotalSize * sizeof(char));

    int lastIndexOfTheString = 0;

    // Firstly: insert the moves into the string
    for(int i = 0; i < scrambleTextTotalSize; i += 3){
        scrambleText[i] = scramble[i / 3].move;
        lastIndexOfTheString++;
    }

    // Secondly: insert the modifiers into the string
    for(int i = 1; i < scrambleTextTotalSize; i += 3){
        scrambleText[i] = scramble[i / 3].modifier;
        lastIndexOfTheString++;
    }

    // Thirdly: insert the whitespaces into the string
    for(int i = 2; i < scrambleTextTotalSize - 1; i += 3){
        scrambleText[i] = ' ';
        lastIndexOfTheString++;
    }

    // Lastly: add the EOL character, signifying the end of the string
    scrambleText[lastIndexOfTheString] = '\0';

    free(scramble);

    return scrambleText;
}


scrambleConfig scrambleGenerateConfigObject(unsigned int len, char* moveset, char* modifiers){
    return (scrambleConfig) { len, moveset, modifiers };
}

scrambleConfig scrambleGetConfiguration(scrambleMode mode){
    // The reason I don't just return the 'scrambleConfigurations[mode]' is the error checking; user can type an invalid index, so to prevent this I use a simple switch statement, and if the index is valid, then I return the 'scrambleConfigurations[mode]', otherwise I default it to the 'MODE_3x3'
    switch (mode) {
        case MODE_2X2: return scrambleConfigurations[mode];
        case MODE_3X3: return scrambleConfigurations[mode];
        default: return scrambleConfigurations[MODE_3X3]; // If the 'scrambleMode' index isn't valid, then default to the 3x3 mode
    }
}

#endif

#endif