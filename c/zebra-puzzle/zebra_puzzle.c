#include "zebra_puzzle.h"
#include "person.h"
#include "simulation.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char *country_to_str(country_t country);

solution_t solve_puzzle(void)
{
    solution_t solution;

    puzzle_t correct_puzzle = run_simulation();

    for (size_t i = 0; i < NUM_HOUSES; i++)
    {
        person_t *person = &correct_puzzle.persons[i];
        if (person->drink == DRINK_WATER)
        {
            solution.drinks_water = country_to_str(person->country);
        }
        if (person->pet == PET_ZEBRA)
        {
            solution.owns_zebra = country_to_str(person->country);
        }
    }

    return solution;
}

char *country_to_str(country_t country)
{
    switch (country)
    {
    case COUNTRY_ENGLAND:
        return "English";
    case COUNTRY_SPAIN:
        return "Spanish";
    case COUNTRY_UKRAINE:
        return "Ukrainian";
    case COUNTRY_NORWAY:
        return "Norwegian";
    case COUNTRY_JAPAN:
        return "Japanese";
    }
    fprintf(stderr, "Invalid country %d\n", country);
    exit(1);
}
