#include "nth_prime.h"
#include <stdexcept>

namespace nth_prime
{
bool is_prime(int n);

int nth(int n)
{
    if (n <= 0)
    {
        throw std::domain_error{"n must be greater than zero"};
    }

    int num{0};
    int count{0};
    for (int i = 0; count < n; i++)
    {
        if (is_prime(i))
        {
            num = i;
            count++;
        }
    }

    return num;
}

bool is_prime(int n)
{
    if (n < 2)
    {
        return false;
    }
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}
} // namespace nth_prime
