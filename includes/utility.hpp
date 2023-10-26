#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <utility>
#include "json.hpp"
#pragma once
namespace utility
{
    std::vector<std::string> split(std::string str, std::string delimiter);
    bool vectorContainsString(std::vector<std::string> &vec, std::string str);
    int distance(std::pair<int, int> p1, std::pair<int, int> p2);
    std::string validateJSONStringElement(nlohmann::json &j, std::string elementName);
    int validateJSONIntegralElement(nlohmann::json &j, std::string elementName);
    bool validateJSONBoolean(nlohmann::json &j, std::string elementName);
} // namespace utility
