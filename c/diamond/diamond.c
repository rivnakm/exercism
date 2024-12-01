#include "diamond.h"

#include <stdlib.h>
#include <string.h>

char **make_diamond(const char letter)
{
    size_t size = ((letter - 'A' + 1) * 2) - 1;

    char **result = malloc(sizeof(char *) * size);

    size_t midpoint = size / 2;
    for (int i = 0; i < (int)size; i++)
    {
        result[i] = malloc(sizeof(char) * (size + 1));
        memset(result[i], ' ', size);
        result[i][size] = '\0';

        int offset = -midpoint;
        size_t a_pos = abs(offset + i);
        size_t b_pos = size - a_pos - 1;
        char ch = letter - abs(offset + i);

        result[i][a_pos] = ch;
        result[i][b_pos] = ch;
    }

    return result;
}

void free_diamond(char **diamond)
{
    size_t size = *diamond == NULL ? 0 : strlen(diamond[0]);
    for (size_t i = 0; i < size; i++)
    {
        free(diamond[i]);
    }
    free(diamond);
}
