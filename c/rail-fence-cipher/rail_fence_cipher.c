#include "rail_fence_cipher.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *encode(char *text, size_t rails)
{
    size_t row_len = strlen(text);
    char *intermediate = malloc((row_len * rails) + 1);

    memset(intermediate, '\0', (row_len * rails) + 1);

    bool increasing = true;
    size_t row = 0;
    for (size_t col = 0; col < row_len; col++)
    {
        intermediate[(row * row_len) + col] = text[col];

        if (increasing)
        {
            row++;
        }
        else
        {
            row--;
        }

        if (row == 0 || row == rails - 1)
        {
            increasing = !increasing;
        }
    }

    char *output = malloc(row_len + 1);
    memset(output, '\0', row_len + 1);
    size_t i = 0;
    for (size_t row = 0; row < rails; row++)
    {
        for (size_t col = 0; col < row_len; col++)
        {
            char ch = intermediate[(row * row_len) + col];
            if (ch != '\0')
            {
                output[i++] = ch;
            }
        }
    }

    free(intermediate);

    return output;
}

char *decode(char *ciphertext, size_t rails)
{
    size_t row_len = strlen(ciphertext);
    char *intermediate = malloc((row_len * rails) + 1);
    memset(intermediate, '\0', (row_len * rails) + 1);

    bool increasing = true;
    size_t row = 0;
    for (size_t col = 0; col < row_len; col++)
    {
        intermediate[(row * row_len) + col] = '?';

        if (increasing)
        {
            row++;
        }
        else
        {
            row--;
        }

        if (row == 0 || row == rails - 1)
        {
            increasing = !increasing;
        }
    }

    size_t i = 0;
    for (size_t row = 0; row < rails; row++)
    {
        for (size_t col = 0; col < row_len; col++)
        {
            char ch = intermediate[(row * row_len) + col];
            if (ch == '?')
            {
                intermediate[(row * row_len) + col] = ciphertext[i];
                i++;
            }
        }
    }

    char *output = malloc(row_len + 1);
    memset(output, '\0', row_len + 1);
    increasing = true;
    row = 0;
    for (size_t col = 0; col < row_len; col++)
    {
        output[col] = intermediate[(row * row_len) + col];

        if (increasing)
        {
            row++;
        }
        else
        {
            row--;
        }

        if (row == 0 || row == rails - 1)
        {
            increasing = !increasing;
        }
    }

    free(intermediate);

    return output;
}
