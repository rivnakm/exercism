#include "armstrong_numbers.h"

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t get_digits(int number, uint8_t **digits);

bool is_armstrong_number(int candidate)
{
    if (candidate == 0)
    {
        return true;
    }

    uint8_t *digits = NULL;
    size_t num_digits = get_digits(candidate, &digits);

    int sum = 0;
    for (size_t i = 0; i < num_digits; i++)
    {
        sum += pow(digits[i], num_digits);
    }

    free(digits);

    return sum == candidate;
}

size_t get_digits(int number, uint8_t **digits)
{
    size_t num_digits = log10f(number) + 1;
    *digits = malloc(sizeof(uint8_t) * num_digits);

    for (size_t i = num_digits; i > 0; i--)
    {
        (*digits)[i - 1] = (uint8_t)(number % 10);
        number /= 10;
    }

    return num_digits;
}
