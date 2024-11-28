#include "beer_song.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOTTLES (99)

/// asprintf is a GNU extension, so it's not available with std=c99
/// so we have to implement it ourselves
int asprintf(char **buffer, const char *fmt, ...);

int verse(char **buffer, uint8_t n);
const char *instruction(uint8_t n);
int bottles(char **buffer, uint8_t n);

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    size_t song_line = 0;
    for (int i = start_bottles; i > start_bottles - take_down; i--)
    {
        char *verse_buffer = NULL;
        int verse_size = verse(&verse_buffer, i);

        size_t line_idx = 0;
        for (int j = 0; j < verse_size; j++)
        {
            if (verse_buffer[j] == '\n')
            {
                song[song_line][line_idx] = '\0';
                song_line++;
                line_idx = 0;
                continue;
            }
            song[song_line][line_idx++] = verse_buffer[j];
        }

        free(verse_buffer);

        if (i != start_bottles - take_down + 1)
        {
            song[song_line][line_idx] = '\0';
            song_line++;
        }
    }
}

int verse(char **buffer, uint8_t n)
{
    char *bottles_str_start;
    bottles(&bottles_str_start, n);
    char *bottles_str_end;
    bottles(&bottles_str_end, n == 0 ? MAX_BOTTLES : n - 1);
    const char *instruction_str = instruction(n);

    int ret = asprintf(buffer,
                       "%s of beer on the wall, %s of beer.\n"
                       "%s, %s of beer on the wall.\n",
                       bottles_str_start, bottles_str_start, instruction_str, bottles_str_end);

    (*buffer)[0] = toupper((*buffer)[0]);

    free(bottles_str_start);
    free(bottles_str_end);

    return ret;
}

const char *instruction(uint8_t n)
{
    if (n == 0)
    {
        return "Go to the store and buy some more";
    }
    else if (n == 1)
    {
        return "Take it down and pass it around";
    }
    else
    {
        return "Take one down and pass it around";
    }
}

int bottles(char **buffer, uint8_t n)
{
    if (n == 0)
    {
        return asprintf(buffer, "no more bottles");
    }
    else if (n == 1)
    {
        return asprintf(buffer, "1 bottle");
    }
    else
    {
        return asprintf(buffer, "%d bottles", n);
    }
}

int asprintf(char **buffer, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    if (len < 0)
    {
        return -1;
    }

    *buffer = malloc(len + 1);
    if (*buffer == NULL)
    {
        return -1;
    }

    va_start(args, fmt);
    vsnprintf(*buffer, len + 1, fmt, args);
    va_end(args);

    return len;
}
