#include "atbash_cipher.h"

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char atbash(const char ch);

char *atbash_encode(const char *input)
{
    size_t length = 0;
    size_t capacity = 5;
    char *result = malloc(capacity);

    size_t input_len = strlen(input);

    size_t block_size = 0;
    for (size_t i = 0; i < input_len; i++)
    {
        char ch = input[i];
        if (isspace(ch) || ispunct(ch))
        {
            continue;
        }

        if (block_size == 5)
        {
            if (length == capacity)
            {
                capacity *= 2;
                result = realloc(result, capacity);
            }
            result[length++] = ' ';
            block_size = 0;
        }

        if (length == capacity)
        {
            capacity *= 2;
            result = realloc(result, capacity);
        }
        result[length++] = atbash(ch);
        block_size++;
    }

    result = realloc(result, length + 1);
    result[length] = '\0';

    return result;
}

char *atbash_decode(const char *input)
{
    size_t length = 0;
    size_t capacity = 5;
    char *result = malloc(capacity);

    size_t input_len = strlen(input);

    for (size_t i = 0; i < input_len; i++)
    {
        char ch = input[i];
        if (isspace(ch))
        {
            continue;
        }

        if (length == capacity)
        {
            capacity *= 2;
            result = realloc(result, capacity);
        }
        result[length++] = atbash(ch);
    }

    result = realloc(result, length + 1);
    result[length] = '\0';

    return result;
}

char atbash(const char ch)
{
    if (isalpha(ch))
    {
        char out = tolower(ch) - 'a';
        out = 25 - out;
        return out + 'a';
    }
    return ch;
}
