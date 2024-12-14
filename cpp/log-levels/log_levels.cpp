#include <string>

namespace log_line
{
std::string message(std::string line)
{
    auto message_start = line.find(": ") + 2;
    return line.substr(message_start, line.length() - message_start);
}

std::string log_level(std::string line)
{
    auto open_bracket = line.find("[");
    auto close_bracket = line.find("]");
    return line.substr(open_bracket + 1, close_bracket - (open_bracket + 1));
}

std::string reformat(std::string line)
{
    auto msg = message(line);
    auto level = log_level(line);

    return msg + " (" + level + ")";
}
} // namespace log_line
