#include "rotational_cipher.h"
#include <stdlib.h>
#include <string.h>

char rotate_single(const char ch, int shift_key);

char *rotate(const char *text, int shift_key)
{
    size_t len = strlen(text);
    char *out = malloc((sizeof(char) * len) + 1);
    for (size_t i = 0; i < len; i++)
    {
        out[i] = rotate_single(text[i], shift_key);
    }
    out[len] = '\0';

    return out;
}

char rotate_single(const char ch, int shift_key)
{
    if (ch >= 'a' && ch <= 'z')
    {
        char work = ch;
        work -= 'a';
        work += shift_key;
        work %= 26;
        work += 'a';
        return work;
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
        char work = ch;
        work -= 'A';
        work += shift_key;
        work %= 26;
        work += 'A';
        return work;
    }
    else
    {
        return ch;
    }
}
