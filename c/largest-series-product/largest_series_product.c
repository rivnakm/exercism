#include "largest_series_product.h"
#include <ctype.h>
#include <stdint.h>
#include <string.h>

int64_t to_num(char c);

int64_t largest_series_product(char *digits, size_t span)
{
    if (span <= 0)
    {
        return -1;
    }

    int64_t max = -1;

    size_t len = strlen(digits);
    for (size_t i = 0; i < len - (span - 1); i++)
    {
        if (!isdigit(digits[i]))
        {
            return -1;
        }

        int64_t res = to_num(digits[i]);
        for (size_t j = 1; j < span; j++)
        {
            if (!isdigit(digits[i + j]))
            {
                return -1;
            }

            res *= to_num(digits[i + j]);
        }

        if (res > max)
        {
            max = res;
        }
    }

    return max;
}
int64_t to_num(char c)
{
    return c - '0';
}
