#include "nth_prime.h"

#include <stdbool.h>

bool is_prime(uint32_t n);

uint32_t nth(uint32_t n)
{
    if (n <= 0)
    {
        return 0;
    }
    uint32_t count = 0;
    uint32_t i = 2;
    while (true)
    {
        if (is_prime(i))
        {
            count++;
        }

        if (count == n)
        {
            break;
        }
        i++;
    }

    return i;
}

bool is_prime(uint32_t n)
{
    for (uint32_t i = 2; i < n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}
