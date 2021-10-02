/**
 * @file huffman-test.cpp
 * @author Juho Röyskö
 * @brief Tests compression using LZW coding
 * @version 0.1
 * @date 2021-10-02
 */
#include <catch.hpp>
#include <stdio.h>
#include "helper.hpp"
#include "../src/lzw-runner.hpp"

/**
 * @brief Test Huffman coding
 */
TEST_CASE("Test LZW coding", "[LZW coding]")
{
    std::string path = Cwd() + "/test-files/";

    SECTION("Test that compressed files are smaller")
    {
        for (std::string test_file : TEST_FILES)
        {
            std::string original_file_name = path + test_file;
            std::string compressed_file_name = test_file + ".bnzip";

            // Compress the file
            INFO("Compressing file '" + original_file_name + "'");
            LZWCompress(original_file_name, 0);

            // Check that the compressed file is smaller in size than the original file
            INFO("Comparing size of '" + compressed_file_name + "' with the size of the original file");
            CHECK(IsSmaller(compressed_file_name, original_file_name));

            // Delete temporary file
            INFO("Deleting file '" + compressed_file_name + "'");
            remove(compressed_file_name.c_str());
        }
    }

    SECTION("Test that decompressed files are equal to original files")
    {
        for (std::string test_file : TEST_FILES)
        {
            std::string original_file_name = path + test_file;
            std::string compressed_file_name = test_file + ".bnzip";
            std::string decompressed_file_name = test_file;

            // Compress the file
            INFO("Compressing file '" + original_file_name + "'");
            LZWCompress(original_file_name, 0);

            // Decompress the compressed file
            INFO("Decompressing file '" + compressed_file_name + "'");
            LZWDecompress(compressed_file_name, 0);

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

    SECTION("Test that compression and decompression work when verbose is true")
    {
        for (std::string test_file : TEST_FILES)
        {
            std::string original_file_name = path + test_file;
            std::string compressed_file_name = test_file + ".bnzip";
            std::string decompressed_file_name = test_file;

            // Compress the file
            INFO("Compressing file '" + original_file_name + "'");
            LZWCompress(original_file_name, 1);

            // Decompress the compressed file
            INFO("Decompressing file '" + compressed_file_name + "'");
            LZWDecompress(compressed_file_name, 1);

            // Delete temporary files
            INFO("Deleting file '" + compressed_file_name + "'");
            remove(compressed_file_name.c_str());
            INFO("Deleting file '" + decompressed_file_name + "'");
            remove(decompressed_file_name.c_str());
        }
    }
}