#include "simulation.h"
#include "parameters.h"
#include "person.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
    const puzzle_t *puzzle;
    double fitness;
} puzzle_ranking_t;

void get_rankings(puzzle_ranking_t *rankings, const puzzle_t *generation);
puzzle_t sample_rankings(const puzzle_ranking_t *rankings, const size_t sample_size);

int ranking_sort(const void *a, const void *b);

puzzle_t run_simulation(void)
{
    puzzle_t *generation = malloc(sizeof(puzzle_t) * POPULATION);
    puzzle_ranking_t *rankings = malloc(sizeof(puzzle_ranking_t) * POPULATION);
    puzzle_ranking_t *samples = malloc(sizeof(puzzle_ranking_t) * SAMPLE_SIZE);

    // generate initial generation
    for (size_t i = 0; i < POPULATION; i++)
    {
        generation[i] = random_puzzle();
    }

    // rank members of current generation
    get_rankings(rankings, generation);

    while (true)
    {
        for (size_t i = 0; i < POPULATION; i++)
        {
            // Found a solution, return
            if (rankings[i].fitness >= 1.0)
            {
                puzzle_t correct_puzzle = *rankings[i].puzzle;

                free(samples);
                free(rankings);
                free(generation);

                return correct_puzzle;
            }
        }

        // create next generation
        for (size_t i = 0; i < POPULATION; i++)
        {
            puzzle_t parent_a = sample_rankings(rankings, SAMPLE_SIZE);
            puzzle_t parent_b = sample_rankings(rankings, SAMPLE_SIZE);

            generation[i] = evolve(parent_a, parent_b);
            mutate(&generation[i]);
        }

        // rank members of current generation
        get_rankings(rankings, generation);
    }
}

void get_rankings(puzzle_ranking_t *rankings, const puzzle_t *generation)
{
    for (size_t i = 0; i < POPULATION; i++)
    {
        rankings[i] = (puzzle_ranking_t){.puzzle = &generation[i], .fitness = fitness(&generation[i])};
    }
}

puzzle_t sample_rankings(const puzzle_ranking_t *rankings, const size_t sample_size)
{
    puzzle_ranking_t *sample = malloc(sizeof(puzzle_ranking_t) * sample_size);
    for (size_t i = 0; i < sample_size; i++)
    {
        size_t random_i = rand() % POPULATION;
        sample[i] = rankings[random_i];
    }

    // sorts in ascending order
    qsort((void *)sample, sample_size, sizeof(puzzle_ranking_t), ranking_sort);

    puzzle_t result = *sample[sample_size - 1].puzzle;

    free(sample);

    return result;
}

int ranking_sort(const void *a, const void *b)
{
    if (((puzzle_ranking_t *)a)->fitness < ((puzzle_ranking_t *)b)->fitness)
    {
        return -1;
    }
    else if (((puzzle_ranking_t *)a)->fitness > ((puzzle_ranking_t *)b)->fitness)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
