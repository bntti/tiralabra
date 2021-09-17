/**
 * @file test.cpp
 * @author Juho Röyskö
 * @brief Runs all tests
 * @version 0.1
 * @date 2021-09-17
 */
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "../src/burrows-wheeler-transform.hpp"
#include "../src/move-to-front-transform.hpp"

/**
 * @brief Tests Burrows-Wheeler transform
 */
TEST_CASE("Testing Burrows-Wheeler transform", "[Burrows-Wheeler transform]")
{
    std::pair<std::string, std::string> test_cases[4] = {
        {"foo", "o#of"},
        {"bar", "rb#a"},
        {"aybabtu", "ub#yabta"},
        {" !~", "~# !"}};

    SECTION("Test encoding")
    {
        for (std::pair<std::string, std::string> test_case : test_cases)
        {
            std::replace(test_case.second.begin(), test_case.second.end(), '#', '\0');
            REQUIRE(BWTEncode(test_case.first) == test_case.second);
        }
    }

    SECTION("Test decoding")
    {
        for (std::pair<std::string, std::string> test_case : test_cases)
        {
            std::replace(test_case.second.begin(), test_case.second.end(), '#', '\0');
            REQUIRE(BWTDecode(test_case.second) == test_case.first);
        }
    }
}

/**
 * @brief Tests move-to-front transform
 */
TEST_CASE("Testing move-to-front transform", "[move-to-front transform]")
{
    std::pair<std::string, std::vector<int>> test_cases[4] = {
        {"abc", {97, 98, 99}},
        {"aaa", {97, 0, 0}},
        {"aabbaa~~b", {97, 0, 98, 0, 1, 0, 126, 0, 2}},
        {"abcdefghijka", {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 10}}};

    SECTION("Test encoding")
    {
        for (std::pair<std::string, std::vector<int>> test_case : test_cases)
            REQUIRE(MTFTEncode(test_case.first) == test_case.second);
    }

    SECTION("Test decoding")
    {
        for (std::pair<std::string, std::vector<int>> test_case : test_cases)
            REQUIRE(MTFTDecode(test_case.second) == test_case.first);
    }
}