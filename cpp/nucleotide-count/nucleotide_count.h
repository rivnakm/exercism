#if !defined(NUCLEOTIDE_COUNT_H)
#define NUCLEOTIDE_COUNT_H

#include <map>
#include <string>

namespace nucleotide_count
{
std::map<char, int> count(std::string sequence);
} // namespace nucleotide_count

#endif // NUCLEOTIDE_COUNT_H
