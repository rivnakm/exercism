#include "triangle.h"
#include <stdexcept>

namespace triangle
{
bool is_valid(double a, double b, double c);

flavor kind(double a, double b, double c)
{
    if (a <= 0 or b <= 0 or c <= 0)
    {
        throw std::domain_error{"Sides must be positive length"};
    }
    if (!is_valid(a, b, c))
    {
        throw std::domain_error{"Triangle inequality violation"};
    }

    if (a == b and b == c)
    {
        return flavor::equilateral;
    }
    if (a == b or b == c or a == c)
    {
        return flavor::isosceles;
    }

    return flavor::scalene;
}

bool is_valid(double a, double b, double c)
{
    return a + b >= c and b + c >= a and a + c >= b;
}
} // namespace triangle
