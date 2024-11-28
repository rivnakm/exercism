#include "resistor_color_trio.h"
#include <math.h>
#include <stdint.h>

resistor_value_t color_code(resistor_band_t *bands)
{
    uint64_t value = ((bands[0] * 10) + bands[1]) * pow(10, bands[2]);
    resistor_value_unit_t unit = OHMS;

    if (value == 0)
    {
        // no-op
    }
    else if (value % (uint64_t)pow(10, 9) == 0)
    {
        value /= pow(10, 9);
        unit = GIGAOHMS;
    }
    else if (value % (uint64_t)pow(10, 6) == 0)
    {
        value /= pow(10, 6);
        unit = MEGAOHMS;
    }
    else if (value % (uint64_t)pow(10, 3) == 0)
    {
        value /= pow(10, 3);
        unit = KILOOHMS;
    }

    resistor_value_t full_value = {.value = value, .unit = unit};
    return full_value;
}
