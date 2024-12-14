#include "protein_translation.h"

#include <algorithm>
#include <optional>

namespace protein_translation
{

std::vector<std::string> codons(std::string sequence);
std::optional<std::string> classify_codon(std::string codon);

std::vector<std::string> proteins(std::string sequence)
{
    std::vector<std::string> result;
    for (auto codon : codons(sequence))
    {
        auto classified = classify_codon(codon);
        if (!classified.has_value())
        {
            break;
        }

        result.emplace_back(classified.value());
    }

    return result;
}

std::vector<std::string> codons(std::string sequence)
{
    std::vector<std::string> result;
    for (size_t i = 0; i < sequence.length(); i += 3)
    {
        auto codon_len = std::min<size_t>(3, sequence.length() - i);
        result.emplace_back(sequence.substr(i, codon_len));
    }
    return result;
}

std::optional<std::string> classify_codon(std::string codon)
{
    if (codon == "UAA" or codon == "UAG" or codon == "UGA")
    {
        return std::nullopt;
    }
    if (codon == "AUG")
    {
        return std::optional<std::string>{"Methionine"};
    }
    if (codon == "UUU" or codon == "UUC")
    {
        return std::optional<std::string>{"Phenylalanine"};
    }
    if (codon == "UUA" or codon == "UUG")
    {
        return std::optional<std::string>{"Leucine"};
    }
    if (codon == "UCU" or codon == "UCC" or codon == "UCA" or codon == "UCG")
    {
        return std::optional<std::string>{"Serine"};
    }
    if (codon == "UAU" or codon == "UAC")
    {
        return std::optional<std::string>{"Tyrosine"};
    }
    if (codon == "UGU" or codon == "UGC")
    {
        return std::optional<std::string>{"Cysteine"};
    }
    if (codon == "UGG")
    {
        return std::optional<std::string>{"Tryptophan"};
    }
    return std::nullopt;
}
} // namespace protein_translation
