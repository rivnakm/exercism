#include "sieve.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    uint32_t value;
    bool marked;
} number_t;

/// Calculate at most `max_primes` prime numbers in the interval [2,limit]
/// using the Sieve of Eratosthenes and store the prime numbers in `primes`
/// in increasing order.
/// The function returns the number of calculated primes.
uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes)
{
    size_t numbers_len = (limit + 1) - 2;
    number_t *numbers = malloc(sizeof(number_t) * numbers_len);

    for (size_t i = 0, val = 2; i < numbers_len; i++, val++)
    {
        number_t num = {.value = val, .marked = false};
        numbers[i] = num;
    }

    size_t idx = 0;
    for (size_t i = 0; i < numbers_len; i++)
    {
        if (idx >= max_primes)
        {
            break;
        }
        number_t *current = &(numbers[i]);
        if (!current->marked)
        {
            // Is prime
            primes[idx++] = current->value;
            current->marked = true;

            for (size_t j = i + 1; j < numbers_len; j++)
            {
                number_t *check = &(numbers[j]);
                if (!check->marked && check->value % current->value == 0)
                {
                    check->marked = true;
                }
            }
        }
    }

    free(numbers);

    return (uint32_t)idx;
}
