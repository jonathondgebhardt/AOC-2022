#pragma once

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace util
{
    std::string GetInputFile(const std::string& stem);

    std::vector<std::string> ParseToContainer(const std::string& filePath);

    std::string Parse(const std::string& filePath);

    template <class T> T StringTo(const std::string& x)
    {
        T result;
        std::stringstream ss(x);
        ss >> result;

        return result;
    }

    template <class T> std::vector<T> ContainerTo(const std::vector<std::string>& x)
    {
        std::vector<T> converted;
        std::ranges::transform(x, std::back_inserter(converted),
                               [](const auto& y) { return StringTo<T>(y); });

        return converted;
    }

    std::vector<std::string> Split(const std::string& x, char delimiter = ' ');
}
