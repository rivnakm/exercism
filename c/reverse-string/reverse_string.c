#include "reverse_string.h"

#include <stdlib.h>
#include <string.h>

char *reverse(const char *value)
{
    size_t len = strlen(value);
    char *out = malloc((sizeof(char) * (len + 1)));

    out[len] = '\0';
    for (size_t i = 0; i < len; i++)
    {
        out[i] = value[len - 1 - i];
    }

    return out;
}
