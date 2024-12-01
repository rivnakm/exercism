#include "secret_handshake.h"

#include <stdlib.h>

void reverse_commands(char **cmds, size_t length);

const char **commands(size_t number)
{
    // No commands
    if ((number & 0xF) == 0)
    {
        char **cmds = malloc(sizeof(char *));
        cmds[0] = NULL;

        return (const char **)cmds;
    }

    size_t length = 0;
    size_t capacity = 4;
    char **cmds = malloc(sizeof(char *) * capacity);

    if ((number & 0x1) > 0)
    {
        cmds[length++] = "wink";
    }
    if ((number & 0x2) > 0)
    {
        cmds[length++] = "double blink";
    }
    if ((number & 0x4) > 0)
    {
        cmds[length++] = "close your eyes";
    }
    if ((number & 0x8) > 0)
    {
        cmds[length++] = "jump";
    }
    if ((number & 0x10) > 0)
    {
        reverse_commands(cmds, length);
    }

    return (const char **)cmds;
}

void reverse_commands(char **cmds, size_t length)
{
    for (size_t i = 0; i < (length / 2); i++)
    {
        char *temp = cmds[length - 1 - i];
        cmds[length - 1 - i] = cmds[i];
        cmds[i] = temp;
    }
}
