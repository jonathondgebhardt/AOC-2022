#pragma once

#include <cstring>
#include <memory>
#include <iostream>
#include <chrono>

///
/// \brief Serves as the main entry-point for all AoC solvers.
///
/// Include this file in your solver and add a definition for CreateSolver.
///
/// \param argc Command line argument count.
/// \param argv Command line arguments.
/// \return Whether the solver terminated successfully.
///
int main(int argc, char** argv)
{
    auto useSample = false;
    auto solvePartOne = true;
    auto solvePartTwo = true;
    auto timeSolutions = false;

    for(int i = 1; i < argc; ++i)
    {
        if(strcmp(argv[i], "--sample") == 0)
        {
            useSample = true;
        }
        else if(strcmp(argv[i], "--part1") == 0)
        {
            solvePartTwo = false;
        }
        else if(strcmp(argv[i], "--part2") == 0)
        {
            solvePartOne = false;
        }
        else if(strcmp(argv[i], "--time") == 0)
        {
            timeSolutions = true;
        }
        else if(strcmp(argv[i], "--help") == 0)
        {
            std::cerr << "Usage: Solver [--sample] [--part1] [--part2]\n";
            std::cerr << "\t--sample Use the sample input file (false by default)\n";
            std::cerr << "\t--part1 Solve part1 (true by default)\n";
            std::cerr << "\t--part2 Solve part2 (true by default)\n";
            std::cerr << "\t--time Measure time spent solving (false by default)\n";

            return EXIT_FAILURE;
        }
    }

    if(!solvePartOne && !solvePartTwo)
    {
        solvePartOne = true;
        solvePartTwo = true;
    }

    auto solver = CreateSolver(useSample);

    if(solvePartOne)
    {
        const auto start = std::chrono::high_resolution_clock::now();
        auto answer = solver->solvePartOne();
        const auto end = std::chrono::high_resolution_clock::now();

        std::cout << "part 1: " << answer;

        if(timeSolutions)
        {
            const auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cout << " (" << delta.count() << " ms)";
        }

        std::cout << "\n";
    }

    if(solvePartTwo)
    {
        const auto start = std::chrono::high_resolution_clock::now();
        auto answer = solver->solvePartTwo();
        const auto end = std::chrono::high_resolution_clock::now();

        std::cout << "part 2: " << answer;

        if(timeSolutions)
        {
            const auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cout << " (" << delta.count() << " ms)";
        }

        std::cout << "\n";
    }

    return EXIT_SUCCESS;
}
