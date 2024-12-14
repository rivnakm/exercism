#if !defined(ATBASH_CIPHER_H)
#define ATBASH_CIPHER_H

#include <string>

namespace atbash_cipher
{
std::string encode(std::string phrase);
std::string decode(std::string phrase);
} // namespace atbash_cipher

#endif // ATBASH_CIPHER_H
