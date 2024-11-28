#include "robot_simulator.h"
#include <string.h>

robot_status_t robot_create(robot_direction_t direction, int x, int y)
{
    robot_status_t robot = {.direction = direction, .position = {.x = x, .y = y}};
    return robot;
}

void robot_move(robot_status_t *robot, const char *commands)
{
    size_t num_commands = strlen(commands);
    for (size_t i = 0; i < num_commands; i++)
    {
        switch (commands[i])
        {
        // Advance
        case 'A':
            switch ((*robot).direction)
            {
            case DIRECTION_NORTH:
                (*robot).position.y++;
                break;
            case DIRECTION_SOUTH:
                (*robot).position.y--;
                break;
            case DIRECTION_EAST:
                (*robot).position.x++;
                break;
            case DIRECTION_WEST:
                (*robot).position.x--;
                break;
            case DIRECTION_MAX:
                break;
            }
            break;
        // Turn left
        case 'L':
            switch ((*robot).direction)
            {
            case DIRECTION_NORTH:
                (*robot).direction = DIRECTION_WEST;
                break;
            default:
                (*robot).direction--;
                break;
            }
            break;
        // Turn right
        case 'R':
            switch ((*robot).direction)
            {
            case DIRECTION_WEST:
                (*robot).direction = DIRECTION_NORTH;
                break;
            default:
                (*robot).direction++;
                break;
            }
            break;
        }
    }
}
