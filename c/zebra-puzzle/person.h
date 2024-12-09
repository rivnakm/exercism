#ifndef PERSON_H
#define PERSON_H

#define NUM_HOUSES (5)

typedef enum
{
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_IVORY,
} color_t;

typedef enum
{
    COUNTRY_ENGLAND,
    COUNTRY_SPAIN,
    COUNTRY_UKRAINE,
    COUNTRY_NORWAY,
    COUNTRY_JAPAN,
} country_t;

typedef enum
{
    PET_DOG,
    PET_SNAIL,
    PET_HORSE,
    PET_FOX,
    PET_ZEBRA,
} pet_t;

typedef enum
{
    DRINK_COFFEE,
    DRINK_TEA,
    DRINK_MILK,
    DRINK_OJ,
    DRINK_WATER,
} drink_t;

typedef enum
{
    HOBBY_DANCING,
    HOBBY_PAINTING,
    HOBBY_FOOTBALL,
    HOBBY_CHESS,
    HOBBY_READING,
} hobby_t;

typedef struct
{
    color_t color;
    country_t country;
    pet_t pet;
    drink_t drink;
    hobby_t hobby;
} person_t;

typedef struct
{
    person_t persons[NUM_HOUSES];
} puzzle_t;

puzzle_t random_puzzle(void);
puzzle_t evolve(puzzle_t a, puzzle_t b);
void mutate(puzzle_t *puzzle);
double fitness(const puzzle_t *puzzle);

#endif
