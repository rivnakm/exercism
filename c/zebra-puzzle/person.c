#include "person.h"
#include "parameters.h"
#include "sequence.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    FIELD_COLOR,
    FIELD_COUNTRY,
    FIELD_PET,
    FIELD_DRINK,
    FIELD_HOBBY,
} puzzle_field_t;

typedef union {
    color_t color;
    country_t country;
    pet_t pet;
    drink_t drink;
    hobby_t hobby;
} puzzle_field_value_t;

void set_sequence(const puzzle_field_t field, person_t persons[NUM_HOUSES], const unsigned int *seq);
puzzle_field_value_t get_field_value(const puzzle_field_t field, person_t person);
void set_field_value(const puzzle_field_t field, person_t *person, puzzle_field_value_t value);
void set_field_value_raw(const puzzle_field_t field, person_t *person, unsigned int value);

puzzle_t random_puzzle(void)
{
    puzzle_t puzzle;

    unsigned int *seq = malloc(sizeof(unsigned int) * NUM_HOUSES);
    for (puzzle_field_t field = FIELD_COLOR; field <= FIELD_HOBBY; field++)
    {
        random_sequence(seq, NUM_HOUSES);
        set_sequence(field, puzzle.persons, seq);
    }
    free(seq);

    return puzzle;
}

puzzle_t evolve(puzzle_t a, puzzle_t b)
{
    puzzle_t puzzle;

    for (puzzle_field_t field = FIELD_COLOR; field <= FIELD_HOBBY; field++)
    {
        int r = rand() % 2;
        for (size_t i = 0; i < NUM_HOUSES; i++)
        {
            puzzle_field_value_t value =
                r ? get_field_value(field, a.persons[i]) : get_field_value(field, b.persons[i]);

            set_field_value(field, &puzzle.persons[i], value);
        }
    }

    return puzzle;
}

// swap one of the fields of a pair of houses
void mutate(puzzle_t *puzzle)
{
    unsigned int should_mutate = rand() % 100;
    if (should_mutate <= MUTATION_RATE)
    {
        size_t index_a = rand() % NUM_HOUSES;
        size_t index_b = rand() % NUM_HOUSES;
        while (index_a == index_b)
        {
            index_b = rand() % NUM_HOUSES;
        }

        puzzle_field_t field = (puzzle_field_t)(rand() % NUM_HOUSES);
        puzzle_field_value_t temp = get_field_value(field, puzzle->persons[index_a]);
        set_field_value(field, &puzzle->persons[index_a], get_field_value(field, puzzle->persons[index_b]));
        set_field_value(field, &puzzle->persons[index_b], temp);
    }
}

