#include "bob.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef enum
{
    QUESTION,
    SHOUTING,
    SHOUTING_QUESTION,
    SILENCE,
    OTHER
} phrase_type_t;

phrase_type_t characterize(const char *greeting);

char *hey_bob(char *greeting)
{
    switch (characterize(greeting))
    {
    case QUESTION:
        return "Sure.";
    case SHOUTING:
        return "Whoa, chill out!";
    case SHOUTING_QUESTION:
        return "Calm down, I know what I'm doing!";
    case SILENCE:
        return "Fine. Be that way!";
    case OTHER:
    default:
        return "Whatever.";
    }
}

phrase_type_t characterize(const char *greeting)
{
    size_t len = strlen(greeting);
    char last = 0;
    bool has_upper = false;
    bool has_lower = false;
    bool is_silent = true;

    for (size_t i = 0; i < len; i++)
    {
        char ch = greeting[i];
        if (isspace(ch))
        {
            continue;
        }

        is_silent = false;
        if (isalpha(ch))
        {
            if (isupper(ch))
            {
                has_upper = true;
            }
            else
            {
                has_lower = true;
            }
        }
        last = ch;
    }

    bool shouting = has_upper && !has_lower;

    if (is_silent)
    {
        return SILENCE;
    }
    if (shouting)
    {
        if (last == '?')
        {
            return SHOUTING_QUESTION;
        }
        return SHOUTING;
    }
    if (last == '?')
    {
        return QUESTION;
    }

    return OTHER;
}
