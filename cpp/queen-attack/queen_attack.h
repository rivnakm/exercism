#include <stdexcept>
#include <utility>
#if !defined(QUEEN_ATTACK_H)
#define QUEEN_ATTACK_H

namespace queen_attack
{
class chess_board
{
  public:
    chess_board(std::pair<int, int> white, std::pair<int, int> black) : _white(white), _black(black)
    {
        if (_white.first < 0 or _white.first > 7 or _white.second < 0 or _white.second > 7 or _black.first < 0 or
            _black.first > 7 or _black.second < 0 or _black.second > 7 or
            (_white.first == _black.first and _white.second == _black.second))
        {
            throw std::domain_error("Invalid bounds");
        }
    }

    std::pair<int, int> white() const;
    std::pair<int, int> black() const;

    bool can_attack() const;

  private:
    std::pair<int, int> _white, _black;
};
} // namespace queen_attack

#endif // QUEEN_ATTACK_H
