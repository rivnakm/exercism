#include "saddle_points.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool check_point(size_t row, size_t col, size_t rows, size_t columns, uint8_t matrix[rows][columns]);

saddle_points_t *saddle_points(size_t rows, size_t columns, uint8_t matrix[rows][columns])
{
    saddle_points_t *points = malloc(sizeof(saddle_points_t));
    points->count = 0;
    points->points = malloc(sizeof(saddle_point_t) * rows * columns);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (check_point(i, j, rows, columns, matrix))
            {
                saddle_point_t *point = &points->points[points->count++];
                point->row = i + 1;
                point->column = j + 1;
            }
        }
    }

    points->points = realloc(points->points, sizeof(saddle_point_t) * points->count);

    return points;
}

void free_saddle_points(saddle_points_t *points)
{
    free(points->points);
    free(points);
}

bool check_point(size_t row, size_t col, size_t rows, size_t columns, uint8_t matrix[rows][columns])
{
    uint8_t height = matrix[row][col];
    // Taller than every tree East/West
    for (size_t i = 0; i < columns; i++)
    {
        if (i == col)
        {
            continue;
        }
        if (matrix[row][i] > height)
        {
            return false;
        }
    }

    // Shorter than every tree North/South
    for (size_t i = 0; i < rows; i++)
    {
        if (i == row)
        {
            continue;
        }
        if (matrix[i][col] < height)
        {
            return false;
        }
    }

    return true;
}
