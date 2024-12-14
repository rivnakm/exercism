#pragma once

#include <string>
#include <vector>

namespace lasagna_master
{

struct amount
{
    int noodles;
    double sauce;
};

int preparationTime(std::vector<std::string> layers, int avg_time = 2);
struct amount quantities(std::vector<std::string> ingredients);
void addSecretIngredient(std::vector<std::string> &myList, const std::vector<std::string> friendList);
void addSecretIngredient(std::vector<std::string> &myList, const std::string secretIngredient);
std::vector<double> scaleRecipe(std::vector<double> quantities, double factor);

} // namespace lasagna_master
