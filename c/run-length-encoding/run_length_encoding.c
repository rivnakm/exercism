#include "run_length_encoding.h"

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    size_t length;
    size_t capacity;
    char *data;
} str_builder_t;

str_builder_t *str_builder_new(void);
void str_builder_cat(str_builder_t *builder, const char *str);
void str_builder_cat_n(str_builder_t *builder, const char *str, size_t n);
void str_builder_cat_ch(str_builder_t *builder, const char ch);
size_t str_builder_length(const str_builder_t *builder);
char *str_builder_build(str_builder_t *builder);
void str_builder_free(str_builder_t *builder);

char *num_to_str(const size_t num);

void encode_chunk(str_builder_t *builder, const size_t count, const char ch);

char *encode(const char *text)
{
    size_t text_len = strlen(text);

    str_builder_t *builder = str_builder_new();

    char prev = '\0';
    size_t count = 0;
    for (size_t i = 0; i < text_len; i++)
    {
        char ch = text[i];
        if (ch != prev)
        {
            encode_chunk(builder, count, prev);

            prev = ch;
            count = 0;
        }

        count++;
    }
    encode_chunk(builder, count, prev);

    char *result = str_builder_build(builder);

    str_builder_free(builder);
    builder = NULL;

    return result;
}

char *decode(const char *data)
{
    size_t data_len = strlen(data);

    str_builder_t *builder = str_builder_new();

    bool is_number = false;
    size_t number = 0;
    for (size_t i = 0; i < data_len; i++)
    {
        char ch = data[i];
        if (isdigit(ch))
        {
            is_number = true;
            number = (number * 10) + (ch - '0');
        }
        else if (is_number)
        {
            for (size_t i = 0; i < number; i++)
            {
                str_builder_cat_ch(builder, ch);
            }
            is_number = false;
            number = 0;
        }
        else
        {
            str_builder_cat_ch(builder, ch);
        }
    }

    char *result = str_builder_build(builder);

    str_builder_free(builder);
    builder = NULL;

    return result;
}

void encode_chunk(str_builder_t *builder, const size_t count, const char ch)
{
    if (count == 1)
    {
        str_builder_cat_ch(builder, ch);
    }
    else if (count > 1)
    {
        char *num_str = num_to_str(count);

        str_builder_cat(builder, num_str);
        str_builder_cat_ch(builder, ch);

        free(num_str);
    }
}

char *num_to_str(const size_t num)
{
    size_t num_digits = log10(num) + 1;
    char *dest = malloc(sizeof(char) * (num_digits + 1));
    snprintf(dest, num_digits + 1, "%zu", num);
    dest[num_digits] = '\0';

    return dest;
}

// String builder
str_builder_t *str_builder_new(void)
{
    const size_t default_capacity = 10;
    str_builder_t *result = malloc(sizeof(str_builder_t));

    result->length = 0;
    result->capacity = default_capacity;
    result->data = malloc(default_capacity);

    return result;
}

void str_builder_cat(str_builder_t *builder, const char *str)
{
    str_builder_cat_n(builder, str, strlen(str));
}

void str_builder_cat_n(str_builder_t *builder, const char *str, size_t n)
{
    if (builder->length + n >= builder->capacity)
    {
        while (builder->length + n >= builder->capacity)
        {
            builder->capacity *= 2;
        }
        builder->data = realloc(builder->data, builder->capacity);
    }

    memcpy(builder->data + builder->length, str, n);
    builder->length += n;
}

void str_builder_cat_ch(str_builder_t *builder, const char ch)
{
    if (builder->length == builder->capacity)
    {
        builder->capacity *= 2;
        builder->data = realloc(builder->data, builder->capacity);
    }

    builder->data[builder->length++] = ch;
}

size_t str_builder_length(const str_builder_t *builder)
{
    return builder->length;
}

char *str_builder_build(str_builder_t *builder)
{
    char *output = malloc(builder->length + 1);
    memcpy(output, builder->data, builder->length);
    output[builder->length] = '\0';

    return output;
}

void str_builder_free(str_builder_t *builder)
{
    free(builder->data);
    free(builder);
}
