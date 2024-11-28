#include "hamming.h"
#include <stddef.h>
#include <string.h>

int compute(const char *lhs, const char *rhs)
{
    if (strlen(lhs) != strlen(rhs))
    {
        return -1;
    }

    int count = 0;
    size_t len = strlen(lhs);
    for (size_t i = 0; i < len; i++)
    {
        if (lhs[i] != rhs[i])
        {
            count++;
        }
    }
    return count;
}
