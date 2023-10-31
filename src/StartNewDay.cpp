#include "HttpsRequest.hpp"
#include "InputDirectoryConfig.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

void showUsage(const std::string& x)
{
    // TODO: Add more detail
    std::cout << "Usage: " << x << " DAY_NUMBER [-f]\n";
    std::cout << "       DAY_NUMBER Which day to start\n";
    std::cout << "       -f Force overwrite\n";
}

bool tryCreateSolutionDirectory(const std::string& rootPath, bool forceOverwrite)
{
    if(std::filesystem::exists(rootPath) && !forceOverwrite)
    {
        return false;
    }

    std::filesystem::create_directory(rootPath);
    return std::filesystem::exists(rootPath);
}

bool createCMakeLists(const std::filesystem::path& x)
{
    const auto cmakeLists = x / "CMakeLists.txt";
    std::ofstream ofs(cmakeLists);
    if(ofs.is_open())
    {
        // TODO: Don't hard-code?
        ofs << "# File auto-generated by StartNewDay\n";

        // TODO: Update this version number
        ofs << "cmake_minimum_required(VERSION 3.0)\n";

        const auto dayNumber = std::string(x.filename());
        ofs << "project(day" << dayNumber << " CXX)\n";
        ofs << "\n";

        ofs << "enable_testing()\n";
        ofs << "\n";

        const auto solutionFile = dayNumber + ".cpp";
        ofs << "add_executable(${PROJECT_NAME} " << solutionFile << ")\n";
        ofs << "target_link_libraries(${PROJECT_NAME} GTest::gtest_main AOC)\n";
        ofs << "\n";

        ofs << "include(GoogleTest)\n";
        ofs << "gtest_discover_tests(${PROJECT_NAME})\n";

        return true;
    }

    return false;
}

// TODO: Use an in-file for this?
bool createSourceFiles(const std::filesystem::path& x)
{
    const auto dayNumber = std::string(x.filename());
    const auto solutionFile = dayNumber + ".cpp";
    std::ofstream ofs{x / solutionFile};
    if(!ofs.is_open())
    {
        return false;
    }

    ofs << "// File auto-generated by StartNewDay\n";
    ofs << "\n";

    ofs << "#include <ACSolver.ipp>\n";
    ofs << "#include <Utilities.ipp>\n";
    ofs << "#include <gtest/gtest.h>\n";
    ofs << "\n";

    ofs << "namespace\n";
    ofs << "{\n";
    ofs << "    struct Solver : public ACSolver\n";
    ofs << "    {\n";
    ofs << "        Answer solvePartOne() override\n";
    ofs << "        {\n";
    ofs << "            return ACSolver::solvePartOne();\n";
    ofs << "        }\n";
    ofs << "\n";
    ofs << "        Answer solvePartTwo() override\n";
    ofs << "        {\n";
    ofs << "            return ACSolver::solvePartTwo();\n";
    ofs << "        }\n";
    ofs << "    };\n";
    ofs << "\n";
    ofs << "    Solver CreateSolver(bool useSample)\n";
    ofs << "    {\n";
    ofs << "        const auto inputFile = useSample ? \"" << dayNumber << "_sample.txt\" : \""
        << dayNumber << ".txt\";\n";
    ofs << "        Solver solver;\n";
    ofs << "        solver.mInput = util::Parse(util::GetInputFile(inputFile));\n";
    ofs << "        return solver;\n";
    ofs << "    }\n";
    ofs << "}\n";
    ofs << "\n";
    ofs << "TEST(day_" << dayNumber << ", part_one)\n";
    ofs << "{\n";
    ofs << "    const auto answer = CreateSolver(false).solvePartOne();\n";
    ofs << "    ASSERT_NE(answer, std::nullopt);\n";
    ofs << "    // EXPECT_EQ(*answer, INSERT_CORRECT_ANSWER);\n";
    ofs << "    std::cout << \"part one: \" << *answer << std::endl;\n";
    ofs << "}\n";
    ofs << "\n";
    ofs << "TEST(day_" << dayNumber << ", part_two)\n";
    ofs << "{\n";
    ofs << "    const auto answer = CreateSolver(false).solvePartTwo();\n";
    ofs << "    ASSERT_NE(answer, std::nullopt);\n";
    ofs << "    // EXPECT_EQ(*answer, INSERT_CORRECT_ANSWER);\n";
    ofs << "    std::cout << \"part two: \" << *answer << std::endl;\n";
    ofs << "}\n";
    ofs << "\n";
    ofs << "TEST(day_" << dayNumber << ", part_one_sample)\n";
    ofs << "{\n";
    ofs << "    const auto answer = CreateSolver(true).solvePartOne();\n";
    ofs << "    ASSERT_NE(answer, std::nullopt);\n";
    ofs << "    // EXPECT_EQ(*answer, PART_ONE_SAMPLE_ANSWER);\n";
    ofs << "}\n";
    ofs << "\n";
    ofs << "TEST(day_" << dayNumber << ", part_two_sample)\n";
    ofs << "{\n";
    ofs << "    const auto answer = CreateSolver(true).solvePartTwo();\n";
    ofs << "    ASSERT_NE(answer, std::nullopt);\n";
    ofs << "    // EXPECT_EQ(*answer, PART_TWO_SAMPLE_ANSWER);\n";
    ofs << "}\n";

    return true;
}

