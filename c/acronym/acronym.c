#include "acronym.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase)
{
    if (phrase == NULL)
    {
        return NULL;
    }

    size_t len = strlen(phrase);
    if (len == 0)
    {
        return NULL;
    }

    char *result = malloc(sizeof(char) * (len + 1));
    size_t letters = 0;

    bool split = true;
    for (size_t i = 0; i < len; i++)
    {
        char ch = phrase[i];
        if (isalpha(ch) || ch == '\'')
        {
            if (split)
            {
                split = false;
                result[letters++] = toupper(ch);
            }
        }
        else
        {
            split = true;
        }
    }

    result = realloc(result, sizeof(char) * (letters + 1));
    result[letters] = '\0';

    return result;
}
