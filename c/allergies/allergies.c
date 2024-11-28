#include "allergies.h"
#include <stddef.h>

bool is_allergic_to(allergen_t allergen, int score)
{
    int value;
    switch (allergen)
    {
    case ALLERGEN_EGGS:
        value = 1;
        break;
    case ALLERGEN_PEANUTS:
        value = 2;
        break;
    case ALLERGEN_SHELLFISH:
        value = 4;
        break;
    case ALLERGEN_STRAWBERRIES:
        value = 8;
        break;
    case ALLERGEN_TOMATOES:
        value = 16;
        break;
    case ALLERGEN_CHOCOLATE:
        value = 32;
        break;
    case ALLERGEN_POLLEN:
        value = 64;
        break;
    case ALLERGEN_CATS:
        value = 128;
        break;
    case ALLERGEN_COUNT:
        value = 0;
        break;
    }

    return (value & score) > 0;
}

allergen_list_t get_allergens(int score)
{
    allergen_list_t list = {.count = 0, .allergens = {false}};
    for (size_t i = 0; i < ALLERGEN_COUNT; i++)
    {
        if (is_allergic_to((allergen_t)i, score))
        {
            list.count++;
            list.allergens[i] = true;
        }
        else
        {
            list.allergens[i] = false;
        }
    }

    return list;
}
