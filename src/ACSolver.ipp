#pragma once

#include "Export.hpp"
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

///
/// \struct ACSolver
/// \brief Provides a consistent interface for solving AoC challenges.
///
struct UTILITIES_EXPORT ACSolver
{
    using Answer = std::optional<int64_t>;

    ACSolver() = default;
    virtual ~ACSolver() noexcept = default;

    ///
    /// \brief Solution for part one.
    /// \return The answer.
    ///
    virtual Answer solvePartOne()
    {
        std::cerr << "Implement part one\n";
        return {};
    }

    ///
    /// \brief Solution for part two.
    /// \return The answer.
    ///
    virtual Answer solvePartTwo()
    {
        std::cerr << "Implement part two\n";
        return {};
    }

    /// \var input
    /// \brief Where all of the challenge input will be stored.
    // TODO: Make a type to describe input?
    std::vector<std::string> input;
};

///
/// \brief Hook for entry-point.
/// \param useSample Whether the sample input file should be used.
/// \return The solver.
///
// std::unique_ptr<ACSolver> CreateSolver(bool useSample);
