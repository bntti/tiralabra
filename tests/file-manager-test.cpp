/**
 * @file file-manager-test.cpp
 * @author Juho Röyskö
 * @brief Tests file-manager.cpp
 * @version 0.3.1
 * @date 2021-10-30
 */
#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <string>
#include <stdio.h>
#include "helper.hpp"
#include "../src/file-manager.hpp"

/**
 * @brief Test file-manager.cpp
 */
TEST_CASE("Test file-manager.cpp", "[file-manager.cpp]")
{
    SECTION("Test functions")
    {
        std::string filename = "tmp.bin";

        INFO("Create file and write one byte to it");
        FileWriter file_writer(filename);
        file_writer.Write(1);
        file_writer.Close();

        INFO("Check that the created file exists");
        CHECK(FileExists(filename));

        INFO("Check that the first byte is correct");
        CHECK(FirstByte(filename) == 1);

        INFO("Check that a file that doesn't exist with FileExists()");
        CHECK(!FileExists("nonexistent.bin"));

        INFO("Try to read first byte of a file that doesn't exist");
        CHECK(FirstByte("nonexistent.bin") == 0);

        INFO("Deleting file '" + filename + "'");
        remove(filename.c_str());

        INFO("Test IsCompressed function");
        INFO("Check a filename that does not end with .bnzip");
        CHECK(!IsCompressed(filename));

        INFO("Check a filename  thatends with .bnzip");
        CHECK(IsCompressed(filename + ".bnzip"));
    }
}
