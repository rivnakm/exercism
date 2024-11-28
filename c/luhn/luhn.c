#include "luhn.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

bool read_digits(const char *input, uint8_t **digits, size_t *length);

bool luhn(const char *num)
{
    uint8_t *digits = NULL;
    size_t num_digits = 0;
    if (!read_digits(num, &digits, &num_digits))
    {
        return false;
    }

    if (num_digits == 1 && digits[0] == 0)
    {
        free(digits);
        return false;
    }

    unsigned int sum = 0;
    for (size_t i = 0; i < num_digits; i++)
    {
        if ((num_digits - i) % 2 == 0)
        {
            uint16_t doubled = (uint16_t)digits[i] * 2;
            if (doubled > 9)
            {
                doubled -= 9;
            }
            digits[i] = (uint8_t)doubled;
        }

        sum += digits[i];
    }

    free(digits);

    return sum % 10 == 0;
}

bool read_digits(const char *input, uint8_t **digits, size_t *length)
{
    size_t input_length = strlen(input);
    size_t capacity = 16;
    *length = 0;
    *digits = malloc(capacity * sizeof(uint8_t));

    for (size_t i = 0; i < input_length; i++)
    {
        char ch = input[i];
        // spaces are allowed but ignored
        if (ch == ' ')
        {
            continue;
        }
        // non-digit characters are invalid
        if (ch < 48 || ch > 57)
        {
            free(*digits);
            return false;
        }

        (*digits)[(*length)++] = (uint8_t)(ch - 48);

        if (*length == capacity)
        {
            capacity *= 2;
            *digits = realloc(*digits, capacity * sizeof(uint8_t));
        }
    }

    *digits = realloc(*digits, (*length) * sizeof(uint8_t));

    return true;
}
