#include "utility.hpp"
namespace utility
{
    bool vectorContainsString(std::vector<std::string> &vec, std::string str)
    {
        return std::find(vec.begin(), vec.end(), str) != vec.end();
    }

    int distance(std::pair<int, int> p1, std::pair<int, int> p2)
    {
        return std::sqrt(std::pow(p1.first - p2.first, 2) + std::pow(p1.second - p2.second, 2));
    }

    std::vector<std::string> split(std::string str, std::string delimiter)
    {
        std::vector<std::string> result;
        size_t pos = 0;
        std::string token;
        while ((pos = str.find(delimiter)) != std::string::npos)
        {
            token = str.substr(0, pos);
            result.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        result.push_back(str);
        return result;
    }

    std::string validateJSONStringElement(nlohmann::json &j, std::string elementName)
    {
        if (!j.contains(elementName) || !j[elementName].is_string())
        {
            throw std::runtime_error("JSON object does not contain element " + elementName);
        }
        return j[elementName];
    }

    int validateJSONIntegralElement(nlohmann::json &j, std::string elementName)
    {
        if (!j.contains(elementName) || !j[elementName].is_number_integer())
        {
            throw std::runtime_error("JSON object does not contain element " + elementName);
        }
        return j[elementName];
    }
    // https://json.nlohmann.me/api/basic_json/is_boolean/
    bool validateJSONBoolean(nlohmann::json &j, std::string elementName)
    {
        if (!j.contains(elementName) || !j[elementName].is_boolean())
        {
            throw std::runtime_error("JSON object does not contain element " + elementName);
        }
        return j[elementName];
    }
}