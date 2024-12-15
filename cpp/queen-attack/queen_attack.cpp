#include "queen_attack.h"

#include <cstdlib>

namespace queen_attack
{
std::pair<int, int> chess_board::white() const
{
    return _white;
}

std::pair<int, int> chess_board::black() const
{
    return _black;
}

bool chess_board::can_attack() const
{
    return _white.first == _black.first or _white.second == _black.second or
           std::abs(_white.first - _black.first) == std::abs(_white.second - _black.second);
}
} // namespace queen_attack
