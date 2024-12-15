#include "nucleotide_count.h"
#include <stdexcept>

namespace nucleotide_count
{
std::map<char, int> count(std::string sequence)
{
    std::map<char, int> result{{'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}};
    for (const auto c : sequence)
    {
        if (c != 'A' and c != 'C' and c != 'G' and c != 'T')
        {
            throw std::invalid_argument("Invalid nucleotide in sequence");
        }

        result[c]++;
    }

    return result;
}
} // namespace nucleotide_count
