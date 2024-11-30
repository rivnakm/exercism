#include "pascals_triangle.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t **create_triangle(size_t rows)
{
    // imo 0 rows should just return a null pointer, but the test cases say otherwise
    if (rows == 0)
    {
        uint8_t **triangle = malloc(sizeof(uint8_t *));
        triangle[0] = malloc(sizeof(uint8_t));

        triangle[0][0] = 0;

        return triangle;
    }

    uint8_t **triangle = malloc(sizeof(uint8_t *) * rows);

    for (size_t i = 0; i < rows; i++)
    {
        // tests expect a square matrix
        triangle[i] = malloc(sizeof(uint8_t) * rows);
        memset(triangle[i], 0, sizeof(uint8_t) * rows);

        size_t row_start = 0;
        size_t row_end = i;

        for (size_t j = row_start; j <= row_end; j++)
        {
            if (j == row_start || j == row_end)
            {
                triangle[i][j] = 1;
            }
            else
            {
                triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }
        }
    }

    return triangle;
}

void free_triangle(uint8_t **triangle, size_t rows)
{
    for (size_t i = 0; i < rows; i++)
    {
        free(triangle[i]);
    }
    free(triangle);
}
