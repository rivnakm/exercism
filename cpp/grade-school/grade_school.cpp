#include "grade_school.h"
#include <algorithm>

namespace grade_school
{
void school::add(std::string name, int grade)
{
    if (auto it = _roster.find(grade); it != _roster.end())
    {
        auto &grade_roster = it->second;
        auto find_it = std::find_if(grade_roster.begin(), grade_roster.end(),
                                    [name](std::string existing) { return name < existing; });
        grade_roster.insert(find_it, name);
    }
    else
    {
        _roster.emplace(grade, std::vector<std::string>{name});
    }
}

std::map<int, std::vector<std::string>> school::roster() const
{
    return _roster;
}

std::vector<std::string> school::grade(int grade) const
{
    if (auto grade_roster = _roster.find(grade); grade_roster != _roster.end())
    {
        return grade_roster->second;
    }
    else
    {
        return {};
    }
}
} // namespace grade_school
