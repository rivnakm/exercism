#include "raindrops.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void convert(char result[], int drops)
{
    bool found = false;
    if (drops % 3 == 0)
    {
        found = true;
        strcat(result, "Pling");
    }
    if (drops % 5 == 0)
    {
        found = true;
        strcat(result, "Plang");
    }
    if (drops % 7 == 0)
    {
        found = true;
        strcat(result, "Plong");
    }

    if (!found)
    {
        sprintf(result, "%i", drops);
    }
}
