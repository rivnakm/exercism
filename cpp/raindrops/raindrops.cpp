#include "raindrops.h"

#include <sstream>
#include <string>

namespace raindrops
{
std::string convert(int num)
{
    std::stringstream result;
    if (num % 3 == 0)
    {
        result << "Pling";
    }
    if (num % 5 == 0)
    {
        result << "Plang";
    }
    if (num % 7 == 0)
    {
        result << "Plong";
    }
    if (num % 3 != 0 and num % 5 != 0 and num % 7 != 0)
    {
        result << std::to_string(num);
    }

    return result.str();
}
} // namespace raindrops
