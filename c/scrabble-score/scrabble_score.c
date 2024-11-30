#include "scrabble_score.h"
#include <ctype.h>
#include <stddef.h>
#include <string.h>

unsigned int letter_score(char letter);

unsigned int score(const char *word)
{
    unsigned int score = 0;
    size_t len = strlen(word);
    for (size_t i = 0; i < len; i++)
    {
        score += letter_score(word[i]);
    }

    return score;
}

unsigned int letter_score(char letter)
{
    letter = toupper(letter);
    switch (letter)
    {
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
    case 'L':
    case 'N':
    case 'R':
    case 'S':
    case 'T':
        return 1;
    case 'D':
    case 'G':
        return 2;
    case 'B':
    case 'C':
    case 'M':
    case 'P':
        return 3;
    case 'F':
    case 'H':
    case 'V':
    case 'W':
    case 'Y':
        return 4;
    case 'K':
        return 5;
    case 'J':
    case 'X':
        return 8;
    case 'Q':
    case 'Z':
        return 10;
    default:
        return 0;
    }
}
