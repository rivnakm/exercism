#include "prime_factors.h"

#include <stdbool.h>
#include <stdio.h>

bool is_prime(uint64_t n);

size_t find_factors(uint64_t n, uint64_t factors[static MAXFACTORS]);

size_t find_factors(uint64_t n, uint64_t factors[static MAXFACTORS])
{
    size_t num_factors = 0;

    while (true)
    {
        for (size_t i = 2; i <= n; i++)
        {
            if (num_factors == MAXFACTORS)
            {
                break;
            }
            if (n % i == 0)
            {
                factors[num_factors++] = i;
                n /= i;
                break;
            }
        }
        if (num_factors == MAXFACTORS)
        {
            break;
        }

        if (n == 1)
        {
            break;
        }
        if (is_prime(n))
        {
            factors[num_factors++] = n;
            break;
        }
    }

    return num_factors;
}

bool is_prime(uint64_t n)
{
    for (size_t i = 2; i < n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}