void showNewDayContents(const std::filesystem::path& x, size_t indent = 1)
{
    for(const auto& item : std::filesystem::directory_iterator(x))
    {
        for(size_t i = 0; i < indent; ++i)
        {
            std::cout << "\t";
        }

        std::cout << item << "\n";

        if(std::filesystem::is_directory(item))
        {
            showNewDayContents(item, ++indent);
            --indent;
        }
    }
}

bool downloadInput(const std::string& dayNumber)
{
    auto success = false;

    HttpsRequest request;
    request.setUrl("https://adventofcode.com/2022/day/" + dayNumber + "/input");
    request.setContentType("text/plain");
    if(const auto content = request(); !content.empty())
    {
        std::ofstream ofs{config::GetInputFilePath() + "/" + dayNumber + ".txt"};
        for(const auto& line : content)
        {
            ofs << line << "\n";
        }

        success = true;
    }

    return success;
}

bool downloadSampleInput(const std::string& dayNumber)
{
    auto success = false;

    HttpsRequest request;
    request.setUrl("https://adventofcode.com/2022/day/" + dayNumber);
    request.setContentType("text/html");
    if(const auto content = request(); !content.empty())
    {
        std::ofstream ofs{config::GetInputFilePath() + "/" + dayNumber + "_sample.txt"};

        // Beginning of sample input starts with "<pre><code>" and ends with "</code></pre>"
        // Ex:
        // <pre><code>A Y
        // B X
        // C Z
        // </code></pre>
        auto sampleInputFound = false;
        for(const auto& line : content)
        {
            auto sampleInput = line;
            if(line.find("<pre><code>") != std::string::npos)
            {
                sampleInputFound = true;

                sampleInput = line.substr(line.find_last_of('>') + 1);
            }

            if(line == "</code></pre>")
            {
                break;
            }

            if(sampleInputFound)
            {
                ofs << sampleInput << "\n";
            }
        }

        success = true;
    }

    return success;
}

int main(int argc, char* argv[])
{
    const auto applicationName = std::string(argv[0]);

    // TODO: Add command line argument for help
    // TODO: Add command line argument for dry-run
    if(argc < 2)
    {
        showUsage(applicationName);
        return EXIT_FAILURE;
    }

    std::filesystem::path solutionsPath(config::GetSolutionsPath());
    if(!std::filesystem::exists(solutionsPath))
    {
        std::cerr << "Could not find solutions path " << solutionsPath << "\n";
        return EXIT_FAILURE;
    }

    constexpr size_t newDayIndex = 1;
    const auto newDay = std::string(argv[newDayIndex]);

    constexpr size_t forceOverwriteIndex = 2;
    auto forceOverwrite = false;

    if(argc == 3 && std::string(argv[forceOverwriteIndex]) == "-f")
    {
        forceOverwrite = true;
    }

    const auto newDayPath = solutionsPath / newDay;
    if(!tryCreateSolutionDirectory(newDayPath, forceOverwrite))
    {
        std::cerr << "Could not create new subdirectory " << newDayPath << "\n";
        std::cerr << "Check write permissions or if subdirectory already exists\n";
        std::cerr << "\n";
        showUsage(applicationName);

        return EXIT_FAILURE;
    }

    if(forceOverwrite)
    {
        std::cout << "Overwriting day " << newDay << "...\n";
    }
    else
    {
        std::cout << "Starting new day " << newDay << "...\n";
    }

    if(!createCMakeLists(newDayPath))
    {
        std::cerr << "Could not create CMakeLists.txt for " << newDayPath << "\n";
        return EXIT_FAILURE;
    }

    if(!createSourceFiles(newDayPath))
    {
        std::cerr << "Could not create source files for " << newDayPath << "\n";
        return EXIT_FAILURE;
    }

    if(!downloadInput(newDay))
    {
        std::cerr << "Could not download input\n";
        return EXIT_FAILURE;
    }

    if(!downloadSampleInput(newDay))
    {
        // This is not a deal breaker. Just grab it yourself ya bum.
        std::cerr << "Could not download sample input\n";
    }

    std::cout << "Files created:\n";
    showNewDayContents(newDayPath);
    std::cout << "\n";

    std::cout << "Re-run CMake to build the new day\n";

    return EXIT_SUCCESS;
}