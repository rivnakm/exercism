#include "pangram.h"

#include <cctype>
#include <set>

namespace pangram
{
bool is_pangram(std::string phrase)
{
    std::set<char> letters;
    for (auto c : phrase)
    {
        if (!std::isalpha(c))
        {
            continue;
        }

        letters.insert(std::tolower(c));
    }

    return letters.size() == 26;
}
} // namespace pangram
