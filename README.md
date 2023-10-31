# Advent of Code

## Description

This template is inspired by https://github.com/fspoettel/advent-of-code-rust. The goal is to reduce the amount of
overhead for solving Advent of Code challenges in C++. You don't have to worry about manually editing CMakeLists or your
filesystem.

## Building

Download the template and build. This project depends on gtest, which will be downloaded and built automatically, and
depends on libcurl, which is not included automatically at the moment.

```shell
git clone ...
cd ...
mkdir build && cd build
cmake ../
cmake --build .
```

## Enabling downloading inputs

`StartNewDay` will download your input for you, but in order to do that, it needs your session cookie.
On https://adventofcode.com, press F12 and find your session token. Paste the value into a file in the "inputs"
subdirectory in a file called ".adventofcode.session";

## Starting a new day

Run `StartNewDay` to download input and create the boilerplate code. From your build directory:

```shell
cd bin
./StartNewDay 1 # start day number 1
cmake --build ../
```

"1.cpp" and the accompanying CMakeLists will be added. CMake should be run after running `StartNewDay` to pick up the
new source file.

## Solving

Stub code will be added, so all you have to do is fill in the blanks:

```cpp
namespace
{
    struct Solver : public ACSolver
    {
        Answer solvePartOne() override
        {
            // The day's input will be stored in the member mInput. Other useful utility functions are provided, see Utilities.hpp.
            const auto ii = util::ContainerTo<int64_t>(mInput);
            
            // Solve the part one.
            return std::accumulate(ii.begin(), ii.end(), 1, std::multiplies<>());
        }
    // ...
}

// ...

TEST(day_1, part_1)
{
    // This part needs no changes.
    const auto answer = CreateSolver(false).solvePartOne();
    ASSERT_NE(answer, std::nullopt);
    
    // Once you know the answer, put it here and uncomment. 
    EXPECT_EQ(*answer, 1337);
    
    std::cout << "part one: " << *answer << std::endl;
}
```
