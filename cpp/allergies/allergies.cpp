#include "allergies.h"

namespace allergies
{
allergy_test::allergy_test(const int score)
{
    if ((score & 0x1) > 0)
    {
        _allergies.emplace("eggs");
    }
    if ((score & 0x2) > 0)
    {
        _allergies.emplace("peanuts");
    }
    if ((score & 0x4) > 0)
    {
        _allergies.emplace("shellfish");
    }
    if ((score & 0x8) > 0)
    {
        _allergies.emplace("strawberries");
    }
    if ((score & 0x10) > 0)
    {
        _allergies.emplace("tomatoes");
    }
    if ((score & 0x20) > 0)
    {
        _allergies.emplace("chocolate");
    }
    if ((score & 0x40) > 0)
    {
        _allergies.emplace("pollen");
    }
    if ((score & 0x80) > 0)
    {
        _allergies.emplace("cats");
    }
}

bool allergy_test::is_allergic_to(const std::string allergen) const
{
    return _allergies.find(allergen) != _allergies.end();
}

std::unordered_set<std::string> allergy_test::get_allergies() const
{
    return _allergies;
}
} // namespace allergies
