#pragma once
#include <string>
#include <array>
#include <sstream>
class Parse_string
{
private:
public:
    Parse_string() = default;
    std::array<int, 5> parseStringToArray(const std::string &str);
    ~Parse_string() = default;
};