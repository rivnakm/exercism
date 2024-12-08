#include "pig_latin.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isvowel(const char ch);
bool starts_with_consonants_then_segment(const char *word, const char *segment, const size_t min_consonants,
                                         size_t *prefix_len);

size_t ensure_output_capacity(char **output, const size_t current_len, const size_t current_capacity,
                              const size_t new_word_len);

char *translate(const char *phrase)
{
    size_t len = strlen(phrase);
    char *phrase_copy = malloc(len + 1);
    strcpy(phrase_copy, phrase);

    size_t output_len = 0;
    size_t output_capacity = (len * 2) + 1;
    char *output = malloc(output_capacity);
    memset(output, '\0', output_capacity);

    char *word = strtok(phrase_copy, " ");
    while (word != NULL)
    {
        size_t prefix_len = 0;
        // Rule 1
        // If a word begins with a vowel, or starts with "xr" or "yt", add an "ay" sound to the end of the word
        if (isvowel(word[0]) || strncmp(word, "xr", 2) == 0 || strncmp(word, "yt", 2) == 0)
        {
            size_t word_len = strlen(word);
            size_t suffix_len = 2;
            output_capacity = ensure_output_capacity(&output, output_len, output_capacity, word_len + suffix_len);

            strcat(output, word);
            strcat(output, "ay");

            output_len += word_len + suffix_len;
        }
        // Rule 3
        // If a word starts with zero or more consonants followed by "qu", first move those consonants (if any) and the
        // "qu" part to the end of the word, and then add an "ay" sound to the end of the word
        else if (starts_with_consonants_then_segment(word, "qu", 0, &prefix_len))
        {
            size_t word_len = strlen(word);
            size_t suffix_len = 2;
            output_capacity = ensure_output_capacity(&output, output_len, output_capacity, word_len + suffix_len);

            strcat(output, word + prefix_len);
            strncat(output, word, prefix_len);
            strcat(output, "ay");

            output_len += word_len + suffix_len;
        }
        // Rule 4
        // If a word starts with one or more consonants followed by "y", first move the consonants preceding the "y"to
        // the end of the word, and then add an "ay" sound to the end of the word
        else if (starts_with_consonants_then_segment(word, "y", 1, &prefix_len))
        {
            size_t word_len = strlen(word);
            size_t suffix_len = 2;
            output_capacity = ensure_output_capacity(&output, output_len, output_capacity, word_len + suffix_len);

            prefix_len -= 1;
            strcat(output, word + prefix_len);
            strncat(output, word, prefix_len);
            strcat(output, "ay");

            output_len += word_len + suffix_len;
        }
        // Rule 2
        // If a word begins with one or more consonants, first move those consonants to the end of the word and then add
        // an "ay" sound to the end of the word
        else
        {
            size_t word_len = strlen(word);
            size_t suffix_len = 2;
            output_capacity = ensure_output_capacity(&output, output_len, output_capacity, word_len + suffix_len);

            for (size_t i = 0; i < word_len; i++)
            {
                if (isvowel(word[i]))
                {
                    prefix_len = i;
                    break;
                }
            }

            strcat(output, word + prefix_len);
            strncat(output, word, prefix_len);
            strcat(output, "ay");

            output_len += word_len + suffix_len;
        }

        word = strtok(NULL, " ");
        if (word != NULL)
        {
            output[output_len++] = ' ';
        }
    }

    free(phrase_copy);

    output = realloc(output, output_len + 1);
    output[output_len] = '\0';

    return output;
}

bool isvowel(const char ch)
{
    if (!isalpha(ch))
    {
        return false;
    }
    char lower = tolower(ch);
    return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u';
}

bool starts_with_consonants_then_segment(const char *word, const char *segment, const size_t min_consonants,
                                         size_t *prefix_len)
{
    size_t len = strlen(word);
    size_t segment_len = strlen(segment);

    for (size_t i = 0; i < len; i++)
    {
        if (i >= min_consonants)
        {
            for (size_t j = 0; j < segment_len; j++)
            {
                if (i + j >= len)
                {
                    break;
                }
                char word_char = word[i + j];
                char segment_char = segment[j];

                if (word_char != segment_char)
                {
                    break;
                }

                if (j == segment_len - 1)
                {
                    *prefix_len = i + j + 1;
                    return true;
                }
            }
        }

        if (isvowel(word[i]))
        {
            break;
        }
    }
    *prefix_len = 0;
    return false;
}

size_t ensure_output_capacity(char **output, const size_t current_len, const size_t current_capacity,
                              const size_t new_word_len)
{

    if (current_capacity <= current_len + new_word_len)
    {
        size_t capacity = current_capacity;
        while (capacity <= current_len + new_word_len)
        {
            capacity *= 2;
        }

        *output = realloc(*output, capacity);
        return capacity;
    }
    else
    {
        return current_capacity;
    }
}
