#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/burrows-wheeler-transform.hpp"
#include "../src/move-to-front-transform.hpp"

TEST_CASE("Testing Burrows-Wheeler transform")
{
    std::pair<std::string, std::string> test_cases[4] = {
        {"foo", "o#of"},
        {"bar", "rb#a"},
        {"aybabtu", "ub#yabta"},
        {" !~", "~# !"}};

    // Test encoding
    for (std::pair<std::string, std::string> test_case : test_cases)
    {
        std::replace(test_case.second.begin(), test_case.second.end(), '#', '\0');
        CHECK(BWTEncode(test_case.first) == test_case.second);
    }

    // Test decoding
    for (std::pair<std::string, std::string> test_case : test_cases)
    {
        std::replace(test_case.second.begin(), test_case.second.end(), '#', '\0');
        CHECK(BWTDecode(test_case.second) == test_case.first);
    }
}

TEST_CASE("Testing move-to-front transform")
{
    std::pair<std::string, std::vector<int>> test_cases[4] = {
        {"abc", {97, 98, 99}},
        {"aaa", {97, 0, 0}},
        {"aabbaa~~b", {97, 0, 98, 0, 1, 0, 126, 0, 2}},
        {"abcdefghijka", {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 10}}};

    // Test encoding
    for (std::pair<std::string, std::vector<int>> test_case : test_cases)
        CHECK(MTFTEncode(test_case.first) == test_case.second);

    // Test decoding
    for (std::pair<std::string, std::vector<int>> test_case : test_cases)
        CHECK(MTFTDecode(test_case.second) == test_case.first);
}