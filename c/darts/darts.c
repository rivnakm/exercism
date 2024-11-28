#include "darts.h"
#include <math.h>
#include <stdint.h>

uint8_t score(coordinate_t pos)
{
    float dist = sqrtf(powf(pos.x, 2) + powf(pos.y, 2));

    if (dist > OUTER_CIRCLE_RADIUS)
    {
        return 0;
    }
    if (dist > MIDDLE_CIRCLE_RADIUS)
    {
        return 1;
    }
    if (dist > INNER_CIRCLE_RADIUS)
    {
        return 5;
    }
    return 10;
}