double fitness(const puzzle_t *puzzle)
{
    double max_score = 14;
    int score = 0;

    // Single-house rules
    for (size_t i = 0; i < NUM_HOUSES; i++)
    {
        const person_t *person = &puzzle->persons[i];

        // Rule 1 is implicit (There are 5 houses)

        // Rule 2 (The Englishman lives in the red house)
        if (person->country == COUNTRY_ENGLAND && person->color == COLOR_RED)
        {
            score++;
        }

        // Rule 3 (The Spaniard owns the dog)
        if (person->country == COUNTRY_SPAIN && person->pet == PET_DOG)
        {
            score++;
        }

        // Rule 4 (The person in the green house drinks coffee)
        if (person->color == COLOR_GREEN && person->drink == DRINK_COFFEE)
        {
            score++;
        }

        // Rule 5 (The Ukrainian drinks tea)
        if (person->country == COUNTRY_UKRAINE && person->drink == DRINK_TEA)
        {
            score++;
        }

        // Rule 7 (The snail owner likes to go dancing)
        if (person->pet == PET_SNAIL && person->hobby == HOBBY_DANCING)
        {
            score++;
        }

        // Rule 8 (The person in the yellow house is a painter)
        if (person->color == COLOR_YELLOW && person->hobby == HOBBY_PAINTING)
        {
            score++;
        }

        // Rule 9 (The person in the middle house drinks milk)
        if (i == 2 && person->drink == DRINK_MILK)
        {
            score++;
        }

        // Rule 10 (The Norwegian lives in the first house)
        if (i == 0 && person->country == COUNTRY_NORWAY)
        {
            score++;
        }

        // Rule 13 (The person who plays football drinks orange juice)
        if (person->hobby == HOBBY_FOOTBALL && person->drink == DRINK_OJ)
        {
            score++;
        }

        // Rule 14 (The Japanese person plays chess)
        if (person->country == COUNTRY_JAPAN && person->hobby == HOBBY_CHESS)
        {
            score++;
        }
    }

    // Multi-house rules
    for (size_t i = 0; i < NUM_HOUSES - 1; i++)
    {
        const person_t *person_a = &puzzle->persons[i];
        const person_t *person_b = &puzzle->persons[i + 1];

        // Rule 6 (The green house is immediately to the right of the ivory house)
        if (person_a->color == COLOR_IVORY && person_b->color == COLOR_GREEN)
        {
            score++;
        }

        // Rule 11 (The person who enjoys reading lives in the house next to the person with the fox)
        if ((person_a->hobby == HOBBY_READING && person_b->pet == PET_FOX) ||
            (person_b->hobby == HOBBY_READING && person_a->pet == PET_FOX))
        {
            score++;
        }

        // Rule 12 (The painter's house is next to the house with the horse)
        if ((person_a->hobby == HOBBY_PAINTING && person_b->pet == PET_HORSE) ||
            (person_b->hobby == HOBBY_PAINTING && person_a->pet == PET_HORSE))
        {
            score++;
        }

        // Rule 15 (The Norwegian lives next to the blue house)
        if ((person_a->country == COUNTRY_NORWAY && person_b->color == COLOR_BLUE) ||
            (person_b->country == COUNTRY_NORWAY && person_a->color == COLOR_BLUE))
        {
            score++;
        }
    }

    return (double)score / max_score;
}

void set_sequence(const puzzle_field_t field, person_t persons[NUM_HOUSES], const unsigned int *seq)
{
    for (size_t i = 0; i < NUM_HOUSES; i++)
    {
        switch (field)
        {
        case FIELD_COLOR:
            persons[i].color = (color_t)seq[i];
            break;
        case FIELD_COUNTRY:
            persons[i].country = (country_t)seq[i];
            break;
        case FIELD_PET:
            persons[i].pet = (pet_t)seq[i];
            break;
        case FIELD_DRINK:
            persons[i].drink = (drink_t)seq[i];
            break;
        case FIELD_HOBBY:
            persons[i].hobby = (hobby_t)seq[i];
            break;
        }
    }
}

puzzle_field_value_t get_field_value(const puzzle_field_t field, person_t person)
{

    switch (field)
    {
    case FIELD_COLOR:
        return (puzzle_field_value_t){.color = person.color};
    case FIELD_COUNTRY:
        return (puzzle_field_value_t){.country = person.country};
    case FIELD_PET:
        return (puzzle_field_value_t){.pet = person.pet};
    case FIELD_DRINK:
        return (puzzle_field_value_t){.drink = person.drink};
    case FIELD_HOBBY:
        return (puzzle_field_value_t){.hobby = person.hobby};
    }
    fprintf(stderr, "Invalid field %d\n", field);
    exit(1);
}

void set_field_value(const puzzle_field_t field, person_t *person, puzzle_field_value_t value)
{
    switch (field)
    {
    case FIELD_COLOR:
        person->color = value.color;
        break;
    case FIELD_COUNTRY:
        person->country = value.country;
        break;
    case FIELD_PET:
        person->pet = value.pet;
        break;
    case FIELD_DRINK:
        person->drink = value.drink;
        break;
    case FIELD_HOBBY:
        person->hobby = value.hobby;
        break;
    }
}

void set_field_value_raw(const puzzle_field_t field, person_t *person, unsigned int value)
{
    switch (field)
    {
    case FIELD_COLOR:
        person->color = (color_t)value;
        break;
    case FIELD_COUNTRY:
        person->country = (country_t)value;
        break;
    case FIELD_PET:
        person->pet = (pet_t)value;
        break;
    case FIELD_DRINK:
        person->drink = (drink_t)value;
        break;
    case FIELD_HOBBY:
        person->hobby = (hobby_t)value;
        break;
    }
}
