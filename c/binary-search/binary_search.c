#include "binary_search.h"
#include <stdio.h>

const int *binary_search(int value, const int *arr, size_t length)
{
    if (length == 0)
    {
        return NULL;
    }
    if (length == 1)
    {
        if (arr[0] == value)
        {
            return &arr[0];
        }
        else
        {
            return NULL;
        }
    }

    size_t midpoint = length / 2;
    int mid_value = arr[midpoint];

    if (mid_value == value)
    {
        return &arr[midpoint];
    }
    else if (value > mid_value)
    {
        return binary_search(value, arr + midpoint, length - midpoint);
    }
    else
    {
        return binary_search(value, arr, midpoint);
    }
}
