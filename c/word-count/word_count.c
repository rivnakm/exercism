#include "word_count.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

bool is_separator(char ch);

int add_word(char *word, size_t word_len, word_count_word_t *words, int *num_words);

size_t trim(char *word, size_t len, char trimchar);

// count_words - routine to classify the unique words and their frequency in a
// sentence inputs:
//    sentence =  a null-terminated string containing that is analyzed
//
// outputs:
//    words = allocated structure to record the words found and their frequency
//    uniqueWords - number of words in the words structure
//           returns a negative number if an error.
//           words will contain the results up to that point.
int count_words(const char *sentence, word_count_word_t *words)
{
    int num_words = 0;
    size_t len = strlen(sentence);

    char *buf = malloc(MAX_WORD_LENGTH + 1);
    size_t current_word_len = 0;

    for (size_t i = 0; i < len; i++)
    {
        char ch = sentence[i];
        if (is_separator(ch))
        {
            if (current_word_len > 0)
            {
                int result = add_word(buf, current_word_len, words, &num_words);
                if (result != 0)
                {
                    free(buf);
                    return result;
                }

                current_word_len = 0;
            }
            continue;
        }

        buf[current_word_len++] = tolower(ch);
    }
    if (current_word_len > 0)
    {
        int result = add_word(buf, current_word_len, words, &num_words);
        if (result != 0)
        {
            free(buf);
            return result;
        }
    }

    free(buf);

    return num_words;
}

bool is_separator(char ch)
{
    return (isspace(ch) || (ispunct(ch) && ch != '\''));
}

int add_word(char *word, size_t word_len, word_count_word_t *words, int *num_words)
{
    word_len = trim(word, word_len, '\'');
    word_len = trim(word, word_len, '"');

    for (int i = 0; i < *num_words; i++)
    {
        if (strncmp(word, words[i].text, word_len) == 0 && strlen(words[i].text) == word_len)
        {
            words[i].count++;

            return 0;
        }
    }

    if (*num_words == MAX_WORDS)
    {
        return EXCESSIVE_NUMBER_OF_WORDS;
    }

    strncpy(words[*num_words].text, word, word_len);
    words[*num_words].text[word_len] = '\0';
    words[*num_words].count = 1;
    (*num_words)++;

    return 0;
}

size_t trim(char *word, size_t len, char trimchar)
{
    int start = 0;
    for (int i = 0; i < (int)len; i++)
    {
        if (word[i] != trimchar)
        {
            start = i;
            break;
        }
    }

    int length = len;
    for (int i = len - 1; i > start; i--)
    {
        if (word[i] != trimchar)
        {
            length = 1 + i - start;
            break;
        }
    }

    for (int i = 0; i < length; i++)
    {
        word[i] = word[i + start];
    }

    return (size_t)length;
}
