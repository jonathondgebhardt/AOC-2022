#include <fstream>
#include <iostream>

#include "InputDirectoryConfig.hpp"
#include "Utilities.ipp"

std::string util::GetInputFile(const std::string& x)
{
    return config::GetInputFilePath() + "/" + x;
}

std::vector<std::string> util::Parse(const std::string& x)
{
    std::vector<std::string> contents;

    if(std::ifstream ifs{x}; ifs.is_open())
    {
        for(std::string line; std::getline(ifs, line);)
        {
            contents.push_back(line);
        }

        // Add the trailing new line to preserve input representation.
        contents.emplace_back();
    }
    else
    {
        std::println(std::cerr, "Could not open '{}'", x);
    }

    return contents;
}

std::vector<std::string> util::Split(const std::string& x, const char delimiter)
{
    std::vector<std::string> tokens;

    std::stringstream ss(x);
    std::string s;
    while(std::getline(ss, s, delimiter))
    {
        tokens.push_back(s);
    }

    return tokens;
}
