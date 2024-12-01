#include "etl.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool is_sorted(const new_map *map, const size_t length);
void sort_map(new_map *map, const size_t length);

int convert(const legacy_map *input, const size_t input_len, new_map **output)
{
    size_t length = 0;
    size_t capacity = 16;
    *output = malloc(sizeof(new_map) * capacity);

    for (size_t i = 0; i < input_len; i++)
    {
        const legacy_map *old = &input[i];
        size_t keys_count = strlen(old->keys);

        for (size_t j = 0; j < keys_count; j++)
        {
            if (length == capacity)
            {
                capacity *= 2;
                *output = realloc(*output, sizeof(new_map) * capacity);
            }

            new_map *new = &(*output)[length++];
            new->value = old->value;
            new->key = tolower(old->keys[j]);
        }
    }

    *output = realloc(*output, sizeof(new_map) * length);

    sort_map(*output, length);

    return (int)length;
}

bool is_sorted(const new_map *map, const size_t length)
{
    for (size_t i = 1; i < length; i++)
    {
        if (map[i - 1].key > map[i].key)
        {
            return false;
        }
    }
    return true;
}

void sort_map(new_map *map, const size_t length)
{
    while (!is_sorted(map, length))
    {
        for (size_t i = 1; i < length; i++)
        {
            if (map[i - 1].key > map[i].key)
            {
                new_map temp = map[i - 1];
                map[i - 1] = map[i];
                map[i] = temp;
            }
        }
    }
}
