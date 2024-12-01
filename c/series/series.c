#include "series.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

slices_t slices(char *input_text, unsigned int substring_length)
{
    size_t input_len = strlen(input_text);
    if (substring_length > input_len || substring_length == 0)
    {
        slices_t result = {.substring_count = 0, .substring = NULL};
        return result;
    }

    slices_t result = {.substring_count = input_len - substring_length + 1, .substring = NULL};
    result.substring = malloc(sizeof(char *) * result.substring_count);

    for (size_t i = 0; i <= input_len - substring_length; i++)
    {
        char *substr = malloc(substring_length + 1);
        strncpy(substr, input_text + i, substring_length);
        substr[substring_length] = '\0';
        result.substring[i] = substr;
    }

    return result;
}
