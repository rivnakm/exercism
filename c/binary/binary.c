#include "binary.h"
#include <stddef.h>
#include <string.h>

int convert(const char *input)
{
    int out = 0;
    size_t len = strlen(input);
    for (size_t i = 0; i < len; i++)
    {
        switch (input[i])
        {
        case '0':
            break;
        case '1':
            out += 1 << (len - 1 - i);
            break;
        default:
            return INVALID;
        }
    }
    return out;
}
