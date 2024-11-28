#include "sum_of_multiples.h"

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned int *values;
    size_t length;
} multiples_list_t;

multiples_list_t multiples(const unsigned int factor, const unsigned int limit);

size_t combine_uniq(const multiples_list_t *multiples_lists, const size_t num_lists, unsigned int **result);

void merge(const unsigned int *buffer, const size_t low, const size_t pivot, const size_t high, unsigned int *result);

void sort_internal(const unsigned int *list, const size_t low, const size_t high, unsigned int *result,
                   unsigned int *buffer);

void sort(unsigned int *list, const size_t len);

unsigned int sum(const unsigned int *factors, const size_t number_of_factors, const unsigned int limit)
{
    multiples_list_t *multiples_lists = malloc(sizeof(multiples_list_t) * number_of_factors);

    for (size_t i = 0; i < number_of_factors; i++)
    {
        multiples_lists[i] = multiples(factors[i], limit);
    }

    unsigned int *unique = NULL;
    size_t num_unique = combine_uniq(multiples_lists, number_of_factors, &unique);

    for (size_t i = 0; i < number_of_factors; i++)
    {
        free(multiples_lists[i].values);
    }
    free(multiples_lists);

    unsigned int sum = 0;
    for (size_t i = 0; i < num_unique; i++)
    {
        sum += unique[i];
    }

    free(unique);

    return sum;
}

multiples_list_t multiples(const unsigned int factor, const unsigned int limit)
{
    if (factor == 0)
    {

        unsigned int *result = malloc(sizeof(unsigned int));
        result[0] = 0;

        multiples_list_t ret = {.values = result, .length = 1};
        return ret;
    }

    size_t length = 0;
    size_t capacity = 8;
    unsigned int *result = malloc(sizeof(unsigned int) * capacity);

    for (size_t i = 1;; i++)
    {
        unsigned int val = factor * (unsigned int)i;
        if (val >= limit)
        {
            break;
        }
        else
        {
            result[length++] = val;

            if (length == capacity)
            {
                capacity *= 2;
                result = realloc(result, sizeof(unsigned int) * capacity);
            }
        }
    }

    result = realloc(result, sizeof(unsigned int) * length);

    multiples_list_t ret = {.values = result, .length = length};
    return ret;
}

size_t combine_uniq(const multiples_list_t *multiples_lists, const size_t num_lists, unsigned int **result)
{
    size_t length = 0;
    size_t capacity = 8;
    *result = malloc(sizeof(unsigned int) * capacity);

    size_t merged_len = 0;
    for (size_t list_idx = 0; list_idx < num_lists; list_idx++)
    {
        merged_len += multiples_lists[list_idx].length;
    }
    unsigned int *merged = malloc(sizeof(unsigned int) * merged_len);

    size_t pos = 0;
    for (size_t list_idx = 0; list_idx < num_lists; list_idx++)
    {
        memcpy(merged + pos, multiples_lists[list_idx].values, sizeof(unsigned int) * multiples_lists[list_idx].length);
        pos += multiples_lists[list_idx].length;
    }

    sort(merged, merged_len);

    for (size_t i = 0; i < merged_len; i++)
    {
        if (i == 0 || merged[i] != merged[i - 1])
        {
            if (length == capacity)
            {
                capacity *= 2;
                *result = realloc(*result, sizeof(unsigned int) * capacity);
            }
            (*result)[length++] = merged[i];
        }
    }

    *result = realloc(*result, sizeof(unsigned int) * length);

    return length;
}

void merge(const unsigned int *buffer, const size_t low, const size_t pivot, const size_t high, unsigned int *result)
{
    size_t left_idx = low;
    size_t right_idx = pivot;
    size_t result_idx = 0;

    while (left_idx < pivot && right_idx < high)
    {
        if (buffer[left_idx] < buffer[right_idx])
        {
            result[result_idx++] = buffer[left_idx++];
        }
        else
        {
            result[result_idx++] = buffer[right_idx++];
        }
    }

    while (left_idx < pivot)
    {
        result[result_idx++] = buffer[left_idx++];
    }

    while (right_idx < high)
    {
        result[result_idx++] = buffer[right_idx++];
    }
}

void sort_internal(const unsigned int *list, const size_t low, const size_t high, unsigned int *result,
                   unsigned int *buffer)
{
    size_t len = high - low;
    if (len == 0)
    {
        return;
    }
    else if (len == 1)
    {
        result[low] = list[low];
        return;
    }

    size_t pivot = low + (len / 2);

    sort_internal(list, low, pivot, buffer, result);
    sort_internal(list, pivot, high, buffer, result);

    merge(buffer, low, pivot, high, result + low);
}

void sort(unsigned int *list, const size_t len)
{
    if (len <= 1)
    {
        return;
    }

    unsigned int *copy = malloc(sizeof(unsigned int) * len * 2);
    unsigned int *buffer = copy + len;

    memcpy(copy, list, sizeof(unsigned int) * len);
    sort_internal(copy, 0, len, list, buffer);

    free(copy);
}
