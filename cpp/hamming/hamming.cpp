#include "hamming.h"
#include <stdexcept>

namespace hamming
{
size_t compute(std::string a, std::string b)
{
    if (a.length() != b.length())
    {
        throw std::domain_error("Cannot compute hamming distance for strings of different lengths");
    }

    size_t count{0};
    for (size_t i = 0; i < a.length(); i++)
    {
        if (a[i] != b[i])
        {
            count++;
        }
    }

    return count;
}
} // namespace hamming
