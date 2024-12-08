#include "crypto_square.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void find_square(const size_t msg_len, size_t *rows, size_t *cols);

char *ciphertext(const char *input)
{
    size_t input_len = strlen(input);

    char *buf = malloc(input_len + 1);
    memset(buf, '\0', input_len + 1);

    size_t buf_i = 0;
    for (size_t i = 0; i < input_len; i++)
    {
        char ch = input[i];
        if (isspace(ch) || ispunct(ch))
        {
            continue;
        }

        buf[buf_i++] = tolower(ch);
    }
    size_t buf_len = buf_i;

    size_t rows;
    size_t cols;
    find_square(buf_i, &rows, &cols);

    // length of stripped input + spaces at the end of each line (in the square), but only if there's more than one row
    size_t output_len = rows > 1 ? rows * (cols + 1) : buf_i;
    char *output = malloc(output_len + 1);
    memset(output, '\0', output_len + 1);

    size_t output_i = 0;
    for (size_t col = 0; col < cols; col++)
    {
        for (size_t row = 0; row < rows; row++)
        {
            buf_i = (row * cols) + col;
            if (buf_i < buf_len)
            {
                output[output_i++] = buf[(row * cols) + col];
            }
            else
            {
                output[output_i++] = ' ';
            }
        }
        if (rows > 1 && col != cols - 1)
        {
            output[output_i++] = ' ';
        }
    }

    free(buf);

    return output;
}

void find_square(const size_t msg_len, size_t *rows, size_t *cols)
{
    *rows = 1;
    *cols = msg_len;
    while (*cols > *rows)
    {
        (*rows)++;
        while ((*rows) * ((*cols) - 1) >= msg_len)
        {
            (*cols)--;
        }

        if ((*cols) >= (*rows) && (*cols) - (*rows) <= 1)
        {
            break;
        }
    }
}
