#include "reverse_string.h"

#include <iterator>
#include <sstream>

namespace reverse_string
{
std::string reverse_string(std::string input)
{
    std::stringstream result;
    for (auto it = input.crbegin(); it != input.crend(); ++it)
    {
        result << *it;
    }
    return result.str();
}
} // namespace reverse_string
