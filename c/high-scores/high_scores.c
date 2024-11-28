#include "high_scores.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_sorted(const int32_t *scores, size_t len);
void sort_scores(int32_t **scores, size_t len);

/// Return the latest score.
int32_t latest(const int32_t *scores, size_t scores_len)
{
    return scores[scores_len - 1];
}

/// Return the highest score.
int32_t personal_best(const int32_t *scores, size_t scores_len)
{
    int32_t max = INT32_MIN;

    for (size_t i = 0; i < scores_len; i++)
    {
        int32_t score = scores[i];
        if (score > max)
        {
            max = score;
        }
    }
    return max;
}

/// Write the highest scores to `output` (in non-ascending order).
/// Return the number of scores written.
size_t personal_top_three(const int32_t *scores, size_t scores_len, int32_t *output)
{
    int32_t *sorted = malloc(sizeof(int32_t) * scores_len);
    memcpy(sorted, scores, sizeof(int32_t) * scores_len);

    sort_scores(&sorted, scores_len);

    size_t num_items = scores_len < 3 ? scores_len : 3;
    for (size_t i = 0; i < num_items; i++)
    {
        output[i] = sorted[i];
    }

    free(sorted);

    return num_items;
}

bool is_sorted(const int32_t *scores, size_t len)
{
    for (size_t i = 1; i < len; i++)
    {
        if (scores[i - 1] < scores[i])
        {
            return false;
        }
    }
    return true;
}

void sort_scores(int32_t **scores, size_t len)
{
    while (!is_sorted(*scores, len))
    {
        for (size_t i = 1; i < len; i++)
        {
            if ((*scores)[i - 1] < (*scores)[i])
            {
                int32_t temp = (*scores)[i - 1];
                (*scores)[i - 1] = (*scores)[i];
                (*scores)[i] = temp;
            }
        }
    }
}
