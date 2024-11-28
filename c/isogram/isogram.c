#include "isogram.h"
#include <stdint.h>
#include <string.h>

#define ABC_LEN 26

bool is_isogram(const char phrase[])
{
    if (phrase == NULL)
    {
        return false;
    }

    uint8_t map[ABC_LEN] = {0};

    size_t phrase_len = strlen(phrase);
    for (size_t i = 0; i < phrase_len; i++)
    {
        int ch = phrase[i];
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
        if (map[i] > 1)
        {
            return false;
        }
    }
    return true;
}
