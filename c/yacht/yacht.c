#include "yacht.h"

#include <stddef.h>
#include <stdio.h>

#define DICE_COUNT (5)
#define DICE_SIDES (6)

int full_house(dice_t dice);
int four_of_a_kind(dice_t dice);
int little_straight(dice_t dice);
int big_straight(dice_t dice);

int score(dice_t dice, category_t category)
{
    int score = 0;
    switch (category)
    {
    case ONES:
        for (size_t i = 0; i < DICE_COUNT; i++)
        {
            if (dice.faces[i] == 1)
            {
                score += 1;
            }
        }
        break;
    case TWOS:
        for (size_t i = 0; i < DICE_COUNT; i++)
        {
            if (dice.faces[i] == 2)
            {
                score += 2;
            }
        }
        break;
    case THREES:
        for (size_t i = 0; i < DICE_COUNT; i++)
        {
            if (dice.faces[i] == 3)
            {
                score += 3;
            }
        }
        break;
    case FOURS:
        for (size_t i = 0; i < DICE_COUNT; i++)
        {
            if (dice.faces[i] == 4)
            {
                score += 4;
            }
        }
        break;
    case FIVES:
        for (size_t i = 0; i < DICE_COUNT; i++)
        {
            if (dice.faces[i] == 5)
            {
                score += 5;
            }
        }
        break;
    case SIXES:
        for (size_t i = 0; i < DICE_COUNT; i++)
        {
            if (dice.faces[i] == 6)
            {
                score += 6;
            }
        }
        break;
    case FULL_HOUSE:
        score = full_house(dice);
        break;
    case FOUR_OF_A_KIND:
        score = four_of_a_kind(dice);
        break;
    case LITTLE_STRAIGHT:
        score = little_straight(dice);
        break;
    case BIG_STRAIGHT:
        score = big_straight(dice);
        break;
    case CHOICE:
        for (size_t i = 0; i < DICE_COUNT; i++)
        {
            score += dice.faces[i];
        }
        break;
    case YACHT:
        score = 50;
        for (size_t i = 1; i < DICE_COUNT; i++)
        {
            if (dice.faces[i] != dice.faces[i - 1])
            {
                score = 0;
                break;
            }
        }
        break;
    }

    return score;
}

int full_house(dice_t dice)
{
    int counts[DICE_SIDES] = {0};

    for (size_t i = 0; i < DICE_COUNT; i++)
    {
        // face values start at 1
        counts[dice.faces[i] - 1]++;
    }

    int two_of_a_kind = -1;
    int three_of_a_kind = -1;

    for (size_t i = 0; i < DICE_SIDES; i++)
    {
        if (counts[i] == 2)
        {
            two_of_a_kind = i;
        }
        else if (counts[i] == 3)
        {
            three_of_a_kind = i;
        }
    }

    if (two_of_a_kind == -1 || three_of_a_kind == -1)
    {
        return 0;
    }

    int score = 0;

    for (size_t i = 0; i < DICE_COUNT; i++)
    {
        score += dice.faces[i];
    }

    return score;
}

int four_of_a_kind(dice_t dice)
{
    int counts[DICE_SIDES] = {0};

    for (size_t i = 0; i < DICE_COUNT; i++)
    {
        counts[dice.faces[i] - 1]++;
    }

    int four_of_a_kind = -1;

    for (size_t i = 0; i < DICE_SIDES; i++)
    {
        if (counts[i] >= 4)
        {
            four_of_a_kind = i + 1;
        }
    }

    if (four_of_a_kind == -1)
    {
        return 0;
    }

    return four_of_a_kind * 4;
}

int little_straight(dice_t dice)
{
    int counts[DICE_SIDES] = {0};

    for (size_t i = 0; i < DICE_COUNT; i++)
    {
        counts[dice.faces[i] - 1]++;
    }

    for (size_t i = 0; i < 5; i++)
    {
        if (counts[i] != 1)
        {
            return 0;
        }
    }
    return 30;
}

int big_straight(dice_t dice)
{
    int counts[DICE_SIDES] = {0};

    for (size_t i = 0; i < DICE_COUNT; i++)
    {
        counts[dice.faces[i] - 1]++;
    }

    for (size_t i = 1; i < 6; i++)
    {
        if (counts[i] != 1)
        {
            return 0;
        }
    }
    return 30;
}
