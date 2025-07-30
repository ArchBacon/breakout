#pragma once

#include <iomanip>
#include <sstream>
#include <string>

inline std::string ZeroFill(const int value, const int padding)
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(padding) << value;
    return ss.str();
}
