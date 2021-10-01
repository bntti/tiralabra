/**
 * @file lzw-runner.cpp
 * @author Juho Röyskö
 * @brief Header file for lzw-runner.cpp
 * @version 0.1
 * @date 2021-10-01
 */
#include <string>

void LZWCompress(std::string const &input_file, bool verbose = 1);
void LZWDecompress(std::string const &input_file, bool verbose = 0);