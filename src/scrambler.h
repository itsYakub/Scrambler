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
    char* scrableMoveset;
    char* scrambleModifiers;
} scrambleConfig;

// Initializing the `random number generation` based on the seed
void scrambleInitRandomNumberGenerator(int seed);

// Generating the `scramble` by specifying the `generation's mode`
void scrambleGenenrateByMode(scrambleMove* moves, scrambleMode mode);
// Generating the `scramble` by giving the generator a `custom configuration`
void scrambleGenenrateByConfig(scrambleMove* moves, scrambleConfig config);

// Generating the `scramble string` by specifying the `generation's mode`
// `WARNING`: generated strings are allocated on the heap memory; after using them remember to call `free()` or `delete`
char* scrambleGenerateAsStringByMode(scrambleMode mode);
// Generating the `scramble string` by giving the generator a `custom configuration`
// `WARNING`: generated strings are allocated on the heap memory; after using them remember to call `free()` or `delete`
char* scrambleGenerateAsStringByConfig(scrambleConfig config);

// Generating the new `scramble config object`
scrambleConfig scrambleGenerateConfigObject(unsigned int len, char* moveset, char* modifiers);

// The constant list of all default `configurations`
const scrambleConfig scrambleConfigurations[2] = { 
    { 9, "URF", " '2" },
    { 20, "UDRLFB", " '2" } 
};

#ifdef SCRAMBLER_IMPLEMENTATION

#include <stdlib.h>
#include <string.h>
#include <time.h>

void scrambleInitRandomNumberGenerator(int seed){
    srand(seed);
}

void scrambleGenenrateByMode(scrambleMove* moves, scrambleMode mode){
    for (int i = 0; i < (int)scrambleConfigurations[mode].scrambleLength; i++) {
        do {
            moves[i].move = scrambleConfigurations[mode].scrableMoveset[rand() % strlen(scrambleConfigurations[mode].scrableMoveset)];
        } while (moves[i].move == moves[i - 1].move || moves[i].move == moves[i - 2].move);

        moves[i].modifier = scrambleConfigurations[mode].scrambleModifiers[rand() % strlen(scrambleConfigurations[mode].scrambleModifiers)];
    }
}

char* scrambleGenerateAsStringByMode(scrambleMode mode){
    scrambleMove scramble[scrambleConfigurations[mode].scrambleLength];
    scrambleGenenrateByMode(scramble, mode);

    int scrambleTextTotalSize = scrambleConfigurations[mode].scrambleLength * 3;
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

    return scrambleText;
}

void scrambleGenenrateByConfig(scrambleMove* moves, scrambleConfig config){
    for (int i = 0; i < (int)config.scrambleLength; i++) {
        do {
            moves[i].move = config.scrableMoveset[rand() % strlen(config.scrableMoveset)];
        } while (moves[i].move == moves[i - 1].move || moves[i].move == moves[i - 2].move);

        moves[i].modifier = config.scrambleModifiers[rand() % strlen(config.scrambleModifiers)];
    }
}

char* scrambleGenerateAsStringByConfig(scrambleConfig config){
    scrambleMove scramble[config.scrambleLength];
    scrambleGenenrateByConfig(scramble, config);

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

    return scrambleText;
}

scrambleConfig scrambleGenerateConfigObject(unsigned int len, char* moveset, char* modifiers){
    return (scrambleConfig){ len, moveset, modifiers };
}

#endif

#endif