#pragma once

#include "Export.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

///
/// \struct ACSolver
/// \brief Provides a consistent interface for solving AoC challenges.
///
struct UTILITIES_EXPORT ACSolver
{
    ACSolver() = default;
    virtual ~ACSolver() = default;

    ///
    /// \brief Solution for part one.
    /// \return The answer.
    ///
    virtual int64_t solvePartOne()
    {
        std::cerr << "Implement part one\n";
        return 0;
    }

    ///
    /// \brief Solution for part two.
    /// \return The answer.
    ///
    virtual int64_t solvePartTwo()
    {
        std::cerr << "Implement part two\n";
        return 0;
    }

    /// \var input
    /// \brief Where all of the challenge input will be stored.
    std::vector<std::string> input;
};

///
/// \brief Hook for entry-point.
/// \param useSample Whether the sample input file should be used.
/// \return The solver.
///
std::unique_ptr<ACSolver> CreateSolver(bool useSample);
