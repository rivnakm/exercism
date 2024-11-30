#include "phone_number.h"

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define OUTPUT_NUM_DIGITS (10)
#define MAX_DIGITS (11)

#define AREA_CODE_OFFSET (0)
#define EXCHANGE_CODE_OFFSET (3)

char *invalid(void);

char *phone_number_clean(const char *input)
{
    size_t num_digits = 0;
    char digits[MAX_DIGITS];
    size_t input_len = strlen(input);

    // Read digits
    for (size_t i = 0; i < input_len; i++)
    {
        if (isdigit(input[i]))
        {
            if (num_digits == MAX_DIGITS)
            {
                return invalid();
            }

            digits[num_digits++] = input[i];
        }
        else
        {
            switch (input[i])
            {
            // Valid punctuation
            case '+':
            case '(':
            case ')':
            case '-':
            case '.':
            case ' ':
                break;
            default:
                return invalid();
            }
        }
    }

    // Too short
    if (num_digits < OUTPUT_NUM_DIGITS)
    {
        return invalid();
    }

    // Check for NANP country code, and discard if it's correct
    if (num_digits == MAX_DIGITS)
    {
        // Correct NANP country code
        if (digits[0] == '1')
        {
            // Remove and shift digits forward (not needed in output)
            for (size_t i = 0; i < OUTPUT_NUM_DIGITS; i++)
            {
                digits[i] = digits[i + 1];
            }
            num_digits = OUTPUT_NUM_DIGITS;
        }
        else
        {
            return invalid();
        }
    }

    // Check valid area code
    if (digits[AREA_CODE_OFFSET] == '0' || digits[AREA_CODE_OFFSET] == '1')
    {
        return invalid();
    }

    // Check valid exchange code
    if (digits[EXCHANGE_CODE_OFFSET] == '0' || digits[EXCHANGE_CODE_OFFSET] == '1')
    {
        return invalid();
    }

    char *output = malloc(sizeof(char) * (OUTPUT_NUM_DIGITS + 1));
    strncpy(output, digits, OUTPUT_NUM_DIGITS);
    output[OUTPUT_NUM_DIGITS] = '\0';

    return output;
}

char *invalid(void)
{
    char *result = malloc(sizeof(char) * (OUTPUT_NUM_DIGITS + 1));
    for (size_t i = 0; i < OUTPUT_NUM_DIGITS; i++)
    {
        result[i] = '0';
    }
    result[OUTPUT_NUM_DIGITS] = '\0';

    return result;
}
