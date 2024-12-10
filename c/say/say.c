#include "say.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN (255)

char *chunk(uint16_t num);
char *ones(uint8_t num);
char *teens(uint8_t num);
char *tens(uint8_t num);

int say(int64_t input, char **ans)
{
    if (input > 999999999999 || input < 0)
    {
        return -1;
    }

    *ans = malloc(MAX_STRING_LEN + 1);
    memset(*ans, '\0', MAX_STRING_LEN + 1);

    if (input == 0)
    {
        sprintf(*ans, "zero");
        return EXIT_SUCCESS;
    }

    input = labs(input);

    uint16_t trillions = (input % 1000000000) / 1000000000000;
    uint16_t billions = (input % 1000000000000) / 1000000000;
    uint16_t millions = (input % 1000000000) / 1000000;
    uint16_t thousands = (input % 1000000) / 1000;
    uint16_t rest = input % 1000;

    if (trillions > 0)
    {
        char *trillions_chunk = chunk(trillions);
        strcat(*ans, trillions_chunk);
        if (rest > 0 || thousands > 0 || millions > 0)
        {
            strcat(*ans, " trillion ");
        }
        else
        {
            strcat(*ans, " trillion");
        }

        free(trillions_chunk);
    }
    if (billions > 0)
    {
        char *billions_chunk = chunk(billions);
        strcat(*ans, billions_chunk);
        if (rest > 0 || thousands > 0 || millions > 0)
        {
            strcat(*ans, " billion ");
        }
        else
        {
            strcat(*ans, " billion");
        }

        free(billions_chunk);
    }
    if (millions > 0)
    {
        char *millions_chunk = chunk(millions);
        strcat(*ans, millions_chunk);
        if (rest > 0 || thousands > 0)
        {
            strcat(*ans, " million ");
        }
        else
        {
            strcat(*ans, " million");
        }

        free(millions_chunk);
    }
    if (thousands > 0)
    {
        char *thousands_chunk = chunk(thousands);
        strcat(*ans, thousands_chunk);
        if (rest == 0)
        {
            strcat(*ans, " thousand");
        }
        else
        {
            strcat(*ans, " thousand ");
        }

        free(thousands_chunk);
    }
    if (rest > 0)
    {
        char *rest_chunk = chunk(rest);
        strcat(*ans, rest_chunk);
        free(rest_chunk);
    }

    return EXIT_SUCCESS;
}

char *chunk(uint16_t num)
{
    char *result = malloc(50);
    memset(result, '\0', 50);
    if (num <= 9)
    {
        strcat(result, ones(num));
    }
    else if (num <= 19)
    {
        char *teens_str = teens(num);
        strcat(result, teens_str);
        free(teens_str);
    }
    else if (num <= 99)
    {
        strcat(result, tens(num / 10));

        if (num % 10 > 0)
        {
            strcat(result, "-");
            strcat(result, ones(num % 10));
        }
    }
    else if (num <= 999)
    {
        strcat(result, ones(num / 100));

        strcat(result, " hundred");

        if (num % 100 > 10)
        {
            strcat(result, " ");
            strcat(result, tens((num % 100) / 10));
            if (num % 10 > 0)
            {
                strcat(result, "-");
            }
        }

        if (num % 10 > 0)
        {
            strcat(result, ones(num % 10));
        }
    }

    return result;
}

char *ones(uint8_t num)
{
    switch (num)
    {
    case 1:
        return "one";
    case 2:
        return "two";
    case 3:
        return "three";
    case 4:
        return "four";
    case 5:
        return "five";
    case 6:
        return "six";
    case 7:
        return "seven";
    case 8:
        return "eight";
    case 9:
        return "nine";
    default:
        // "zero" only happens for 0 exactly, handle that separately
        return "";
    }
}

char *teens(uint8_t num)
{
    char *result = malloc(20);
    memset(result, '\0', 20);
    switch (num)
    {
    case 10:
        strcat(result, "ten");
        break;
    case 11:
        strcat(result, "eleven");
        break;
    case 12:
        strcat(result, "twelve");
        break;
    case 13:
        strcat(result, "thirteen");
        break;
    case 15:
        strcat(result, "fifteen");
        break;
    case 14:
        /* fallthrough */
    case 16:
        /* fallthrough */
    case 17:
        /* fallthrough */
    case 18:
        /* fallthrough */
    case 19:
        sprintf(result, "%steen", ones(num - 10));
        break;
    default:
        break;
    }
    return result;
}

char *tens(uint8_t num)
{
    switch (num)
    {
    case 2:
        return "twenty";
    case 3:
        return "thirty";
    case 4:
        return "forty";
    case 5:
        return "fifty";
    case 6:
        return "sixty";
    case 7:
        return "seventy";
    case 8:
        return "eighty";
    case 9:
        return "ninety";
    default:
        return "";
    }
}
