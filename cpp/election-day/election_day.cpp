#include <climits>
#include <stdexcept>
#include <string>
#include <vector>

namespace election
{

// The election result struct is already created for you:

struct ElectionResult
{
    // Name of the candidate
    std::string name{};
    // Number of votes the candidate has
    int votes{};
};

int vote_count(ElectionResult &result)
{
    return result.votes;
}

void increment_vote_count(ElectionResult &result, int num_votes)
{
    result.votes += num_votes;
}

ElectionResult &determine_result(std::vector<ElectionResult> &final_count)
{
    int max = INT_MIN;
    for (const auto &result : final_count)
    {
        if (result.votes > max)
        {
            max = result.votes;
        }
    }

    for (auto &result : final_count)
    {
        if (result.votes == max)
        {
            result.name = "President " + result.name;
            return result;
        }
    }

    throw std::invalid_argument{""};
}
} // namespace election
