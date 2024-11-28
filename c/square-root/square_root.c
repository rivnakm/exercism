#include "square_root.h"

#include <math.h>
#include <stdbool.h>

#define PRECISION 0.1

bool check(double square, double sqrt);

uint16_t square_root(uint32_t number)
{
    const double least_sq_reg = 0.485;
    double two_n = floor(log2(number));
    double a = (double)number / pow(2, two_n);
    double guess = (least_sq_reg + least_sq_reg * a) * pow(2, two_n / 2);

    while (!check(number, guess))
    {
        guess = 0.5 * (guess + ((double)number / guess));
    }

    // Rounding here is silly, but so is having this function return an int,
    // not sure why the tests are set up this way.
    return (uint16_t)round(guess);
}

bool check(double square, double sqrt)
{
    return (fabs(square - pow(sqrt, 2)) < PRECISION);
}
