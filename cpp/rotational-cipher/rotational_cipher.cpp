#include "rotational_cipher.h"

#include <cctype>
#include <sstream>

namespace rotational_cipher
{
char rotate_single(char c, int factor);
std::string rotate(std::string phrase, int factor)
{
    std::stringstream result;
    for (auto &c : phrase)
    {
        result << rotate_single(c, factor);
    }

    return result.str();
}

char rotate_single(char c, int factor)
{
    if (!std::isalpha(c))
    {
        return c;
    }

    if (std::isupper(c))
    {
        c -= 'A';
        c += factor;
        c %= 26;
        c += 'A';
    }
    else
    {
        c -= 'a';
        c += factor;
        c %= 26;
        c += 'a';
    }

    return c;
}
} // namespace rotational_cipher
