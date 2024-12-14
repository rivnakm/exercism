#include <stdexcept>
namespace hellmath
{
enum class AccountStatus
{
    troll = 0,
    guest,
    user,
    mod,
};

enum class Action
{
    read = 0,
    write,
    remove,
};

bool display_post(AccountStatus poster, AccountStatus viewer)
{
    if (poster == AccountStatus::troll)
    {
        return viewer == AccountStatus::troll;
    }
    return true;
}

bool permission_check(Action action, AccountStatus acctStatus)
{
    switch (acctStatus)
    {
    case AccountStatus::mod:
        return true;
    case AccountStatus::troll:
        [[fallthrough]];
    case AccountStatus::user:
        return action == Action::read or action == Action::write;
    case AccountStatus::guest:
        return action == Action::read;
    }

    throw std::out_of_range("acctStatus");
}

bool valid_player_combination(AccountStatus one, AccountStatus two)
{
    if (one == AccountStatus::troll and two == AccountStatus::troll)
    {
        return true;
    }
    else if (one == AccountStatus::troll or two == AccountStatus::troll or one == AccountStatus::guest or
             two == AccountStatus::guest)
    {
        return false;
    }
    return true;
}

bool has_priority(AccountStatus first, AccountStatus second)
{
    return first > second;
}

} // namespace hellmath
