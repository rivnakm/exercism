#include "collatz_conjecture.h"
#include <stdexcept>

namespace collatz_conjecture
{
size_t steps(int number)
{
    if (number <= 0)
    {
        throw std::domain_error{"Number must be greater than zero"};
    }

    size_t steps{0};
    for (; number != 1; steps++)
    {
        if (number % 2 == 0)
        {
            number /= 2;
        }
        else
        {
            number = (3 * number) + 1;
        }
    }
    return steps;
}
} // namespace collatz_conjecture
