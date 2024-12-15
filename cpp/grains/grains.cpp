#include "grains.h"
#include <climits>

namespace grains
{
unsigned long long square(int square_num)
{
    unsigned long long out{1};
    out <<= (square_num - 1);
    return out;
}

unsigned long long total()
{
    return ULLONG_MAX;
}
} // namespace grains
