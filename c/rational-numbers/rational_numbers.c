#include "rational_numbers.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int16_t gcf(int16_t num1, int16_t num2);

rational_t inverse(rational_t r);

rational_t add(rational_t r1, rational_t r2)
{
    int16_t denominator = r1.denominator * r2.denominator;
    int16_t numerator = (r1.numerator * r2.denominator) + (r2.numerator * r1.denominator);

    rational_t result = {.numerator = numerator, .denominator = denominator};
    return reduce(result);
}

rational_t subtract(rational_t r1, rational_t r2)
{
    int16_t denominator = r1.denominator * r2.denominator;
    int16_t numerator = (r1.numerator * r2.denominator) - (r2.numerator * r1.denominator);

    rational_t result = {.numerator = numerator, .denominator = denominator};
    return reduce(result);
}

rational_t multiply(rational_t r1, rational_t r2)
{
    int16_t numerator = r1.numerator * r2.numerator;
    int16_t denominator = r1.denominator * r2.denominator;

    rational_t result = {.numerator = numerator, .denominator = denominator};
    return reduce(result);
}

rational_t divide(rational_t r1, rational_t r2)
{
    return multiply(r1, inverse(r2));
}

rational_t absolute(rational_t r)
{
    rational_t result = {.numerator = abs(r.numerator), .denominator = abs(r.denominator)};
    return reduce(result);
}

rational_t exp_rational(rational_t r, int16_t n)
{
    if (n < 0)
    {
        n = abs(n);
        rational_t result = {.numerator = pow(r.denominator, n), .denominator = pow(r.numerator, n)};
        return reduce(result);
    }
    rational_t result = {.numerator = pow(r.numerator, n), .denominator = pow(r.denominator, n)};
    return reduce(result);
}

float exp_real(uint16_t x, rational_t r)
{
    return powf(x, (float)r.numerator / r.denominator);
}

rational_t reduce(rational_t r)
{
    if (r.numerator == 0)
    {
        rational_t result = {.numerator = 0, .denominator = 1};
        return result;
    }

    int16_t num_gcf = gcf(r.numerator, r.denominator);
    if (r.numerator < 0 && r.denominator < 0)
    {
        num_gcf = -num_gcf;
    }

    printf("reducing %d/%d with gcf: %d\n", r.numerator, r.denominator, num_gcf);

    rational_t result = {.numerator = r.numerator / num_gcf, .denominator = r.denominator / num_gcf};

    // negative should live in the numerator
    if (result.denominator < 0 && result.numerator >= 0)
    {
        result.numerator = -result.numerator;
        result.denominator = -result.denominator;
    }
    return result;
}

int16_t gcf(int16_t num1, int16_t num2)
{
    num1 = abs(num1);
    num2 = abs(num2);

    for (int16_t test = num1 > num2 ? num2 : num1; test > 0; test--)
    {
        if (num1 % test == 0 && num2 % test == 0)
        {
            return test;
        }
    }
    return 1;
}

rational_t inverse(rational_t r)
{
    rational_t result = {.numerator = r.denominator, .denominator = r.numerator};
    return result;
}
