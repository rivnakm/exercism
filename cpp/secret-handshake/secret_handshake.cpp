#include "secret_handshake.h"
#include <algorithm>
#include <vector>

namespace secret_handshake
{
std::vector<std::string> commands(int code)
{
    std::vector<std::string> result;
    if ((code & 0b1) > 0)
    {
        result.emplace_back("wink");
    }
    if ((code & 0b10) > 0)
    {
        result.emplace_back("double blink");
    }
    if ((code & 0b100) > 0)
    {
        result.emplace_back("close your eyes");
    }
    if ((code & 0b1000) > 0)
    {
        result.emplace_back("jump");
    }
    if ((code & 0b1'0000) > 0)
    {
        std::reverse(result.begin(), result.end());
    }

    return result;
}
} // namespace secret_handshake
