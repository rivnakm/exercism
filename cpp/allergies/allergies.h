#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>

namespace allergies
{
class allergy_test
{
  public:
    allergy_test(const int score);

    bool is_allergic_to(const std::string allergen) const;
    std::unordered_set<std::string> get_allergies() const;

  private:
    std::unordered_set<std::string> _allergies;
};
} // namespace allergies

#endif // ALLERGIES_H
