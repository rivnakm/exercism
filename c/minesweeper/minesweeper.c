#include "minesweeper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **annotate(const char **minefield, const size_t rows)
{
    if (rows == 0)
    {
        return NULL;
    }

    size_t columns = strlen(minefield[0]);

    char **result = malloc(sizeof(char *) * rows);
    for (size_t i = 0; i < rows; i++)
    {
        result[i] = malloc(sizeof(char) * (columns + 1));
        strcpy(result[i], minefield[i]);
    }

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            unsigned short count = 0;
            if (minefield[i][j] == '*')
            {
                continue;
            }

            for (int n = -1; n <= 1; n++)
            {
                if ((int)i + n < 0 || (int)i + n >= (int)rows)
                {
                    continue;
                }
                for (int m = -1; m <= 1; m++)
                {
                    if ((int)j + m < 0 || (int)j + m >= (int)columns)
                    {
                        continue;
                    }
                    if (minefield[i + n][j + m] == '*')
                    {
                        count++;
                    }
                }
            }
            result[i][j] = count == 0 ? ' ' : count + 48;
        }
    }

    return result;
}

// FIXME: Can't properly free memory with this function signature,
// needs an upstream change to pass `make memtest`
void free_annotation(char **annotation)
{
    free(annotation);
}
