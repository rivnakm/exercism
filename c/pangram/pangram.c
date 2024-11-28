#include "pangram.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define ABC_LEN 26

bool is_pangram(const char *sentence)
{
    if (sentence == NULL)
    {
        return false;
    }

    uint8_t map[ABC_LEN] = {0};

    size_t sentence_len = strlen(sentence);
    for (size_t i = 0; i < sentence_len; i++)
    {
        int ch = sentence[i];
        // Uppercase letters
        if (ch >= 65 && ch <= 90)
        {
            size_t idx = ch - 65;
            map[idx]++;
        }
        // Lowercase letters
        else if (ch >= 97 && ch <= 122)
        {
            size_t idx = ch - 97;
            map[idx]++;
        }
    }

    for (size_t i = 0; i < ABC_LEN; i++)
    {
        if (map[i] == 0)
        {
            return false;
        }
    }
    return true;
}
