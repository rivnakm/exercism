#include "anagram.h"

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define ABC_LEN (26)

bool check_word(const char *base, const char *test);

void find_anagrams(const char *subject, struct candidates *candidates)
{
    for (size_t i = 0; i < candidates->count; i++)
    {
        struct candidate *test = &candidates->candidate[i];
        if (check_word(subject, test->word))
        {
            test->is_anagram = IS_ANAGRAM;
        }
        else
        {
            test->is_anagram = NOT_ANAGRAM;
        }
    }
}

bool check_word(const char *base, const char *test)
{
    if (strlen(base) != strlen(test))
    {
        return false;
    }

    size_t len = strlen(base);

    bool is_same = true;
    for (size_t i = 0; i < len; i++)
    {
        if (tolower(base[i]) != tolower(test[i]))
        {
            is_same = false;
        }
    }
    if (is_same)
    {
        return false;
    }

    char base_letters[ABC_LEN] = {0};
    char test_letters[ABC_LEN] = {0};
    for (size_t i = 0; i < len; i++)
    {
        base_letters[tolower(base[i]) - 'a']++;
        test_letters[tolower(test[i]) - 'a']++;
    }

    for (size_t i = 0; i < ABC_LEN; i++)
    {
        if (base_letters[i] != test_letters[i])
        {
            return false;
        }
    }

    return true;
}
