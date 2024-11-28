#include "grains.h"
#include <stdint.h>

uint64_t square(uint8_t index)
{
    if (index < 1 || index > 64)
    {
        return 0;
    }
    uint64_t out = 1;
    return out << (index - 1);
}

uint64_t total(void)
{
    uint64_t sum = 0;
    for (uint64_t i = 1; i <= 64; i++)
    {
        sum += square(i);
    }

    return sum;
}
