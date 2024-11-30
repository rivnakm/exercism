#include "spiral_matrix.h"

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct
{
    size_t top;
    size_t bottom;
    size_t left;
    size_t right;
} bounds_t;

typedef struct
{
    size_t x;
    size_t y;
    int value;
} cursor_t;

void draw_right(spiral_matrix_t *spiral, bounds_t *bounds, cursor_t *cursor);
void draw_down(spiral_matrix_t *spiral, bounds_t *bounds, cursor_t *cursor);
void draw_left(spiral_matrix_t *spiral, bounds_t *bounds, cursor_t *cursor);
void draw_up(spiral_matrix_t *spiral, bounds_t *bounds, cursor_t *cursor);

spiral_matrix_t *spiral_matrix_create(int size)
{

    spiral_matrix_t *spiral = malloc(sizeof(spiral_matrix_t));
    spiral->size = size;
    spiral->matrix = NULL;

    if (size == 0)
    {
        return spiral;
    }

    spiral->matrix = malloc(sizeof(int *) * size);
    for (size_t i = 0; i < (size_t)size; i++)
    {
        spiral->matrix[i] = malloc(sizeof(int) * size);
    }

    bounds_t bounds = {.top = 0, .bottom = size - 1, .left = 0, .right = size - 1};
    cursor_t cursor = {.x = 0, .y = 0, .value = 1};

    int end = pow(size, 2);
    while (true)
    {
        if (cursor.value <= end)
        {
            draw_right(spiral, &bounds, &cursor);
        }
        else
        {
            break;
        }
        if (cursor.value <= end)
        {
            draw_down(spiral, &bounds, &cursor);
        }
        else
        {
            break;
        }
        if (cursor.value <= end)
        {
            draw_left(spiral, &bounds, &cursor);
        }
        else
        {
            break;
        }
        if (cursor.value <= end)
        {
            draw_up(spiral, &bounds, &cursor);
        }
        else
        {
            break;
        }
    }

    return spiral;
}

void spiral_matrix_destroy(spiral_matrix_t *spiral)
{
    for (size_t i = 0; i < (size_t)spiral->size; i++)
    {
        free(spiral->matrix[i]);
    }
    free(spiral->matrix);
    free(spiral);
}

void draw_right(spiral_matrix_t *spiral, bounds_t *bounds, cursor_t *cursor)
{
    while (cursor->x <= bounds->right)
    {
        spiral->matrix[cursor->y][cursor->x] = cursor->value++;
        if (cursor->x == bounds->right)
        {
            cursor->y++;
            break;
        }
        else
        {
            cursor->x++;
        }
    }
    bounds->top++;
}

void draw_down(spiral_matrix_t *spiral, bounds_t *bounds, cursor_t *cursor)
{
    while (cursor->y <= bounds->bottom)
    {
        spiral->matrix[cursor->y][cursor->x] = cursor->value++;
        if (cursor->y == bounds->bottom)
        {
            cursor->x--;
            break;
        }
        else
        {
            cursor->y++;
        }
    }
    bounds->right--;
}

void draw_left(spiral_matrix_t *spiral, bounds_t *bounds, cursor_t *cursor)
{
    while (cursor->x >= bounds->left)
    {
        spiral->matrix[cursor->y][cursor->x] = cursor->value++;
        if (cursor->x == bounds->left)
        {
            cursor->y--;
            break;
        }
        else
        {
            cursor->x--;
        }
    }
    bounds->bottom--;
}

void draw_up(spiral_matrix_t *spiral, bounds_t *bounds, cursor_t *cursor)
{
    while (cursor->y >= bounds->top)
    {
        spiral->matrix[cursor->y][cursor->x] = cursor->value++;
        if (cursor->y == bounds->top)
        {
            cursor->x++;
            break;
        }
        else
        {
            cursor->y--;
        }
    }
    bounds->left++;
}
