#include "doctor_data.h"

namespace heaven
{
void Vessel::make_buster()
{
    busters++;
}

bool Vessel::shoot_buster()
{
    if (busters > 0)
    {
        busters--;
        return true;
    }
    return false;
}

Vessel Vessel::replicate(std::string name)
{
    return Vessel{name, generation + 1, current_system};
}

std::string get_older_bob(Vessel a, Vessel b)
{
    if (a.name == "Bob" and b.name == "Bob")
    {
        return a.generation < b.generation ? a.name : b.name;
    }
    if (a.name == "Bob")
    {
        return a.name;
    }
    else if (b.name == "Bob")
    {
        return b.name;
    }
    else
    {
        return "";
    }
}

bool in_the_same_system(Vessel a, Vessel b)
{
    return a.current_system == b.current_system;
}
} // namespace heaven
