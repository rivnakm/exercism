#include "all_your_base.h"

size_t rebase(int8_t *digits, int16_t input_base, int16_t output_base, size_t input_length)
{
    if (input_base <= 1 || output_base <= 1 || input_length == 0)
    {
        return 0;
    }

    size_t value = 0;

    for (size_t i = 0; i < input_length; i++)
    {
        if (digits[i] < 0 || digits[i] >= input_base)
        {
            return 0;
        }
        value = value * input_base + digits[i];
    }

    if (value == 0)
    {
        digits[0] = 0;
        return 1;
    }

    size_t output_length = 0;
    while (value > 0)
    {
        digits[output_length++] = value % output_base;
        value /= output_base;
    }

    // Reverse the digits
    for (size_t i = 0; i < output_length / 2; i++)
    {
        int8_t temp = digits[i];
        digits[i] = digits[output_length - i - 1];
        digits[output_length - i - 1] = temp;
    }

    return output_length;
}
