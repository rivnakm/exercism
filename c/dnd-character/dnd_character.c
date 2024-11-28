#include "dnd_character.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_within(int min, int max);

int ability(void)
{
    int nums[4];
    int min = INT_MAX;
    size_t min_idx = 0;

    for (size_t i = 0; i < 4; i++)
    {
        int num = rand_within(1, 6);
        nums[i] = num;
        if (num < min)
        {
            min = num;
            min_idx = i;
        }
    }

    int result = 0;
    for (size_t i = 0; i < 4; i++)
    {
        if (i == min_idx)
        {
            continue;
        }
        result += nums[i];
    }

    return result;
}

int modifier(int score)
{
    return floorf((float)(score - 10) / 2.0F);
}

dnd_character_t make_dnd_character(void)
{
    srand(time(NULL));

    dnd_character_t character = {.strength = ability(),
                                 .dexterity = ability(),
                                 .constitution = ability(),
                                 .intelligence = ability(),
                                 .wisdom = ability(),
                                 .charisma = ability()};
    character.hitpoints = 10 + modifier(character.constitution);

    return character;
}

int rand_within(int min, int max)
{
    int val = (rand() % (max - min + 1)) + min;
    return val;
}
