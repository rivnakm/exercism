#include "queen_attack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

bool in_bounds(position_t pos);

attack_status_t can_attack(position_t queen_1, position_t queen_2)
{
    // OOB
    if (!in_bounds(queen_1) || !in_bounds(queen_2))
    {
        return INVALID_POSITION;
    }

    // Overlapping
    if (queen_1.column == queen_2.column && queen_1.row == queen_2.row)
    {
        return INVALID_POSITION;
    }

    // Inline
    if (queen_1.column == queen_2.column || queen_1.row == queen_2.row)
    {
        return CAN_ATTACK;
    }

    uint8_t dy = abs((int8_t)queen_1.row - (int8_t)queen_2.row);
    uint8_t dx = abs((int8_t)queen_1.column - (int8_t)queen_2.column);
    // Diagonal
    if (dy == dx)
    {
        return CAN_ATTACK;
    }

    return CAN_NOT_ATTACK;
}

bool in_bounds(position_t pos)
{
    if (pos.row > 7 || pos.column > 7)
    {
        return false;
    }
    return true;
}
