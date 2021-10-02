/**
 * @file helper.hpp
 * @author Juho Röyskö
 * @brief Header file for helper.cpp
 * @version 0.1
 * @date 2021-10-02
 */
#include <string>

const std::string TEST_FILES[5] = {"plaintext.txt", "random-plaintext.txt", "special-characters.txt", "all-characters.txt", "random-binary-data.bin"};
bool IsSmaller(std::string compressed_file_name, std::string original_file_name);
std::string Cwd();