#include "collatz_conjecture.h"

int steps(int start)
{
    if (start < 1)
    {
        return ERROR_VALUE;
    }

    int count = 0;

    int num = start;
    for (;;)
    {
        if (num == 1)
        {
            return count;
        }

        count++;
        if (num % 2 == 0)
        {
            num /= 2;
        }
        else
        {
            num = (3 * num) + 1;
        }
    }
}
