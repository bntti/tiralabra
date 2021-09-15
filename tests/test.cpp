#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/burrows-wheeler-transform.hpp"

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
        CHECK(Encode(test_case.first) == test_case.second);
    }

    // Test decoding
    for (std::pair<std::string, std::string> test_case : test_cases)
        CHECK(Decode(Encode(test_case.first)) == test_case.first);
}