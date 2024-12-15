#include "rna_transcription.h"

#include <sstream>
#include <stdexcept>

namespace rna_transcription
{
char to_rna(char dna)
{
    switch (dna)
    {
    case 'G':
        return 'C';
    case 'C':
        return 'G';
    case 'T':
        return 'A';
    case 'A':
        return 'U';
    default:
        throw std::invalid_argument("Invalid DNA nucleotide");
    }
}
std::string to_rna(std::string dna)
{
    std::stringstream result;
    for (const auto c : dna)
    {
        result << to_rna(c);
    }
    return result.str();
}
} // namespace rna_transcription
