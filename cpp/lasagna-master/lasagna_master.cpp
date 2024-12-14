#include "lasagna_master.h"
#include <algorithm>

const int qty_per_noodle = 50;
const double qty_per_sauce = 0.2;

namespace lasagna_master
{

int preparationTime(std::vector<std::string> layers, int avg_time)
{
    return avg_time * static_cast<int>(layers.size());
}

struct amount quantities(std::vector<std::string> ingredients)
{
    auto num_noodles = std::count_if(ingredients.begin(), ingredients.end(),
                                     [](std::string ingredient) { return ingredient == "noodles"; });
    auto num_sauce = std::count_if(ingredients.begin(), ingredients.end(),
                                   [](std::string ingredient) { return ingredient == "sauce"; });

    return {static_cast<int>(num_noodles) * qty_per_noodle, static_cast<double>(num_sauce) * qty_per_sauce};
}

void addSecretIngredient(std::vector<std::string> &myList, const std::vector<std::string> friendList)
{
    addSecretIngredient(myList, friendList.back());
}

void addSecretIngredient(std::vector<std::string> &myList, const std::string secretIngredient)
{
    std::replace(myList.begin(), myList.end(), std::string{"?"}, secretIngredient);
}

std::vector<double> scaleRecipe(std::vector<double> quantities, double factor)
{
    factor /= 2.0;
    std::vector<double> result(quantities.size());
    std::transform(quantities.begin(), quantities.end(), result.begin(), [factor](double q) { return q * factor; });
    return result;
}

} // namespace lasagna_master
