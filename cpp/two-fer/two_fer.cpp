#include "two_fer.h"

namespace two_fer
{
std::string two_fer()
{
    return two_fer("you");
}
std::string two_fer(std::string name)
{
    return "One for " + name + ", one for me.";
}
} // namespace two_fer
