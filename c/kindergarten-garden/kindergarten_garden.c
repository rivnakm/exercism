#include "kindergarten_garden.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

plant_t from_char(char ch);

plants_t plants(const char *diagram, const char *student)
{
    char initial = student[0];

    int offset = (initial - 'A') * 2;

    size_t second_row = (size_t)(strchr(diagram, '\n') - diagram) + 1;

    plants_t result = {.plants = {from_char(diagram[offset]), from_char(diagram[offset + 1]),
                                  from_char(diagram[second_row + offset]),
                                  from_char(diagram[second_row + offset + 1])}};
    return result;
}

plant_t from_char(char ch)
{
    switch (ch)
    {
    case 'G':
        return GRASS;
    case 'C':
        return CLOVER;
    case 'R':
        return RADISHES;
    case 'V':
    default:
        return VIOLETS;
    }
}
