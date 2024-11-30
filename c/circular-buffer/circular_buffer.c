#include "circular_buffer.h"

#include <errno.h>
#include <stdlib.h>

circular_buffer_t *new_circular_buffer(size_t capacity)
{
    circular_buffer_t *result = malloc(sizeof(circular_buffer_t));
    result->capacity = capacity;
    result->items = malloc(sizeof(buffer_value_t) * (capacity + 1));

    clear_buffer(result);

    return result;
}
void delete_buffer(circular_buffer_t *buffer)
{
    free(buffer->items);
    free(buffer);
}
void clear_buffer(circular_buffer_t *buffer)
{
    buffer->tail = 0;
    buffer->head = 0;
}

int16_t read(circular_buffer_t *buffer, buffer_value_t *value)
{
    if (buffer->head == buffer->tail)
    {
        errno = ENODATA;
        return EXIT_FAILURE;
    }
    *value = buffer->items[buffer->head++];
    if (buffer->head > buffer->capacity)
    {
        buffer->head = 0;
    }

    return 0;
}
int16_t write(circular_buffer_t *buffer, buffer_value_t value)
{
    if (buffer->tail - buffer->head == buffer->capacity)
    {
        errno = ENOBUFS;
        return EXIT_FAILURE;
    }

    return overwrite(buffer, value);
}

int16_t overwrite(circular_buffer_t *buffer, buffer_value_t value)
{
    buffer->items[buffer->tail++] = value;
    if (buffer->tail > buffer->capacity)
    {
        buffer->tail = 0;
    }
    if (buffer->head == buffer->tail)
    {
        // buffer is full, write over oldest element
        buffer->head++;
    }

    return 0;
}
