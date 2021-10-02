/**
 * @file huffman-test.cpp
 * @author Juho Röyskö
 * @brief Tests Huffman coding compression
 * @version 0.1.2
 * @date 2021-10-02
 */
#include <catch.hpp>
#include <stdio.h>
#include "helper.hpp"
#include "../src/huffman/huffman-runner.hpp"

/**
 * @brief Test Huffman coding
 */
TEST_CASE("Test Huffman coding", "[Huffman coding]")
{
    std::string path = Cwd() + "/test-files/";

    SECTION("Test that compressed files are smaller")
    {
        for (std::string test_file : TEST_FILES)
        {
            std::string original_file_name = path + test_file;
            std::string compressed_file_name = test_file + ".bnzip";

            INFO("Compressing file '" + original_file_name + "'");
            HuffmanCompress(original_file_name, 0);

            INFO("Comparing size of '" + compressed_file_name + "' with the size of the original file");
            CHECK(IsSmaller(compressed_file_name, original_file_name));

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

            INFO("Compressing file '" + original_file_name + "'");
            HuffmanCompress(original_file_name, 0);

            INFO("Decompressing file '" + compressed_file_name + "'");
            HuffmanDecompress(compressed_file_name, 0);

            INFO("Comparing '" + decompressed_file_name + "' with the original file");
            std::string command = "cmp -s " + original_file_name + " " + decompressed_file_name;
            CHECK(!system(command.c_str()));

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

            INFO("Compressing file '" + original_file_name + "'");
            HuffmanCompress(original_file_name, 1);

            INFO("Decompressing file '" + compressed_file_name + "'");
            HuffmanDecompress(compressed_file_name, 1);

            INFO("Deleting file '" + compressed_file_name + "'");
            remove(compressed_file_name.c_str());
            INFO("Deleting file '" + decompressed_file_name + "'");
            remove(decompressed_file_name.c_str());
        }
    }
}
