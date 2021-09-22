/**
 * @file test.cpp
 * @author Juho Röyskö
 * @brief Runs all tests
 * @version 0.3
 * @date 2021-09-22
 */
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <stdio.h>
#include "../src/huffman-runner.hpp"

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
    INFO("Opening file '" + original_file_name + "'");
    std::ifstream original(original_file_name, std::ifstream::ate | std::ifstream::binary);
    CHECK(original.is_open());
    INFO("Opening file '" + compressed_file_name + "'");
    std::ifstream compressed(compressed_file_name, std::ifstream::ate | std::ifstream::binary);
    CHECK(compressed.is_open());

    INFO("Size of compressed file ('" + compressed_file_name + "') is " + std::to_string(compressed.tellg()));
    INFO("Size of original file ('" + original_file_name + "') is " + std::to_string(original.tellg()));
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

/**
 * @brief Test Huffman coding
 */
TEST_CASE("Test Huffman coding", "[Huffman coding]")
{
    std::string test_files[4] = {"plaintext.txt", "special-characters.txt", "all-characters.txt", "random-binary-data.bin"};
    std::string path = Cwd() + "/test-files/";

    SECTION("Test that compressed files are smaller")
    {
        for (std::string test_file : test_files)
        {
            std::string original_file_name = path + test_file;
            std::string compressed_file_name = test_file + ".bnzip";

            // Compress the file
            INFO("Compressing file '" + original_file_name + "'");
            HuffmanCompress(original_file_name);

            // Check that the compressed file is smaller in size than the original file
            INFO("Comparing size of '" + compressed_file_name + "' with the size of the original file");
            CHECK(IsSmaller(compressed_file_name, original_file_name));
            remove(compressed_file_name.c_str());
        }
    }

    SECTION("Test that decompressed files are equal to original files")
    {
        for (std::string test_file : test_files)
        {
            std::string original_file_name = path + test_file;
            std::string compressed_file_name = test_file + ".bnzip";
            std::string decompressed_file_name = test_file;

            // Compress the file
            INFO("Compressing file '" + original_file_name + "'");
            HuffmanCompress(original_file_name);

            // Decompress the compressed file
            INFO("Decompressing file '" + compressed_file_name + "'");
            HuffmanDecompress(compressed_file_name);

            // Compare resulting file to original file and check that they are the same
            INFO("Comparing '" + decompressed_file_name + "' with the original file");
            std::string command = "cmp -s " + original_file_name + " " + decompressed_file_name;
            CHECK(!system(command.c_str()));

            // Delete temporary files
            INFO("Deleting file '" + compressed_file_name + "'");
            remove(compressed_file_name.c_str());
            INFO("Deleting file '" + decompressed_file_name + "'");
            remove(decompressed_file_name.c_str());
        }
    }
}
