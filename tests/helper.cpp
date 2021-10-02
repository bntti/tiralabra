/**
 * @file helper.cpp
 * @author Juho Röyskö
 * @brief Provides functions for tests
 * @version 0.1
 * @date 2021-10-02
 */
#include <catch.hpp>
#include <string>
#include <fstream>
#include <unistd.h>

/**
 * @brief Check if compressed file is smaller in size than the original
 * 
 * @param compressed_file_name Path to compressed file
 * @param original_file_name Path to original file
 * @return true If compressed file is smaller in size than the original
 * @return false Otherwise
 */
bool IsSmaller(std::string compressed_file_name, std::string original_file_name)
{
    // Open files and check that they are open
    std::ifstream original(original_file_name, std::ifstream::ate | std::ifstream::binary);
    CHECK(original.is_open());
    std::ifstream compressed(compressed_file_name, std::ifstream::ate | std::ifstream::binary);
    CHECK(compressed.is_open());

    return compressed.tellg() < original.tellg();
}

/**
 * @brief Get current working directory
 * 
 * @return std::string Current working directory
 */
std::string Cwd()
{
    char cwd[256];
    getcwd(cwd, 256);
    return cwd;
}
