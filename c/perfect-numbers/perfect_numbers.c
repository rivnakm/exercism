#include "perfect_numbers.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_factors(int num, int **factors);

int aliquot_sum(int num);

kind classify_number(int num)
{
    if (num <= 0)
    {
        return ERROR;
    }

    int sum = aliquot_sum(num);

    if (sum == num)
    {
        return PERFECT_NUMBER;
    }
    if (sum < num)
    {
        return DEFICIENT_NUMBER;
    }
    if (sum > num)
    {
        return ABUNDANT_NUMBER;
    }

    return ERROR; // Unreachable
}

int aliquot_sum(int num)
{
    int *factors = NULL;
    int num_factors = get_factors(num, &factors);

    int sum = 0;
    for (size_t i = 0; i < (size_t)num_factors; i++)
    {
        if (factors[i] == num)
        {
            continue;
        }

        sum += factors[i];
    }

    free(factors);

    return sum;
}

int get_factors(int num, int **factors)
{
    size_t capacity = 10;
    *factors = malloc(sizeof(int) * capacity);
    int count = 0;

    for (size_t i = 1; i <= (size_t)num / 2; i++)
    {
        if (num % i == 0)
        {

            (*factors)[count++] = i;

            if ((size_t)count == capacity)
            {
                capacity *= 2;
                *factors = realloc(*factors, sizeof(int) * capacity);
            }
        }
    }

    *factors = realloc(*factors, sizeof(int) * count);

    return count;
}
