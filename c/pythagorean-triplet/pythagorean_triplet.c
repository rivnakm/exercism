#include "pythagorean_triplet.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

triplets_t *triplets_with_sum(uint16_t sum)
{
    triplets_t *result = malloc(sizeof(triplets_t));
    result->count = 0;
    result->triplets = malloc(sizeof(triplet_t) * (size_t)sum);

    for (uint16_t a = 1; 3 * (a + 1) <= sum; a++)
    {
        for (uint16_t b = a + 1; (2 * b) + 1 <= sum; b++)
        {
            uint16_t c = sum - a - b;
            if (((uint32_t)a * a) + ((uint32_t)b * b) == ((uint32_t)c * c))
            {
                result->triplets[result->count++] = (triplet_t){.a = a, .b = b, .c = c};
            }
        }
    }

    result->triplets = realloc(result->triplets, sizeof(triplet_t) * result->count);

    return result;
}

void free_triplets(triplets_t *triplets)
{
    free(triplets->triplets);
    free(triplets);
}
