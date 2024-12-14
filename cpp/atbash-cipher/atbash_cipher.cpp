#include "atbash_cipher.h"

#include <cctype>
#include <sstream>

char encode_char(char c);

namespace atbash_cipher
{
std::string encode(std::string phrase)
{
    std::stringstream result;
    size_t block_size{0};
    for (size_t i = 0; i < phrase.length(); i++)
    {
        if (std::isspace(phrase[i]) or std::ispunct(phrase[i]))
        {
            continue;
        }

        if (block_size == 5)
        {
            result << " ";
            block_size = 0;
        }

        result << encode_char(phrase[i]);
        block_size++;
    }

    return result.str();
}

std::string decode(std::string phrase)
{
    std::stringstream result;
    for (size_t i = 0; i < phrase.length(); i++)
    {
        if (phrase[i] == ' ')
        {
            continue;
        }
        result << encode_char(phrase[i]);
    }

    return result.str();
}
} // namespace atbash_cipher

char encode_char(char c)
{
    if (!std::isalpha(c))
    {
        return c;
    }

    c = std::tolower(c);
    c -= 'a';
    c = 25 - c;
    c += 'a';

    return c;
}
