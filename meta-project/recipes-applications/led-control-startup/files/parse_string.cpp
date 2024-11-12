#include "parse_string.hpp"

std::array<int, 5> Parse_string::parseStringToArray(const std::string &str)
{
    std::array<int, 5> result;
    std::string cleanedStr = str.substr(1, str.size() - 2); // Remove '[' and ']'
    std::stringstream ss(cleanedStr);
    std::string token;
    int index = 0;

    while (std::getline(ss, token, ',') && index < result.size())
    {
        result[index++] = std::stoi(token); // Convert each token to an integer
    }

    return result;
}