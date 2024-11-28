#include "eliuds_eggs.h"
#include <stddef.h>

unsigned int egg_count(unsigned int coop)
{
    unsigned int eggs = coop & 0x1;
    size_t len = sizeof(unsigned int) * 8;
    for (size_t i = 0; i < len; i++)
    {
        coop >>= 1;
        eggs += coop & 0x1;
    }

    return eggs;
}
