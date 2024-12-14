#pragma once

#include <string>

namespace star_map
{
enum class System
{
    AlphaCentauri,
    BetaHydri,
    DeltaEridani,
    EpsilonEridani,
    Omicron2Eridani,
    Sol,
};
} // namespace star_map

namespace heaven
{
class Vessel
{
  public:
    Vessel(std::string name, int generation) : generation(generation), name(name)
    {
    }
    Vessel(std::string name, int generation, star_map::System system)
        : generation(generation), current_system(system), name(name)
    {
    }

    int busters = 0;
    int generation;
    star_map::System current_system = star_map::System::Sol;
    std::string name;

    void make_buster();
    bool shoot_buster();
    Vessel replicate(std::string name);
};

std::string get_older_bob(Vessel a, Vessel b);
bool in_the_same_system(Vessel a, Vessel b);
} // namespace heaven
