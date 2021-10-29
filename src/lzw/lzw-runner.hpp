/**
 * @file lzw-runner.hpp
 * @author Juho Röyskö
 * @brief Header file for lzw-runner.cpp
 * @version 0.2.1
 * @date 2021-10-29
 */
#include <string>

void LZWCompress(std::string const &input_file, bool verbose = 0);
void LZWDecompress(std::string const &input_file, bool verbose = 0);