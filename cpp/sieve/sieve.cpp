#include "sieve.h"
#include <algorithm>
#include <iterator>

namespace sieve
{
bool is_prime(int n);

std::vector<int> primes(int num)
{
    std::vector<std::pair<int, bool>> all_nums;
    for (int i = 2; i <= num; i++)
    {
        all_nums.emplace_back(std::make_pair(i, false));
    }

    for (auto &[num, is_marked] : all_nums)
    {
        if (!is_marked)
        {
            for (auto &[inner_num, inner_is_marked] : all_nums)
            {
                if (inner_num == num)
                {
                    continue;
                }
                if (inner_num % num == 0)
                {
                    inner_is_marked = true;
                }
            }
        }
    }

    std::vector<std::pair<int, bool>> marked_nums(all_nums.size());
    auto end = std::copy_if(all_nums.begin(), all_nums.end(), marked_nums.begin(),
                            [](std::pair<int, bool> pair) { return !pair.second; });
    marked_nums.resize(std::distance(marked_nums.begin(), end));
    marked_nums.shrink_to_fit();

    std::vector<int> primes(marked_nums.size());
    std::transform(marked_nums.begin(), marked_nums.end(), primes.begin(),
                   [](std::pair<int, bool> pair) { return pair.first; });

    return primes;
}

bool is_prime(int n)
{
    if (n < 2)
    {
        return false;
    }
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}
} // namespace sieve
