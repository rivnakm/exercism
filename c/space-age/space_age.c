#include "space_age.h"

float age(planet_t planet, int64_t seconds)
{
    float earth_years = (float)seconds / 31557600.0F;

    switch (planet)
    {
    case MERCURY:
        return earth_years / 0.2408467F;
    case VENUS:
        return earth_years / 0.61519726F;
    case EARTH:
        return earth_years;
    case MARS:
        return earth_years / 1.8808158F;
    case JUPITER:
        return earth_years / 11.862615F;
    case SATURN:
        return earth_years / 29.447498F;
    case URANUS:
        return earth_years / 84.016846F;
    case NEPTUNE:
        return earth_years / 164.79132F;
    default:
        return -1;
    }
}
