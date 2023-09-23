# Scrambler
<B>Single-Header Rubik's cube scrambling tool made in C!</B>

# Example
```c
#include <stdio.h>

#define SCRAMBLER_IMPLEMENTATION
#include "scrambler.h"

int main(void) {
    char* scramble = scrambleGenerateString(scrambleGetConfiguration(MODE_3X3));

    printf("%s\n", scramble);

    free(scramble);

    return 0;
}
```

# Description
<B>Scrambler</B> is a single-header library for scrambling the twisty puzzles written in C. It's simplicity and design allows to simply drag and drop the `scrambler.h` file into your project and use it however you'd like to! You can use pre-defined configurations and even create your own settings which then scrambler will use to output the desired scramble.

# Informations:
- `#define SCRAMBLER_IMPLEMENTATION` - Scrambler is single-header library, and to make it work you need to define the macro `SCRAMBLER_IMPLEMENTATION` somewhere in your code. <B>THIS MACRO MUST BE DEFINED ONLY ONCE, OTHERWISE THE COMPILER WON'T COMPILE THE PROJECT PROPERLY</B>;
- `Heap allocation` - currently the project uses dynamically-allocated string to output the scramble as text. Remember to call the `free()` or `delete` at the end of your program to prevent memory leaks;

# Licensing
This project uses the [MIT](https://github.com/itsYakub/Scrambler/blob/main/LICENSE) license.
