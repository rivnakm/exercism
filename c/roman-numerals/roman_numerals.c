#include "roman_numerals.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

size_t resolve(uint8_t factor, roman_numeral_t magnitude, roman_numeral_t **numerals);
char roman_to_char(roman_numeral_t roman);

void add_numerals(const roman_numeral_t *numerals, const size_t numerals_count, char **result, size_t *length,
                  size_t *capacity);

char *to_roman_numeral(unsigned int number)
{
    size_t length = 0;
    size_t capacity = 10;
    char *result = malloc(sizeof(char) * capacity);

    while (number > 0)
    {
        if (number >= 1000)
        {
            roman_numeral_t *numerals = NULL;
            size_t numerals_count = resolve(number / 1000, NUMERAL_M, &numerals);

            add_numerals(numerals, numerals_count, &result, &length, &capacity);

            free(numerals);

            number %= 1000;
        }
        else if (number >= 100)
        {
            roman_numeral_t *numerals = NULL;
            size_t numerals_count = resolve(number / 100, NUMERAL_C, &numerals);

            add_numerals(numerals, numerals_count, &result, &length, &capacity);

            free(numerals);

            number %= 100;
        }
        else if (number >= 10)
        {
            roman_numeral_t *numerals = NULL;
            size_t numerals_count = resolve(number / 10, NUMERAL_X, &numerals);

            add_numerals(numerals, numerals_count, &result, &length, &capacity);

            free(numerals);

            number %= 10;
        }
        else
        {
            roman_numeral_t *numerals = NULL;
            size_t numerals_count = resolve(number, NUMERAL_I, &numerals);

            add_numerals(numerals, numerals_count, &result, &length, &capacity);

            free(numerals);

            number = 0;
        }
    }

    result = realloc(result, sizeof(char) * (length + 1));
    result[length] = '\0';

    return result;
}

size_t resolve(uint8_t factor, roman_numeral_t magnitude, roman_numeral_t **numerals)
{
    size_t length = 0;
    if (factor < 4)
    {
        length = factor;
        *numerals = malloc(sizeof(roman_numeral_t) * length);
        for (size_t i = 0; i < length; i++)
        {
            (*numerals)[i] = magnitude;
        }
    }
    else if (factor == 4)
    {
        length = 2;
        *numerals = malloc(sizeof(roman_numeral_t) * length);
        (*numerals)[0] = magnitude;
        (*numerals)[1] = magnitude + 1;
    }
    else if (factor == 5)
    {
        length = 1;
        *numerals = malloc(sizeof(roman_numeral_t) * length);
        (*numerals)[0] = magnitude + 1;
    }
    else if (factor < 9)
    {
        length = factor - 4;
        *numerals = malloc(sizeof(roman_numeral_t) * length);
        (*numerals)[0] = magnitude + 1;
        for (size_t i = 1; i < length; i++)
        {
            (*numerals)[i] = magnitude;
        }
    }
    else if (factor == 9)
    {
        length = 2;
        *numerals = malloc(sizeof(roman_numeral_t) * length);
        (*numerals)[0] = magnitude;
        (*numerals)[1] = magnitude + 2;
    }

    return length;
}

char roman_to_char(roman_numeral_t roman)
{
    switch (roman)
    {
    case NUMERAL_I:
        return 'I';
    case NUMERAL_V:
        return 'V';
    case NUMERAL_X:
        return 'X';
    case NUMERAL_L:
        return 'L';
    case NUMERAL_C:
        return 'C';
    case NUMERAL_D:
        return 'D';
    case NUMERAL_M:
        return 'M';
    }
    return '\0';
}

void add_numerals(const roman_numeral_t *numerals, const size_t numerals_count, char **result, size_t *length,
                  size_t *capacity)
{
    for (size_t i = 0; i < numerals_count; i++)
    {
        char ch = roman_to_char(numerals[i]);
        if (*length == *capacity)
        {
            *capacity *= 2;
            *result = realloc(*result, sizeof(char) * *capacity);
        }

        (*result)[(*length)++] = ch;
    }
}
