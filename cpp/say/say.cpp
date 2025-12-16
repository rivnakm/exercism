#include "say.h"

#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace say
{

std::string chunk(uint16_t num);
std::string ones(uint8_t num);
std::string teens(uint8_t num);
std::string tens(uint8_t num);

std::string in_english(int64_t num)
{
    if (num > 999'999'999'999 || num < 0)
    {
        throw std::domain_error{"num"};
    }

    if (num == 0)
    {
        return "zero";
    }

    std::stringstream result;

    uint16_t trillions = (num % 1'000'000'000) / 1'000'000'000'000;
    uint16_t billions = (num % 1'000'000'000'000) / 1'000'000'000;
    uint16_t millions = (num % 1'000'000'000) / 1'000'000;
    uint16_t thousands = (num % 1'000'000) / 1000;
    uint16_t rest = num % 1000;

    if (trillions > 0)
    {
        auto tri_chunk = chunk(trillions);
        result << tri_chunk << " trillion";
        if (rest > 0 || thousands > 0 || millions > 0 || billions > 0)
        {
            result << " ";
        }
    }
    if (billions > 0)
    {
        auto bil_chunk = chunk(billions);
        result << bil_chunk << " billion";
        if (rest > 0 || thousands > 0 || millions > 0)
        {
            result << " ";
        }
    }
    if (millions > 0)
    {
        auto mil_chunk = chunk(millions);
        result << mil_chunk << " million";
        if (rest > 0 || thousands > 0)
        {
            result << " ";
        }
    }
    if (thousands > 0)
    {
        auto thou_chunk = chunk(thousands);
        result << thou_chunk << " thousand";
        if (rest > 0)
        {
            result << " ";
        }
    }
    if (rest > 0)
    {
        auto rest_chunk = chunk(rest);
        result << rest_chunk;
    }

    return result.str();
}

std::string chunk(uint16_t num)
{

    if (num <= 9)
    {
        return ones(num);
    }
    if (num <= 19)
    {
        return teens(num);
    }

    std::stringstream result;

    if (num <= 99)
    {
        result << tens(num / 10);
        if (num % 10 > 0)
        {
            result << "-" << ones(num % 10);
        }
    }
    else if (num <= 999)
    {
        result << ones(num / 100) << " hundred";

        if (num % 100 > 10)
        {
            result << " " << tens((num % 100) / 10);
            if (num % 10 > 0)
            {
                result << "-";
            }
        }
        if (num % 10 > 0)
        {
            result << ones(num % 10);
        }
    }

    return result.str();
}

std::string ones(uint8_t num)
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

std::string teens(uint8_t num)
{
    switch (num)
    {
    case 10:
        return "ten";
    case 11:
        return "eleven";
    case 12:
        return "twelve";
    case 13:
        return "thirteen";
    case 15:
        return "fifteen";
    case 14:
    case 16:
    case 17:
    case 18:
    case 19:
        return ones(num - 10) + "teen";
    }

#ifdef __cpp_lib_unreachable
    std::unreachable();
#else
#if defined(_MSC_VER) && !defined(__clang__)
    __assume(false);
#else
    __builtin_unreachable();
#endif
#endif
}

std::string tens(uint8_t num)
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

} // namespace say
