#include <algorithm>
#include <array>
#include <cmath>
#include <iterator>
#include <string>
#include <tuple>
#include <vector>

// Round down all provided student scores.
std::vector<int> round_down_scores(std::vector<double> student_scores)
{
    std::vector<int> result{};
    for (auto score : student_scores)
    {
        result.emplace_back(std::floor(score));
    }
    return result;
}

// Count the number of failing students out of the group provided.
int count_failed_students(std::vector<int> student_scores)
{
    return std::count_if(student_scores.begin(), student_scores.end(), [](int score) { return score <= 40; });
}

// Determine how many of the provided student scores were 'the best' based on the provided threshold.
std::vector<int> above_threshold(std::vector<int> student_scores, int threshold)
{
    std::vector<int> output(student_scores.size());
    auto last = std::copy_if(student_scores.begin(), student_scores.end(), output.begin(),
                             [threshold](int score) { return score >= threshold; });
    output.resize(std::distance(output.begin(), last));

    return output;
}

// Create a list of grade thresholds based on the provided highest grade.
std::array<int, 4> letter_grades(int highest_score)
{
    auto step = (highest_score - 40) / 4;
    std::array<int, 4> result;
    for (auto i = 0; i < 4; i++)
    {
        result[i] = (41 + (step * i));
    }
    return result;
}

// Organize the student's rank, name, and grade information in ascending order.
std::vector<std::string> student_ranking(std::vector<int> student_scores, std::vector<std::string> student_names)
{
    std::vector<std::tuple<std::string, int>> combined;
    for (size_t i = 0; i < student_scores.size(); i++)
    {
        combined.emplace_back(student_names[i], student_scores[i]);
    }

    std::sort(combined.begin(), combined.end(), [](std::tuple<std::string, int> a, std::tuple<std::string, int> b) {
        return std::get<1>(a) > std::get<1>(b);
    });

    std::vector<std::string> result;
    for (size_t i = 0; i < combined.size(); i++)
    {
        result.emplace_back(std::to_string(i + 1) + ". " + std::get<0>(combined[i]) + ": " +
                            std::to_string(std::get<1>(combined[i])));
    }
    return result;
}

// Create a string that contains the name of the first student to make a perfect score on the exam.
std::string perfect_score(std::vector<int> student_scores, std::vector<std::string> student_names)
{
    for (size_t i = 0; i < student_scores.size(); i++)
    {
        if (student_scores[i] == 100)
        {
            return student_names[i];
        }
    }
    return "";
}
