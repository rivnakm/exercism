#include "knapsack.h"
#include <stdlib.h>
#include <string.h>

unsigned int maximum_value(const unsigned int maximum_weight, const item_t *items, const size_t item_count)
{
    size_t t_cols = maximum_weight + 1;
    size_t t_rows = item_count + 1;
    unsigned int *table = malloc(sizeof(unsigned int) * t_cols * t_rows);
    memset(table, 0, sizeof(unsigned int) * t_cols * t_rows);

    for (size_t row = 1; row < t_rows; row++)
    {
        for (size_t col = 0; col < t_cols; col++)
        {
            if (items[row - 1].weight <= col)
            {
                unsigned int exclude = table[((row - 1) * t_cols) + col];
                unsigned int include =
                    table[((row - 1) * t_cols) + (col - items[row - 1].weight)] + items[row - 1].value;

                table[(row * t_cols) + col] = exclude > include ? exclude : include;
            }
            else
            {

                table[(row * t_cols) + col] = table[((row - 1) * t_cols) + col];
            }
        }
    }

    unsigned int result = table[(item_count * t_cols) + maximum_weight];

    free(table);

    return result;
}
